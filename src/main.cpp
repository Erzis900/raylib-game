#include "pch.hpp"
#include "player/entity/player.hpp"
#include "system/drawRectangle.hpp"
#include "player/system/move.hpp"
#include "system/drawAnimation.hpp"
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
    const int screenWidth = 1280;
    const int screenHeight = 720;
    int fps = 60;

    InitWindow(screenWidth, screenHeight, "raylib game");
    SetTargetFPS(fps);

    entt::registry registry;
    player::createPlayer(registry);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        update(registry, dt);

        BeginDrawing();
            ClearBackground(GRAY);
            render(registry);

            DrawText(TextFormat("FPS: %d", GetFPS()), 0, 0, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}