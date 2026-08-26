#include "NetworkClient.h"

#include <iostream>

NetworkClient::NetworkClient()
{
    client = nullptr;
    server = nullptr;
}

bool NetworkClient::Start()
{
    client = enet_host_create(
        nullptr,
        1,
        2,
        0,
        0
    );

    if (client == nullptr)
    {
        std::cout
            << "Failed to create client.\n";

        return false;
    }

    std::cout
        << "Client started.\n";

    return true;
}

bool NetworkClient::Connect(
    const char* host,
    unsigned short port
)
{
    if (client == nullptr)
    {
        return false;
    }

    ENetAddress address{};

    if (enet_address_set_host(
        &address,
        host
    ) != 0)
    {
        std::cout
            << "Failed to resolve host.\n";

        return false;
    }

    address.port = port;

    server = enet_host_connect(
        client,
        &address,
        2,
        0
    );

    if (server == nullptr)
    {
        std::cout
            << "Failed to create connection.\n";

        return false;
    }

    ENetEvent event;

    if (
        enet_host_service(
            client,
            &event,
            5000
        ) > 0 &&
        event.type == ENET_EVENT_TYPE_CONNECT
    )
    {
        std::cout
            << "Connected to server!\n";

        return true;
    }

    std::cout
        << "Connection timeout.\n";

    server = nullptr;

    return false;
}

void NetworkClient::Update()
{
    if (client == nullptr)
    {
        return;
    }

    ENetEvent event;

    while (
        enet_host_service(
            client,
            &event,
            0
        ) > 0
    )
    {
        switch (event.type)
        {
            case ENET_EVENT_TYPE_CONNECT:

                std::cout
                    << "Connected!\n";

                break;

            case ENET_EVENT_TYPE_DISCONNECT:

                std::cout
                    << "Disconnected!\n";

                server = nullptr;

                break;

            case ENET_EVENT_TYPE_RECEIVE:

                enet_packet_destroy(
                    event.packet
                );

                break;

            default:
                break;
        }
    }
}

void NetworkClient::Stop()
{
    if (client == nullptr)
    {
        return;
    }

    if (server != nullptr)
    {
        enet_peer_disconnect(
            server,
            0
        );
    }

    enet_host_destroy(client);

    client = nullptr;
    server = nullptr;

    std::cout
        << "Client stopped.\n";
}

bool NetworkClient::IsConnected() const
{
    return server != nullptr;
}