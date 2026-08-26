#include "raylib.h"

#include "Player/Player.h"
#include "Interaction/Item/ReviveItem.h"
#include "UI/HUD.h"

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(
        screenWidth,
        screenHeight,
        "Test-dev"
    );

    SetTargetFPS(60);

    SetRandomSeed(
        (unsigned int)GetTime()
    );

    float playerX =
        (float)GetRandomValue(
            0,
            screenWidth - 40
        );

    float playerY =
        (float)GetRandomValue(
            0,
            screenHeight - 40
        );

    Player player(
        playerX,
        playerY
    );

    float itemX =
        (float)GetRandomValue(
            15,
            screenWidth - 15
        );

    float itemY =
        (float)GetRandomValue(
            15,
            screenHeight - 15
        );

    ReviveItem reviveItem(itemX, itemY);

    HUD hud;

    while (!WindowShouldClose())
    {
        // UPDATE

        player.Update(
            screenWidth,
            screenHeight
        );

        if (
            reviveItem.CanInteract(
                player.GetPosition()
            )
        )
        {
            if (IsKeyPressed(KEY_E))
            {
                reviveItem.Interact(
                    player
                );
            }
        }

        // DRAW

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangleLines(
            0,
            0,
            screenWidth,
            screenHeight,
            BLACK
        );

        reviveItem.Draw();

        player.Draw();

        if (
            reviveItem.CanInteract(
                player.GetPosition()
            )
        )
        {
            DrawText(
                "[E] Collect",
                (int)itemX - 45,
                (int)itemY - 40,
                20,
                BLACK
            );
        }

        hud.DrawHealth(
            player.GetHealth(),
            player.GetMaxHealth()
        );

        hud.DrawInventory(
            player.HasReviveItem()
        );

        EndDrawing();
    }

    CloseWindow();

    return 0;
}