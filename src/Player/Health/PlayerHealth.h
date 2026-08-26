#pragma once

class PlayerHealth
{
private:
    float health;
    float maxHealth;

public:
    PlayerHealth(float maxHealth = 100.0f);

    float GetHealth() const;
    float GetMaxHealth() const;

    void TakeDamage(float damage);
    void Heal(float amount);

    bool IsEmpty() const;
};