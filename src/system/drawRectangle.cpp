#include "drawRectangle.hpp"
#include "component/position.hpp"
#include "component/size.hpp"
#include "component/color.hpp"
// #include "component/hitbox.hpp"
#include "component/collider.hpp"

namespace renderer
{
    void drawRectangle(entt::registry &registry)
    {
        auto view = registry.view<component::collider, component::color>();
        for (auto [rectangle, collider, color] : view.each())
        {
            DrawRectangleLines(collider.rect.x, collider.rect.y, collider.rect.width, collider.rect.height, color.data);
            // DrawCircle(position.vec.x, position.vec.y, 1, color.data);
        }
    }
}