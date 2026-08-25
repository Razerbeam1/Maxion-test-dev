#include "InteractionObject.h"

InteractionObject::InteractionObject(
    float x,
    float y,
    float range
)
{
    position = {x, y};
    interactionRange = range;
}