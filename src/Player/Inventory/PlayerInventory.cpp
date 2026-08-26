#include "PlayerInventory.h"

PlayerInventory::PlayerInventory()
{
    hasReviveItem = false;
}

bool PlayerInventory::HasReviveItem() const
{
    return hasReviveItem;
}

void PlayerInventory::AddReviveItem()
{
    hasReviveItem = true;
}

void PlayerInventory::RemoveReviveItem()
{
    hasReviveItem = false;
}