#include "PlayerMovement.h"

PlayerMovement::PlayerMovement(float speed)
{
    this->speed = speed;
}

void PlayerMovement::Update(
    Vector2& position,
    int screenWidth,
    int screenHeight
)
{
    float deltaTime = GetFrameTime();

    if (IsKeyDown(KEY_W))
    {
        position.y -= speed * deltaTime;
    }

    if (IsKeyDown(KEY_S))
    {
        position.y += speed * deltaTime;
    }

    if (IsKeyDown(KEY_A))
    {
        position.x -= speed * deltaTime;
    }

    if (IsKeyDown(KEY_D))
    {
        position.x += speed * deltaTime;
    }

    const float playerSize = 40.0f;

    if (position.x < 0.0f)
    {
        position.x = 0.0f;
    }

    if (position.x > screenWidth - playerSize)
    {
        position.x = screenWidth - playerSize;
    }

    if (position.y < 0.0f)
    {
        position.y = 0.0f;
    }

    if (position.y > screenHeight - playerSize)
    {
        position.y = screenHeight - playerSize;
    }
}