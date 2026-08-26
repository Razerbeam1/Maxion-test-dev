#include "PlayerHealth.h"

PlayerHealth::PlayerHealth(float maxHealth)
{
    this->maxHealth = maxHealth;
    health = maxHealth;
}

float PlayerHealth::GetHealth() const
{
    return health;
}

float PlayerHealth::GetMaxHealth() const
{
    return maxHealth;
}

void PlayerHealth::TakeDamage(float damage)
{
    health -= damage;

    if (health < 0.0f)
    {
        health = 0.0f;
    }
}

void PlayerHealth::Heal(float amount)
{
    health += amount;

    if (health > maxHealth)
    {
        health = maxHealth;
    }
}

bool PlayerHealth::IsEmpty() const
{
    return health <= 0.0f;
}