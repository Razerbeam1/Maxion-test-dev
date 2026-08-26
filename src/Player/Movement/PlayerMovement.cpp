#include "PlayerMovement.h"

PlayerMovement::PlayerMovement(float speed)
{
    this->speed = speed;
}

void PlayerMovement::Move(Vector2D& position, float inputX, float inputY, float deltaTime,
                          float arenaWidth, float arenaHeight, float playerSize) const
{
    position.x += inputX * speed * deltaTime;
    position.y += inputY * speed * deltaTime;
    if (position.x < 0.0f) position.x = 0.0f;
    if (position.x > arenaWidth - playerSize) position.x = arenaWidth - playerSize;
    if (position.y < 0.0f) position.y = 0.0f;
    if (position.y > arenaHeight - playerSize) position.y = arenaHeight - playerSize;
}
