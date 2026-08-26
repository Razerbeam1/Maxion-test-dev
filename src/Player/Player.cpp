#include "Player.h"

Player::Player(float x, float y)
{
    data.position = {x, y};

    state = PlayerState::Alive;
}

void Player::Update(
    int screenWidth,
    int screenHeight
)
{
    if (state != PlayerState::Alive)
    {
        return;
    }

    movement.Update(
        data.position,
        screenWidth,
        screenHeight
    );
}

void Player::Draw()
{
    DrawRectangle(
        (int)data.position.x,
        (int)data.position.y,
        40,
        40,
        BLUE
    );
}

// =========================
// POSITION
// =========================

Vector2 Player::GetPosition() const
{
    return data.position;
}

// =========================
// HEALTH
// =========================

float Player::GetHealth() const
{
    return health.GetHealth();
}

float Player::GetMaxHealth() const
{
    return health.GetMaxHealth();
}

void Player::TakeDamage(float damage)
{
    health.TakeDamage(damage);

    if (health.IsEmpty())
    {
        state = PlayerState::Downed;
    }
}

void Player::Heal(float amount)
{
    health.Heal(amount);
}

// =========================
// INVENTORY
// =========================

bool Player::HasHealItem() const
{
    return inventory.HasHealItem();
}

void Player::AddHealItem()
{
    inventory.AddHealItem();
}

void Player::UseHealItem()
{
    inventory.RemoveHealItem();
}

// =========================
// STATE
// =========================

PlayerState Player::GetState() const
{
    return state;
}