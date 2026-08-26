#include "ReviveSystem.h"

#include "../Player/Player.h"
#include "../Test/Dummy/DummyPlayer.h"

ReviveSystem::ReviveSystem()
{
    reviveDuration = 3.0f;
    reviveProgress = 0.0f;
    isReviving = false;
}

void ReviveSystem::Update(
    Player& player,
    DummyPlayer& target
)
{
    // Player ไม่อยู่ในระยะ
    if (!target.CanRevive(player.GetPosition()))
    {
        reviveProgress = 0.0f;
        isReviving = false;

        return;
    }

    // อยู่ในระยะ แต่ไม่ได้กด E
    if (!IsKeyDown(KEY_E))
    {
        reviveProgress = 0.0f;
        isReviving = false;

        return;
    }

    // เริ่ม Revive
    isReviving = true;

    float deltaTime = GetFrameTime();

    reviveProgress += deltaTime;

    // ป้องกันค่าเกิน 3 วินาที
    if (reviveProgress > reviveDuration)
    {
        reviveProgress = reviveDuration;
    }
}

void ReviveSystem::Draw(Vector2 position)
{
    if (!isReviving)
    {
        return;
    }

    // =========================
    // Progress Bar Background
    // =========================

    DrawRectangle(
        (int)position.x - 50,
        (int)position.y,
        100,
        15,
        LIGHTGRAY
    );

    // =========================
    // Progress
    // =========================

    float progressPercent =
        reviveProgress / reviveDuration;

    DrawRectangle(
        (int)position.x - 50,
        (int)position.y,
        (int)(100 * progressPercent),
        15,
        GREEN
    );

    // =========================
    // Border
    // =========================

    DrawRectangleLines(
        (int)position.x - 50,
        (int)position.y,
        100,
        15,
        BLACK
    );

    // =========================
    // Text
    // =========================

    DrawText(
        "Reviving...",
        (int)position.x - 45,
        (int)position.y - 25,
        16,
        BLACK
    );
}

bool ReviveSystem::IsReviving() const
{
    return isReviving;
}