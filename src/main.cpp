#include "pch.hpp"
#include "player/entity/player.hpp"
#include "system/drawRectangle.hpp"
#include "player/system/move.hpp"

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
        player::move(registry, dt);

        BeginDrawing();
            ClearBackground(BLACK);
            renderer::drawRectangle(registry);
            // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();


    return 0;
}