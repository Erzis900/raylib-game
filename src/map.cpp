#include "map.hpp"
#include "constants.hpp"
#include "component/collider.hpp"
#include "component/color.hpp"

Map::Map(const std::string &projectPath)
{
	ldtkProject.loadFromFile(projectPath);
	scale = 4.f;
}

entt::entity Map::createCollider(entt::registry &registry, Rectangle collider)
{
	auto entity = registry.create();
	registry.emplace<component::collider>(entity, collider, RED);

	return entity;
}

void Map::initRenderTexture(entt::registry &registry)
{
	const auto &world = ldtkProject.getWorld();
	const auto &level = world.getLevel("Level_0");

	renderTexture = LoadRenderTexture(constants::screenWidth, constants::screenHeight);

	BeginTextureMode(renderTexture);
	ClearBackground(GRAY);
	for (auto it = level.allLayers().rbegin(); it != level.allLayers().rend(); ++it)
	{
		const auto &layer = *it;

		if (layer.getType() == ldtk::LayerType::Tiles)
		{
			texture = LoadTexture(("assets/map/" + layer.getTileset().path).c_str());
			for (const auto &tile : layer.allTiles())
			{
				const auto &position = tile.getPosition();
				const auto &texture_rect = tile.getTextureRect();
				Vector2 dest = {
					static_cast<float>(position.x),
					static_cast<float>(position.y),
				};
				Rectangle src = {static_cast<float>(texture_rect.x), static_cast<float>(texture_rect.y),
								 static_cast<float>(texture_rect.width) * (tile.flipX ? -1.0f : 1.0f),
								 static_cast<float>(texture_rect.height) * (tile.flipY ? -1.0f : 1.0f)};
				DrawTextureRec(texture, src, dest, WHITE);
			}
		}
		else
		{
			auto gridSize = layer.getGridSize();
			int width = gridSize.x;
			int height = gridSize.y;

			float colliderSize = 64.f;
            int collision = 1;
            
			for (int row = 0; row < width; row++)
			{
				for (int col = 0; col < height; col++)
				{
					int value = layer.getIntGridVal(row, col).value;

                    if (value == collision)
                    {
						// fmt::print("Coll at ({}, {}): {}\n", row, col, value);
						Rectangle mapCollider = {static_cast<float>(row * colliderSize), static_cast<float>(col * colliderSize), colliderSize, colliderSize};
						createCollider(registry, mapCollider);
                    }
				}
			}
		}
	}
	EndTextureMode();
}

void Map::drawRenderTexture()
{
	Rectangle src = {0, 0, static_cast<float>(renderTexture.texture.width), -static_cast<float>(renderTexture.texture.height)};
	Rectangle dest = {0, 0, static_cast<float>(renderTexture.texture.width) * scale, static_cast<float>(renderTexture.texture.height) * scale};
	DrawTexturePro(renderTexture.texture, src, dest, {0}, .0f, WHITE);
}