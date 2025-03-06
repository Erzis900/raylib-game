#include "updateAnimFrame.hpp"
#include "component/animation.hpp"

namespace systems
{
    void updateAnimFrame(entt::registry &registry, float dt)
    {
        auto view = registry.view<component::animation>();
        for (auto [entity, animation] : view.each())
        {
            animation.elapsedTime += dt;
            if (animation.elapsedTime >= animation.frameTime)
            {
                animation.elapsedTime -= animation.frameTime;
                animation.frameCurrent++;
                
                if (animation.frameCurrent == animation.frameCount)
                {
                    animation.frameCurrent = 0;
                }

                animation.frameRec = {animation.frameCurrent * animation.frameSize.x, 0, animation.frameSize.x, animation.frameSize.y};
            }
        }
    }
}