#include "drawAnimation.hpp"
#include "component/animation.hpp"
#include "component/position.hpp"

namespace renderer
{
    void drawAnimation(entt::registry &registry)
    {
        auto view = registry.view<component::animation, component::position>();
        for (auto [entity, animation, position] : view.each())
        {
            Rectangle frame = animation.frameRec;
            Rectangle scaledFrame = {position.vec.x, position.vec.y, frame.width * animation.scale, frame.height * animation.scale};
            DrawTexturePro(animation.texture, frame, scaledFrame, Vector2(0, 0), 0, WHITE);
        }
    }
}