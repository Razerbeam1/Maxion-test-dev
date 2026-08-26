#pragma once

#include "raylib.h"

class HUD
{
public:
    void DrawHealth(
        float health,
        float maxHealth
    );

    void DrawInventory(
        bool hasReviveItem
    );
};