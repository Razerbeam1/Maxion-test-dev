#pragma once
#include "../Network/NetworkPacket.h"

struct ClientInputState
{
    float moveX = 0.0f;
    float moveY = 0.0f;
    bool collectPressed = false;
    bool reviveHeld = false;
    bool attackPressed = false;
    int attackTargetId = -1;
};

// แปลงคีย์บอร์ดและเมาส์เป็นคำสั่งเพื่อส่งไป server
class ClientInput
{
public:
    ClientInputState Read(const NetworkMatchSnapshot* snapshot, int localPlayerId) const;
};
