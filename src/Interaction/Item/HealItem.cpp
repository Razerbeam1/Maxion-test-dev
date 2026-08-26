#include "HealItem.h"

#include "../../Player/Player.h"
#include "raymath.h"

HealItem::HealItem(float x, float y)
    : Item(
        x,
        y,
        80.0f
    )
{
}

bool HealItem::CanInteract(
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

void HealItem::Interact(
    Player& player
)
{
    if (collected)
    {
        return;
    }

    player.AddHealItem();

    collected = true;
}

void HealItem::Draw()
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