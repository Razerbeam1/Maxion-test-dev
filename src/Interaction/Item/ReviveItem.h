#pragma once

#include "Item.h"

class Player;

class ReviveItem : public Item
{
public:
    ReviveItem(float x, float y);

    bool CanInteract(
        Vector2 playerPosition
    ) override;

    void Interact(
        Player& player
    ) override;

    void Draw() override;
};