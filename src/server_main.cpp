#include "Network/NetworkServer.h"
#include <enet/enet.h>
#include <chrono>
#include <iostream>
#include <thread>
int main(){if(enet_initialize()!=0){std::cerr<<"ENet initialization failed\n";return 1;}NetworkServer server;if(!server.Start(27015)){std::cerr<<"Could not bind port 27015\n";enet_deinitialize();return 1;}auto previous=std::chrono::steady_clock::now();while(true){auto now=std::chrono::steady_clock::now();std::chrono::duration<float> elapsed=now-previous;previous=now;server.Update(elapsed.count());std::this_thread::sleep_for(std::chrono::milliseconds(16));}}
