#include "raylib.h"
#include "Player/Player.h"

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetTargetFPS(60);
    InitWindow(
        screenWidth,
        screenHeight,
        "Test-dev"
    );
    Player player(380, 280);

    while (!WindowShouldClose())
    {
        // UPDATE
        player.Update(screenWidth, screenHeight);

        // DRAW
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(
            "WASD - Move",
            20,
            20,
            20,
            BLACK
        );

        DrawRectangleLines(
            0,
            0,
            screenWidth,
            screenHeight,
            BLACK
        );

        player.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}