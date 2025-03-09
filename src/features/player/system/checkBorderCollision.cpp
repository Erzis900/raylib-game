#include "checkBorderCollision.hpp"
#include "component/direction.hpp"
#include "component/position.hpp"
#include "player/component/collider.hpp"

namespace player
{
	void checkBorderCollision(entt::registry &registry, int screenWidth, int screenHeight)
	{
		auto view = registry.view<component::position, player::collider>();
		for (auto [player, position, collider] : view.each())
		{
			if (collider.rect.x + collider.rect.width >= screenWidth)
            {
                registry.replace<component::position>(player, screenWidth - collider.rect.width / 2, position.vec.y);
            }
            else if (collider.rect.x <= 0.f) 
            {
                registry.replace<component::position>(player, collider.rect.width / 2, position.vec.y);
            }
            if (collider.rect.y <= 0.f)
            {
                registry.replace<component::position>(player, position.vec.x, collider.rect.height / 2);
            }
			else if (collider.rect.y + collider.rect.height >= screenHeight)
            {
                registry.replace<component::position>(player, position.vec.x, screenHeight - collider.rect.height / 2);
            }
		}
	}
}  // namespace player