#include "checkMapCollision.hpp"
#include "component/collider.hpp"
#include "component/position.hpp"
#include "player/component/isPlayer.hpp"


namespace player
{
	void checkMapCollision(entt::registry &registry)
	{
		auto playerView = registry.view<player::isPlayer, component::collider, component::position>();
		for (auto [player, playerCollider, playerPosition] : playerView.each())
		{
			auto view = registry.view<component::collider>();
			for (auto [entity, collider] : view.each())
			{
				if (entity == player) continue;

				if (CheckCollisionRecs(playerCollider.rect, collider.rect))
				{
					float overlapX = std::min(playerCollider.rect.x + playerCollider.rect.width - collider.rect.x,
											  collider.rect.x + collider.rect.width - playerCollider.rect.x);
					float overlapY = std::min(playerCollider.rect.y + playerCollider.rect.height - collider.rect.y,
											  collider.rect.y + collider.rect.height - playerCollider.rect.y);

					if (overlapX < overlapY)
					{
						if (playerCollider.rect.x < collider.rect.x)
						{
							playerPosition.vec.x = collider.rect.x - playerCollider.rect.width / 2;
						}
						else
						{
							playerPosition.vec.x = collider.rect.x + collider.rect.width + playerCollider.rect.width / 2;
						}
					}
					else
					{
						if (playerCollider.rect.y < collider.rect.y)
						{
							playerPosition.vec.y = collider.rect.y - playerCollider.rect.height / 2;
						}
						else
						{
							playerPosition.vec.y = collider.rect.y + collider.rect.height + playerCollider.rect.height / 2;
						}
					}
				}
			}
		}
	}
}  // namespace player