#pragma once

#include "../Network/NetworkManager.h"

class Game
{
private:
    NetworkManager* network;

    bool hostMode;

public:
    Game();
    ~Game();

    void StartHost();
    void StartClient(const char* host);

    void Run();
};