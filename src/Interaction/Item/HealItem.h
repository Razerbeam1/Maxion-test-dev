#pragma once

#include "Item.h"

class Player;

class HealItem : public Item
{
public:
    HealItem(float x, float y);

    bool CanInteract(
        Vector2 playerPosition
    ) override;

    void Interact(
        Player& player
    ) override;

    void Draw() override;
};