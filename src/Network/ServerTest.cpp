#include "NetworkServer.h"

#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    if (enet_initialize() != 0)
    {
        std::cout
            << "Failed to initialize ENet.\n";

        return 1;
    }

    NetworkServer server;

    if (!server.Start(27015))
    {
        enet_deinitialize();

        return 1;
    }

    std::cout
        << "Server is running...\n";

    std::cout
        << "Press Ctrl+C to stop.\n";

    while (true)
    {
        server.Update();

        std::this_thread::sleep_for(
            std::chrono::milliseconds(10)
        );
    }

    server.Stop();

    enet_deinitialize();

    return 0;
}