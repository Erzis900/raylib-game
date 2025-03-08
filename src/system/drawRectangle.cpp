#include "drawRectangle.hpp"
#include "component/position.hpp"
#include "component/size.hpp"
#include "component/color.hpp"
#include "component/hitbox.hpp"

namespace renderer
{
    void drawRectangle(entt::registry &registry)
    {
        auto view = registry.view<component::position, component::hitbox, component::color>();
        for (auto [rectangle, position, hitbox, color] : view.each())
        {
            DrawRectangleLines(hitbox.rect.x, hitbox.rect.y, hitbox.rect.width, hitbox.rect.height, color.data);
            // DrawRectangleLines(position.vec.x, position.vec.y, hitbox.rect.width, hitbox.rect.height, color.data);
            // DrawCircle(position.vec.x, position.vec.y, 1, color.data);
        }
    }
}