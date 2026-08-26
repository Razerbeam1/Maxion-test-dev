#pragma once

#include "raylib.h"

class Player;
class DummyPlayer;

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
        DummyPlayer& target
    );

    void Draw(
        Vector2 position
    );

    bool IsReviving() const;
};