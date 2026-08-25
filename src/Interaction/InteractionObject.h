#pragma once

#include "raylib.h"

class InteractionObject
{
protected:
    Vector2 position;
    float interactionRange = 30.0f;

public:
    InteractionObject(float x, float y, float range);

    virtual ~InteractionObject() = default;

    virtual bool CanInteract(Vector2 playerPosition) = 0;
    virtual void Interact() = 0;
    virtual void Draw() = 0;
};