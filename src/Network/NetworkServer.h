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
#include "../Game/GameWorld.h"
// เซิร์ฟเวอร์ผู้ตัดสิน: รับคำสั่ง อัปเดตโลก และกระจาย snapshot
class NetworkServer { public: NetworkServer(); bool Start(unsigned short port); void Update(float deltaTime); void Stop(); bool IsRunning()const; const GameWorld& GetWorld()const; private: void SendSnapshot(); void SendAssignment(ENetPeer* peer,int playerId); ENetHost* server=nullptr; ENetPeer* peers[GameWorld::PlayerCount]{}; GameWorld world; };
