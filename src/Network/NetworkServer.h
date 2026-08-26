#pragma once

// ENet บน Windows ดึง Windows API เข้ามา
// ซึ่งมีชื่อชนกับ Raylib เช่น Rectangle, DrawText, CloseWindow
#define Rectangle Win32Rectangle
#define CloseWindow Win32CloseWindow
#define ShowCursor Win32ShowCursor
#define LoadImage Win32LoadImage
#define DrawText Win32DrawText
#define DrawTextEx Win32DrawTextEx
#define PlaySound Win32PlaySound

#include <enet/enet.h>

// คืนชื่อเดิมหลังจาก include ENet
#undef Rectangle
#undef CloseWindow
#undef ShowCursor
#undef LoadImage
#undef DrawText
#undef DrawTextEx
#undef PlaySound


class NetworkServer
{
private:
    ENetHost* server;

public:
    NetworkServer();

    bool Start(unsigned short port);

    void Update();

    void Stop();

    bool IsRunning() const;
};