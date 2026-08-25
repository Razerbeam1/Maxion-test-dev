#pragma once

#include "raylib.h"

class Player
{
private:
    Vector2 position;
    float speed;

    // Health
    float health;
    float maxHealth;

    // Inventory
    bool hasHealItem;

public:
    Player(float x, float y);

    void Update(int screenWidth, int screenHeight);
    void Draw();

    Vector2 GetPosition() const;

    // Health
    float GetHealth() const;
    float GetMaxHealth() const;

    // Inventory
    bool HasHealItem() const;

    void AddHealItem();
};