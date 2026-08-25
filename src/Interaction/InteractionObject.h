#pragma once

#include "raylib.h"

class Player;

class InteractionObject
{
protected:
    Vector2 position;
    float interactionRange;

public:
    InteractionObject(
        float x,
        float y,
        float interactionRange
    );

    virtual bool CanInteract(Vector2 playerPosition) = 0;

    virtual void Interact(Player& player) = 0;

    virtual void Draw() = 0;

    virtual ~InteractionObject() = default;
};