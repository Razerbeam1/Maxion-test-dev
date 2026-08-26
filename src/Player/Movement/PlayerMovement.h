#pragma once

#include "raylib.h"

class PlayerMovement
{
private:
    float speed;

public:
    PlayerMovement(float speed = 250.0f);

    void Update(
        Vector2& position,
        int screenWidth,
        int screenHeight
    );
};