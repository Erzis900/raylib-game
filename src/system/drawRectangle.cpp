#include "drawRectangle.hpp"
#include "component/hitbox.hpp"
#include "component/collider.hpp"

namespace renderer
{
    void drawRectangle(entt::registry &registry)
    {
        auto colliderView = registry.view<component::collider>();
        for (auto [rectangle, collider] : colliderView.each())
        {
            DrawRectangleLines(collider.rect.x, collider.rect.y, collider.rect.width, collider.rect.height, collider.color);
            // DrawCircle(position.vec.x, position.vec.y, 1, color.data);
        }

        auto hitboxView = registry.view<component::hitbox>();
        for (auto [rectangle, hitbox] : hitboxView.each())
        {
            DrawRectangleLines(hitbox.rect.x, hitbox.rect.y, hitbox.rect.width, hitbox.rect.height, hitbox.color);
            // DrawCircle(position.vec.x, position.vec.y, 1, color.data);
        }
    }
}