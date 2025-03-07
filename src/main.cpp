#include "gui/gui_game.hpp"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define GUI_GAME_LAYOUT_IMPLEMENTATION
#include "gui/gui_game_layout.h"

#include "constants.hpp"
#include "player/entity/player.hpp"
#include "player/system/move.hpp"
#include "system/drawAnimation.hpp"
#include "system/drawRectangle.hpp"
#include "system/updateAnimFrame.hpp"

void update(entt::registry &registry, float dt)
{
	player::move(registry, dt);
	systems::updateAnimFrame(registry, dt);
}

void render(entt::registry &registry)
{
	renderer::drawAnimation(registry);
	renderer::drawRectangle(registry);
}

int main(void)
{
	// SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(constants::screenWidth, constants::screenHeight, "raylib game");
	SetTargetFPS(240);

	RenderTexture2D target = LoadRenderTexture(constants::screenWidth, constants::screenHeight);
	SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

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

		Vector2 mouse = GetMousePosition();
		Vector2 virtualMouse = {0};
		virtualMouse.x = (mouse.x - (GetScreenWidth() - (constants::screenWidth * scale)) * 0.5f) / scale;
		virtualMouse.y = (mouse.y - (GetScreenHeight() - (constants::screenHeight * scale)) * 0.5f) / scale;
		virtualMouse = Vector2Clamp(virtualMouse, (Vector2){0, 0}, (Vector2){(float) constants::screenWidth, (float) constants::screenHeight});

		SetMouseOffset(-(GetScreenWidth() - (constants::screenWidth * scale)) * 0.5f, -(GetScreenHeight() - (constants::screenHeight * scale)) * 0.5f);
		SetMouseScale(1 / scale, 1 / scale);

		BeginTextureMode(target);
		ClearBackground(GRAY);
		render(registry);

		DrawText(TextFormat("FPS: %d", GetFPS()), 0, 0, 20, LIGHTGRAY);
		GuiGameLayout(&state);
		EndTextureMode();

		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexturePro(target.texture, (Rectangle){0.0f, 0.0f, (float) target.texture.width, (float) -target.texture.height},
					   (Rectangle){(GetScreenWidth() - ((float) constants::screenWidth * scale)) * 0.5f,
								   (GetScreenHeight() - ((float) constants::screenHeight * scale)) * 0.5f, (float) constants::screenWidth * scale,
								   (float) constants::screenHeight * scale},
					   (Vector2){0, 0}, 0.0f, WHITE);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}