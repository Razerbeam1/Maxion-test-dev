#include "raylib.h"

#include "Player/Player.h"
#include "Interaction/Item/ReviveItem.h"
#include "UI/HUD.h"
#include "Test/Dummy/DummyPlayer.h"

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

    // Random seed
    SetRandomSeed(
        (unsigned int)GetTime()
    );

    // Random Player position
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
    DummyPlayer dummy(
        700,
        400
    );

    

    // Random Revive Item position
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

    ReviveItem reviveItem(
        itemX,
        itemY
    );

    HUD hud;

    while (!WindowShouldClose())
    {
        // =========================
        // UPDATE
        // =========================

        player.Update(
            screenWidth,
            screenHeight
        );

        // Collect Revive Item
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

        // =========================
        // DRAW
        // =========================

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
        dummy.Draw();

        if (dummy.CanRevive(player.GetPosition()))
        {
            DrawText(
            "[Hold E] Revive",
            (int)dummy.GetPosition().x - 35,
            (int)dummy.GetPosition().y + 50,
            20,
            BLACK
        );
        }

        // Interaction UI
        if (
            reviveItem.CanInteract(
                player.GetPosition()
            )
        )
        {
            DrawText(
                "[E] Collect Revive Item",
                (int)itemX - 90,
                (int)itemY - 40,
                20,
                BLACK
            );
        }

        // HUD
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