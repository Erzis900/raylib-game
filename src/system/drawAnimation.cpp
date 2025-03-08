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

            float offsetX = (animation.frameSize.x / 2) * animation.scale + 1;
            float offsetY = (animation.frameSize.y / 2) * animation.scale + animation.frameSize.y * 0.3;

            Rectangle scaledFrame = {position.vec.x - offsetX, position.vec.y - offsetY, frame.width * animation.scale, frame.height * animation.scale};
            DrawTexturePro(animation.texture, frame, scaledFrame, Vector2(0, 0), 0, WHITE);
        }
    }
}