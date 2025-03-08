#include "map.hpp"
#include "constants.hpp"

Map::Map(const std::string &projectPath)
{
	ldtkProject.loadFromFile(projectPath);
	scale = 4.f;
}

void Map::initRenderTexture()
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

            int collision = 1;

            
			for (int row = 0; row < height; row++)
			{
				for (int col = 0; col < width; col++)
				{
					int value = layer.getIntGridVal(row, col).value;
                    if (value == collision)
                    {
                        fmt::print("Coll at ({}, {}): {}\n", row, col, value);
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