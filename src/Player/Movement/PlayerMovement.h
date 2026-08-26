#pragma once

#include "../../Core/Vector2D.h"

class PlayerMovement
{
private:
    float speed;

public:
    PlayerMovement(float speed = 250.0f);

    void Move(Vector2D& position, float inputX, float inputY, float deltaTime,
              float arenaWidth, float arenaHeight, float playerSize) const;
};
