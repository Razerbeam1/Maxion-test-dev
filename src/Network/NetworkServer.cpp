#include "NetworkServer.h"

#include <iostream>

NetworkServer::NetworkServer()
{
    server = nullptr;
}

bool NetworkServer::Start(unsigned short port)
{
    std::cout
        << "Starting ENet server on port "
        << port
        << "...\n";

    ENetAddress address{};

    if (enet_address_set_host(
        &address,
        "0.0.0.0"
    ) != 0)
    {
        std::cout
            << "Failed to set server address.\n";

        return false;
    }

    address.port = port;

    std::cout
        << "Creating ENet host...\n";

    server = enet_host_create(
        &address,
        10,
        2,
        0,
        0
    );

    if (server == nullptr)
    {
        std::cout
            << "ERROR: enet_host_create() failed.\n";

        return false;
    }

    std::cout
        << "Server started successfully.\n";

    std::cout
        << "Listening on port "
        << port
        << "\n";

    return true;
}

void NetworkServer::Update()
{
    if (server == nullptr)
    {
        return;
    }

    ENetEvent event;

    while (
        enet_host_service(
            server,
            &event,
            0
        ) > 0
    )
    {
        switch (event.type)
        {
            case ENET_EVENT_TYPE_CONNECT:

                std::cout
                    << "Client connected!\n";

                break;

            case ENET_EVENT_TYPE_DISCONNECT:

                std::cout
                    << "Client disconnected!\n";

                break;

            case ENET_EVENT_TYPE_RECEIVE:

                std::cout
                    << "Packet received.\n";

                enet_packet_destroy(
                    event.packet
                );

                break;

            default:
                break;
        }
    }
}

void NetworkServer::Stop()
{
    if (server == nullptr)
    {
        return;
    }

    enet_host_destroy(server);

    server = nullptr;

    std::cout
        << "Server stopped.\n";
}

bool NetworkServer::IsRunning() const
{
    return server != nullptr;
}