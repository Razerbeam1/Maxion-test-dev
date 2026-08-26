#include "Game/Game.h"
#include <iostream>
int main(int argc,char** argv){const char* host=argc>1?argv[1]:"127.0.0.1";Game game;if(!game.Connect(host)){std::cerr<<"Could not connect to "<<host<<":27015\n";return 1;}game.Run();return 0;}
