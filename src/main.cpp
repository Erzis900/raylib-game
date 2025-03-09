#include "gui/gui_game.hpp"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define GUI_GAME_LAYOUT_IMPLEMENTATION
#include "gui/gui_game_layout.h"

#include "constants.hpp"
#include "player/entity/player.hpp"
#include "player/system/move.hpp"
#include "player/system/checkBorderCollision.hpp"

#include "resources.hpp"
#include "system/animate.hpp"
#include "system/drawAnimation.hpp"
#include "system/drawRectangle.hpp"

#include "map.hpp"

void update(entt::registry &registry, float dt)
{
	player::move(registry, dt);
	player::checkBorderCollision(registry, constants::screenWidth, constants::screenHeight);
	systems::animate(registry, dt);
}

void render(entt::registry &registry)
{
	renderer::drawAnimation(registry);
	renderer::drawRectangle(registry);
}

int main(void)
{
	SetTraceLogLevel(LOG_ERROR);
	// SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(constants::screenWidth, constants::screenHeight, "raylib game");
	SetTargetFPS(constants::fps);

	Map map("assets/map/map.ldtk");
	map.initRenderTexture();

	// ToggleBorderlessWindowed();

	RenderTexture2D target = LoadRenderTexture(constants::screenWidth, constants::screenHeight);
	SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

	resources::load();

	GuiGameLayoutState state = InitGuiGameLayout();
	gui::initLogic(&state);

	entt::registry registry;
	player::createPlayer(registry);

	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		update(registry, dt);
		gui::handleLogic(&state);

		float scale = std::min(static_cast<float>(GetScreenWidth()) / constants::screenWidth, static_cast<float>(GetScreenHeight()) / constants::screenHeight);

		SetMouseOffset(-(GetScreenWidth() - (constants::screenWidth * scale)) * 0.5f, -(GetScreenHeight() - (constants::screenHeight * scale)) * 0.5f);
		SetMouseScale(1 / scale, 1 / scale);

		BeginTextureMode(target);
			ClearBackground(GRAY);
			map.drawRenderTexture();

			render(registry);

			DrawText(TextFormat("FPS: %d", GetFPS()), 0, 0, 20, LIGHTGRAY);
			GuiGameLayout(&state);
		EndTextureMode();

		BeginDrawing();
			ClearBackground(BLACK);
			Rectangle src = {0.f, 0.f, static_cast<float>(target.texture.width), static_cast<float>(-target.texture.height)};
			Rectangle dest = {(GetScreenWidth() - (static_cast<float>(constants::screenWidth) * scale)) / 2.f,
							(GetScreenHeight() - (static_cast<float>(constants::screenHeight) * scale)) / 2.f, static_cast<float>(constants::screenWidth) * scale,
							static_cast<float>(constants::screenHeight) * scale};
			DrawTexturePro(target.texture, src, dest, Vector2(0, 0), 0.f, WHITE);
		EndDrawing();
	}

	resources::unload();
	CloseWindow();

	return 0;
}