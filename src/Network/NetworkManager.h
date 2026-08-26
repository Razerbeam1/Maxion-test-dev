#pragma once

#include "NetworkServer.h"
#include "NetworkClient.h"

class NetworkManager
{
private:
    NetworkServer server;
    NetworkClient client;

    bool isHost;

public:
    NetworkManager();
    ~NetworkManager();

    bool StartHost(unsigned short port);

    bool StartClient(
        const char* host,
        unsigned short port
    );

    void Update();

    void Stop();

    bool IsHost() const;

    bool IsConnected() const;
};