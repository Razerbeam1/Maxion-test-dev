#include "InteractionObject.h"

InteractionObject::InteractionObject(
    float x,
    float y,
    float interactionRange
)
{
    position = {x, y};
    this->interactionRange = interactionRange;
}