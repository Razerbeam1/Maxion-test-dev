#pragma once

#include "../InteractionObject.h"

class Item : public InteractionObject
{
protected:
    bool collected;

public:
    Item(
        float x,
        float y,
        float interactionRange
    )
        : InteractionObject(
            x,
            y,
            interactionRange
        )
    {
        collected = false;
    }
};