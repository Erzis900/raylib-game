#include "player.hpp"
#include "component/position.hpp"
#include "component/size.hpp"
#include "component/color.hpp"
#include "component/speed.hpp"
#include "component/direction.hpp"
#include "player/component/isPlayer.hpp"
#include "player/component/state.hpp"
#include "component/animation.hpp"
#include "player/component/facing.hpp"
#include "resources.hpp"

namespace player
{
    entt::entity createPlayer(entt::registry &registry)
    {
        entt::entity player = registry.create();

        float scale = 4.f;
        Vector2 frameSize = {64.f, 64.f};

        registry.emplace<player::isPlayer>(player);
        registry.emplace<component::position>(player, 50.f, 50.f);
        registry.emplace<component::size>(player, frameSize.x * scale, frameSize.y * scale);
        registry.emplace<component::speed>(player, 200.f);
        registry.emplace<component::direction>(player, 0.f, 0.f);
        registry.emplace<component::color>(player, GREEN);
        registry.emplace<player::state>(player, state::idle);
        registry.emplace<player::facing>(player, facing::down);

        float frameTime = 0.1f;
        int frameCount = 4;
        bool loop = true;
        Rectangle frameRec = {0, 0, frameSize.x, frameSize.y};

        registry.emplace<component::animation>(player, resources::idlewalk, frameSize, frameRec, frameTime, frameCount, 0, 0, scale, loop);

        return player;
    }
}