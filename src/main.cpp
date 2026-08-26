#include <iostream>

#include "Game/Game.h"

int main()
{
    std::cout << "=========================\n";
    std::cout << "       TEST-DEV\n";
    std::cout << "=========================\n";
    std::cout << "1. Host\n";
    std::cout << "2. Client\n";
    std::cout << "Select: ";

    int choice;
    std::cin >> choice;

    Game game;

    if (choice == 1)
    {
        game.StartHost();
    }
    else if (choice == 2)
    {
        game.StartClient(
            "127.0.0.1"
        );
    }
    else
    {
        std::cout << "Invalid choice.\n";
        return 1;
    }

    game.Run();

    return 0;
}