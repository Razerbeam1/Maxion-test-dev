#include "Game.h"
#include "raylib.h"
#include <enet/enet.h>

Game::Game()
{
    enet_initialize();
}

Game::~Game()
{
    client.Stop();
    enet_deinitialize();
}

bool Game::Connect(const char* host)
{
    return client.Start() && client.Connect(host, 27015);
}

void Game::Run()
{
    InitWindow(1280, 720, "Co-op Arena Client");
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        client.Update();
        SendFrameInput();
        renderer.Draw(client.HasSnapshot() ? &client.GetSnapshot() : nullptr,
                      client.IsConnected(), client.GetPlayerId());
    }
    CloseWindow();
}

void Game::SendFrameInput()
{
    const ClientInputState frameInput = input.Read(client.HasSnapshot() ? &client.GetSnapshot() : nullptr,
                                                   client.GetPlayerId());
    client.SendInput(frameInput.moveX, frameInput.moveY, frameInput.collectPressed,
                     frameInput.reviveHeld, frameInput.attackPressed, frameInput.attackTargetId);
}
