#include "drawRectangle.hpp"
#include "component/position.hpp"
#include "component/size.hpp"
#include "component/color.hpp"

namespace renderer
{
    void drawRectangle(entt::registry &registry)
    {
        auto view = registry.view<component::position, component::size, component::color>();
        for (auto [rectangle, position, size, color] : view.each())
        {
            DrawRectangleLines(position.vec.x, position.vec.y, size.vec.x, size.vec.y, color.data);
        }
    }
}