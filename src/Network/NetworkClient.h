#pragma once
#define Rectangle Win32Rectangle
#define CloseWindow Win32CloseWindow
#define ShowCursor Win32ShowCursor
#define LoadImage Win32LoadImage
#define DrawText Win32DrawText
#define DrawTextEx Win32DrawTextEx
#define PlaySound Win32PlaySound
#include <enet/enet.h>
#undef Rectangle
#undef CloseWindow
#undef ShowCursor
#undef LoadImage
#undef DrawText
#undef DrawTextEx
#undef PlaySound
#include "NetworkPacket.h"
class NetworkClient { public: bool Start();bool Connect(const char* host,unsigned short port);void Update();void Stop();bool IsConnected()const;void SendInput(float x,float y,bool collect,bool revive,bool attack,int attackTargetId);int GetPlayerId()const;bool HasSnapshot()const;const NetworkMatchSnapshot& GetSnapshot()const;private: ENetHost* client=nullptr;ENetPeer* server=nullptr;int playerId=-1;unsigned int sequence=0;bool hasSnapshot=false;NetworkMatchSnapshot snapshot{};};
