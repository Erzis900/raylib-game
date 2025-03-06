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
        auto view = registry.view<player::isPlayer, component::position, component::speed, component::direction>();
        for (auto [player, position, speed, direction] : view.each())
        {
            if(IsKeyDown(KEY_W)) direction.vec.y -= 1;
            if(IsKeyDown(KEY_S)) direction.vec.y += 1;
            if(IsKeyDown(KEY_A)) direction.vec.x -= 1;
            if(IsKeyDown(KEY_D)) direction.vec.x += 1;

            direction.vec = Vector2Normalize(direction.vec);

            if(direction.vec.x == 0 && direction.vec.y == 0)
            {
                // fmt::print("idle\n");
            }
            else 
            {
                // fmt::print("moving\n");
            }

            registry.replace<component::position>(player, position.vec.x + direction.vec.x * speed.value * dt,  position.vec.y + direction.vec.y * speed.value * dt);
            registry.replace<component::direction>(player, Vector2(0, 0));
        }
    }
}