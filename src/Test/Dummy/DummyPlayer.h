#pragma once

#include "raylib.h"

class DummyPlayer
{
private:
    Vector2 position;

    float reviveRange;

public:
    DummyPlayer(float x, float y);

    void Draw();

    Vector2 GetPosition() const;

    bool CanRevive(Vector2 playerPosition) const;
};