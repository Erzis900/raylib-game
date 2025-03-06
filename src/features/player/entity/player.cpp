#include "player.hpp"
#include "component/position.hpp"
#include "component/size.hpp"
#include "component/color.hpp"
#include "component/speed.hpp"
#include "../component/isPlayer.hpp"

namespace player
{
    entt::entity createPlayer(entt::registry &registry)
    {
        entt::entity player = registry.create();

        registry.emplace<player::isPlayer>(player);
        registry.emplace<component::position>(player, 50.f, 50.f);
        registry.emplace<component::size>(player, 50, 50);
        registry.emplace<component::speed>(player, 200.f);
        registry.emplace<component::color>(player, GREEN);

        return player;
    }
}