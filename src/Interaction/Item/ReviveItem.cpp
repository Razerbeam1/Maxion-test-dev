#include "ReviveItem.h"

#include "../../Player/Player.h"
#include "raymath.h"

ReviveItem::ReviveItem(float x, float y)
    : Item(
        x,
        y,
        80.0f
    )
{
}

bool ReviveItem::CanInteract(
    Vector2 playerPosition
)
{
    if (collected)
    {
        return false;
    }

    float distance = Vector2Distance(
        position,
        playerPosition
    );

    return distance <= interactionRange;
}

void ReviveItem::Interact(
    Player& player
)
{
    if (collected)
    {
        return;
    }

    player.AddReviveItem();

    collected = true;
}

void ReviveItem::Draw()
{
    if (collected)
    {
        return;
    }

    DrawCircle(
        (int)position.x,
        (int)position.y,
        15,
        GREEN
    );
}