#include "DummyPlayer.h"

#include "raymath.h"

DummyPlayer::DummyPlayer(float x, float y)
{
    position = { x, y };

    reviveRange = 80.0f;

    isDowned = true;
}

void DummyPlayer::Draw()
{
    if (!isDowned)
    {
        // Dummy ฟื้นแล้ว
        DrawRectangle(
            (int)position.x - 20,
            (int)position.y - 20,
            40,
            40,
            BLUE
        );

        return;
    }

    // =========================
    // DOWNED
    // =========================

    DrawRectangle(
        (int)position.x - 20,
        (int)position.y - 20,
        40,
        40,
        RED
    );

    DrawText(
        "DOWNED",
        (int)position.x - 35,
        (int)position.y - 45,
        18,
        RED
    );
}

Vector2 DummyPlayer::GetPosition() const
{
    return position;
}

bool DummyPlayer::CanRevive(
    Vector2 playerPosition
) const
{
    if (!isDowned)
    {
        return false;
    }

    float distance = Vector2Distance(
        position,
        playerPosition
    );

    return distance <= reviveRange;
}

bool DummyPlayer::IsDowned() const
{
    return isDowned;
}

void DummyPlayer::Revive()
{
    isDowned = false;
}