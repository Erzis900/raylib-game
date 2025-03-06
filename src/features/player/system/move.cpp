#include "move.hpp"
#include "player/component/isPlayer.hpp"
#include "component/position.hpp"
#include "component/speed.hpp"

namespace player
{
    void move(entt::registry &registry, float dt)
    {
        auto view = registry.view<player::isPlayer, component::position, component::speed>();
        for (auto [player, pos, speed] : view.each())
        {
            Vector2 direction = {0, 0};

            if(IsKeyDown(KEY_W)) direction.y -= 1;
            if(IsKeyDown(KEY_S)) direction.y += 1;
            if(IsKeyDown(KEY_A)) direction.x -= 1;
            if(IsKeyDown(KEY_D)) direction.x += 1;

            direction = Vector2Normalize(direction);

            registry.replace<component::position>(player, pos.x + direction.x * speed.value * dt,  pos.y + direction.y * speed.value * dt);
        }
    }
}