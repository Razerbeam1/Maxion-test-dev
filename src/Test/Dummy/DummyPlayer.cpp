#include "DummyPlayer.h"

#include "raymath.h"

DummyPlayer::DummyPlayer(float x, float y)
{
    position = {x, y};

    reviveRange = 80.0f;
}

void DummyPlayer::Draw()
{
    DrawRectangle(
        (int)position.x,
        (int)position.y,
        40,
        40,
        RED
    );

    DrawText(
        "DOWNED",
        (int)position.x - 5,
        (int)position.y - 30,
        18,
        RED
    );
}

Vector2 DummyPlayer::GetPosition() const
{
    return position;
}

bool DummyPlayer::CanRevive(Vector2 playerPosition) const
{
    float distance = Vector2Distance(
        position,
        playerPosition
    );

    return distance <= reviveRange;
}