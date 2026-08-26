#include "Game.h"

#include "raylib.h"

#include "../Player/Player.h"
#include "../Interaction/Item/ReviveItem.h"
#include "../UI/HUD.h"

Game::Game()
{
    network = new NetworkManager();
    hostMode = false;
}

Game::~Game()
{
    delete network;
    network = nullptr;
}

void Game::StartHost()
{
    hostMode = true;

    if (!network->StartHost(27015))
    {
        TraceLog(
            LOG_ERROR,
            "Failed to start host."
        );
    }
}

void Game::StartClient(const char* host)
{
    hostMode = false;

    if (!network->StartClient(
        host,
        27015
    ))
    {
        TraceLog(
            LOG_ERROR,
            "Failed to start client."
        );
    }
}


void Game::Run()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(
        screenWidth,
        screenHeight,
        "Test-dev"
    );

    SetTargetFPS(60);


    // =========================
    // NETWORK
    // =========================

    if (!network->StartHost(27015))
    {
        TraceLog(
            LOG_ERROR,
            "Failed to start host."
        );
    }


    // =========================
    // RANDOM SEED
    // =========================

    SetRandomSeed(
        (unsigned int)GetTime()
    );


    // =========================
    // PLAYER
    // =========================

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


    // =========================
    // REVIVE ITEM
    // =========================

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


    // =========================
    // GAME LOOP
    // =========================

    while (!WindowShouldClose())
    {
        network->Update();


        player.Update(
            screenWidth,
            screenHeight
        );


        // =========================
        // COLLECT REVIVE ITEM
        // =========================

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


        // =========================
        // INTERACTION UI
        // =========================

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


        // =========================
        // HUD
        // =========================

        hud.DrawHealth(
            player.GetHealth(),
            player.GetMaxHealth()
        );

        hud.DrawInventory(
            player.HasReviveItem()
        );


        // =========================
        // NETWORK STATUS
        // =========================

        if (network->IsConnected())
        {
            DrawText(
                "Network: Connected",
                20,
                220,
                20,
                GREEN
            );
        }
        else
        {
            DrawText(
                "Network: Disconnected",
                20,
                220,
                20,
                RED
            );
        }


        EndDrawing();
    }


    // =========================
    // SHUTDOWN
    // =========================

    network->Stop();

    CloseWindow();
}