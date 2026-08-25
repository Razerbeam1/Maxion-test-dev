#include "Player.h"

Player::Player(float x, float y)
{
    position = {x, y};
    speed = 250.0f;
}

void Player::Update(int screenWidth, int screenHeight)
{
    float deltaTime = GetFrameTime();

    // Movement
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

    // Player size
    const float playerSize = 40.0f;

    // Boundary X
    if (position.x < 0.0f)
    {
        position.x = 0.0f;
    }

    if (position.x > screenWidth - playerSize)
    {
        position.x = screenWidth - playerSize;
    }

    // Boundary Y
    if (position.y < 0.0f)
    {
        position.y = 0.0f;
    }

    if (position.y > screenHeight - playerSize)
    {
        position.y = screenHeight - playerSize;
    }
}

void Player::Draw()
{
    DrawRectangle(
        (int)position.x,
        (int)position.y,
        40,
        40,
        BLUE
    );
}
Vector2 Player::GetPosition() const
{
    return position;
}