#include "NetworkClient.h"

#include <iostream>

int main()
{
    if (enet_initialize() != 0)
    {
        std::cout
            << "Failed to initialize ENet.\n";

        return 1;
    }

    NetworkClient client;

    if (!client.Start())
    {
        enet_deinitialize();

        return 1;
    }

    if (!client.Connect(
        "127.0.0.1",
        27015
    ))
    {
        client.Stop();

        enet_deinitialize();

        return 1;
    }

    std::cout
        << "Client connected successfully!\n";

    std::cout
        << "Press ENTER to stop client...\n";

    std::cin.get();

    client.Stop();

    enet_deinitialize();

    return 0;
}