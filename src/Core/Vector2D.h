#pragma once

struct Vector2D
{
    float x = 0.0f;
    float y = 0.0f;
};

inline float DistanceSquared(const Vector2D& a, const Vector2D& b)
{
    const float dx = a.x - b.x;
    const float dy = a.y - b.y;
    return dx * dx + dy * dy;
}
