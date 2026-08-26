#include "ClientInput.h"
#include "raylib.h"

ClientInputState ClientInput::Read(const NetworkMatchSnapshot* snapshot, int localPlayerId) const
{
    ClientInputState input;
    input.moveX = static_cast<float>((IsKeyDown(KEY_D)) - (IsKeyDown(KEY_A)));
    input.moveY = static_cast<float>((IsKeyDown(KEY_S)) - (IsKeyDown(KEY_W)));
    input.collectPressed = IsKeyPressed(KEY_E);
    // E เดียวกัน: กดครั้งเดียวเพื่อเก็บ และกดค้างเพื่อชุบ
    input.reviveHeld = IsKeyDown(KEY_E);

    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || snapshot == nullptr) return input;
    Vector2 mouse = GetMousePosition();
    // แปลงพิกัดหน้าจอให้ตรงกับพิกัดสนามของ server
    mouse.x -= 40.0f;
    mouse.y -= 110.0f;
    for (const NetworkPlayerSnapshot& player : snapshot->players)
    {
        if (!player.connected || player.playerId == localPlayerId) continue;
        if (CheckCollisionPointRec(mouse, {player.x, player.y, 40.0f, 40.0f}))
        {
            input.attackPressed = true;
            input.attackTargetId = player.playerId;
            break;
        }
    }
    return input;
}
