#include "NetworkManager.h"

#include <iostream>
#include <enet/enet.h>

NetworkManager::NetworkManager()
{
    isHost = false;

    if (enet_initialize() != 0)
    {
        std::cout
            << "Failed to initialize ENet.\n";
    }
    else
    {
        std::cout
            << "ENet initialized.\n";
    }
}

NetworkManager::~NetworkManager()
{
    Stop();

    enet_deinitialize();
}

bool NetworkManager::StartHost(unsigned short port)
{
    std::cout
        << "Starting host...\n";

    // =========================
    // START SERVER
    // =========================

    if (!server.Start(port))
    {
        std::cout
            << "Failed to start server.\n";

        return false;
    }

    // Host ไม่ต้องสร้าง Client
    isHost = true;

    std::cout
        << "Host started successfully.\n";

    return true;
}

bool NetworkManager::StartClient(
    const char* host,
    unsigned short port
)
{
    std::cout
        << "Starting client...\n";

    // =========================
    // START CLIENT
    // =========================

    if (!client.Start())
    {
        std::cout
            << "Failed to start client.\n";

        return false;
    }

    // =========================
    // CONNECT
    // =========================

    if (!client.Connect(
        host,
        port
    ))
    {
        std::cout
            << "Failed to connect to server.\n";

        client.Stop();

        return false;
    }

    isHost = false;

    std::cout
        << "Client started successfully.\n";

    return true;
}

void NetworkManager::Update()
{
    // Host
    if (isHost)
    {
        server.Update();
    }

    // Client
    client.Update();
}

void NetworkManager::Stop()
{
    client.Stop();

    if (isHost)
    {
        server.Stop();
    }

    isHost = false;
}

bool NetworkManager::IsHost() const
{
    return isHost;
}

bool NetworkManager::IsConnected() const
{
    // Host = server กำลังทำงาน
    if (isHost)
    {
        return server.IsRunning();
    }

    // Client = เชื่อมต่อ server อยู่
    return client.IsConnected();
}