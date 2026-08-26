#pragma once

#include "../Client/ClientInput.h"
#include "../Client/GameRenderer.h"
#include "../Network/NetworkClient.h"

class Game
{
public:
    Game();
    ~Game();

    bool Connect(const char* host);
    void Run();

private:
    void SendFrameInput();
    NetworkClient client;
    ClientInput input;
    GameRenderer renderer;
};
