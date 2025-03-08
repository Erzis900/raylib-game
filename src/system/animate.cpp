#include "animate.hpp"
#include "component/animation.hpp"
#include "player/component/state.hpp"

namespace systems
{
    void animate(entt::registry &registry, float dt)
    {
        auto view = registry.view<component::animation, player::state>();
        for (auto [entity, animation, state] : view.each())
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

                animation.frameRec = {animation.frameCurrent * animation.frameSize.x, static_cast<float>(state.currentState) * animation.frameSize.y, animation.frameSize.x, animation.frameSize.y};
            }
        }
    }
}