#include "PlayerInventory.h"

PlayerInventory::PlayerInventory()
{
    hasHealItem = false;
}

bool PlayerInventory::HasHealItem() const
{
    return hasHealItem;
}

void PlayerInventory::AddHealItem()
{
    hasHealItem = true;
}

void PlayerInventory::RemoveHealItem()
{
    hasHealItem = false;
}