#include "raylib.h"

int main()
{
    InitWindow(800, 600, "Raylib Test");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Test - DEV MAXION", 300, 280, 30, BLUE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}