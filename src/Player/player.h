#pragma once

#include "raylib.h"

class Player
{
private:
    Vector2 position;
    float speed;

public:
    Player(float x, float y);

    void Update(int screenWidth, int screenHeight);
    void Draw();

    Vector2 GetPosition() const;
};