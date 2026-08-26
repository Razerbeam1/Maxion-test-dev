#pragma once

#include "raylib.h"

#include "Data/PlayerData.h"
#include "Movement/PlayerMovement.h"
#include "Health/PlayerHealth.h"
#include "Inventory/PlayerInventory.h"
#include "State/PlayerState.h"

class Player
{
private:
    PlayerData data;

    PlayerMovement movement;
    PlayerHealth health;
    PlayerInventory inventory;

    PlayerState state;

public:
    Player(float x, float y);

    void Update(
        int screenWidth,
        int screenHeight
    );

    void Draw();

    // Position
    Vector2 GetPosition() const;

    // Health
    float GetHealth() const;
    float GetMaxHealth() const;

    void TakeDamage(float damage);
    void Heal(float amount);

    // Inventory
    bool HasHealItem() const;

    void AddHealItem();
    void UseHealItem();

    // State
    PlayerState GetState() const;
};