#pragma once

#include "raylib.h"

class Player;

class ReviveSystem
{
private:
    float reviveDuration;
    float reviveProgress;

    bool isReviving;

public:
    ReviveSystem();

    void Update(
        Player& player,
        Player& target
    );

    void Draw(
        Vector2 position
    );

    bool IsReviving() const;
};