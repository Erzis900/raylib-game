#include "move.hpp"
#include "player/component/isPlayer.hpp"
#include "player/component/state.hpp"
#include "component/position.hpp"
#include "component/speed.hpp"
#include "component/direction.hpp"

namespace player
{
    void move(entt::registry &registry, float dt)
    {
        auto view = registry.view<player::isPlayer, component::position, component::speed, component::direction, player::state>();
        for (auto [player, position, speed, direction, state] : view.each())
        {
            if(IsKeyDown(KEY_W)) direction.vec.y -= 1;
            if(IsKeyDown(KEY_S)) direction.vec.y += 1;
            if(IsKeyDown(KEY_A)) direction.vec.x -= 1;
            if(IsKeyDown(KEY_D)) direction.vec.x += 1;

            direction.vec = Vector2Normalize(direction.vec);

            if(direction.vec.x == 0 && direction.vec.y == 0)
            {
                if(state.currentState == state::walk && state.currentState != state::idle) registry.replace<player::state>(player, state::idle);
                else if(state.currentState == state::walk_right && state.currentState != state::idle_right) registry.replace<player::state>(player, state::idle_right);
                else if(state.currentState == state::walk_left && state.currentState != state::idle_left) registry.replace<player::state>(player, state::idle_left);
                else if(state.currentState == state::walk_back && state.currentState != state::idle_back) registry.replace<player::state>(player, state::idle_back);
            }
            else if (direction.vec.x > 0 && state.currentState != state::walk_right)
            {
                registry.replace<player::state>(player, state::walk_right);
            }
            else if (direction.vec.x < 0 && state.currentState != state::walk_left)
            {
                registry.replace<player::state>(player, state::walk_left);
            }
            else if (direction.vec.y > 0 && state.currentState != state::walk)
            {
                registry.replace<player::state>(player, state::walk);
            }
            else if (direction.vec.y < 0 && state.currentState != state::walk_back)
            {
                registry.replace<player::state>(player, state::walk_back);
            }

            registry.replace<component::position>(player, position.vec.x + direction.vec.x * speed.value * dt,  position.vec.y + direction.vec.y * speed.value * dt);
            registry.replace<component::direction>(player, Vector2(0, 0));
        }
    }
}