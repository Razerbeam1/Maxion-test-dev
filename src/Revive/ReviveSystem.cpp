#include "ReviveSystem.h"

#include "../Player/Player.h"
#include "raymath.h"

ReviveSystem::ReviveSystem()
{
    reviveDuration = 3.0f;
    reviveProgress = 0.0f;
    isReviving = false;
}

void ReviveSystem::Update(
    Player& player,
    Player& target
)
{
    // =========================
    // Check Revive Item
    // =========================

    if (!player.HasReviveItem())
    {
        reviveProgress = 0.0f;
        isReviving = false;

        return;
    }

    // =========================
    // Check Target State
    // =========================

    if (target.GetState() != PlayerState::Downed)
    {
        reviveProgress = 0.0f;
        isReviving = false;

        return;
    }

    // =========================
    // Check Distance
    // =========================

    float distance = Vector2Distance(
        player.GetPosition(),
        target.GetPosition()
    );

    const float reviveRange = 80.0f;

    if (distance > reviveRange)
    {
        reviveProgress = 0.0f;
        isReviving = false;

        return;
    }

    // =========================
    // Check Hold E
    // =========================

    if (!IsKeyDown(KEY_E))
    {
        reviveProgress = 0.0f;
        isReviving = false;

        return;
    }

    // =========================
    // Reviving
    // =========================

    isReviving = true;

    reviveProgress += GetFrameTime();

    // =========================
    // Complete
    // =========================

    if (reviveProgress >= reviveDuration)
    {
        reviveProgress = reviveDuration;
        isReviving = false;

        target.Revive();
        player.UseReviveItem();
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