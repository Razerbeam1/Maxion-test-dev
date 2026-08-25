#pragma once
#include "../InteractionObject.h"

class HealItem : public InteractionObject
{
private:
    bool collected;

public:
    HealItem(float x, float y);

    bool CanInteract(Vector2 playerPosition) override;
    void Interact() override;
    void Draw() override;
};