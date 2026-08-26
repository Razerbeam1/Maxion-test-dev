#pragma once

#include "Data/PlayerData.h"
#include "Movement/PlayerMovement.h"
#include "Health/PlayerHealth.h"
#include "Inventory/PlayerInventory.h"
#include "State/PlayerState.h"

// ข้อมูลและกฎของผู้เล่น ไม่มีโค้ดวาดภาพหรือคีย์บอร์ด
class Player
{
private:
    PlayerData data;

    PlayerMovement movement;
    PlayerHealth health;
    PlayerInventory inventory;

    PlayerLifeState state;

public:
    Player(float x = 0.0f, float y = 0.0f);

    void Move(float inputX, float inputY, float deltaTime,
              float arenaWidth, float arenaHeight, float playerSize);

    // Position
    Vector2D GetPosition() const;
    void SetPosition(Vector2D position);

    // Health
    float GetHealth() const;
    float GetMaxHealth() const;

    void TakeDamage(float damage);
    void Heal(float amount);

    // Inventory
    bool HasReviveItem() const;

    void AddReviveItem();
    bool UseReviveItem();

    // State
    PlayerLifeState GetLifeState() const;
    void Revive(float healthAmount);
    void SetDead();
};
