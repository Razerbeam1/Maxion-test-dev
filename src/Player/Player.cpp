#include "player.h"

Player::Player(float x, float y) { data.position = {x, y}; state = PlayerLifeState::Alive; }
void Player::Move(float inputX, float inputY, float deltaTime, float arenaWidth, float arenaHeight, float playerSize)
{
    if (state == PlayerLifeState::Alive) movement.Move(data.position, inputX, inputY, deltaTime, arenaWidth, arenaHeight, playerSize);
}
Vector2D Player::GetPosition() const { return data.position; }
void Player::SetPosition(Vector2D position) { data.position = position; }
float Player::GetHealth() const { return health.GetHealth(); }
float Player::GetMaxHealth() const { return health.GetMaxHealth(); }
void Player::TakeDamage(float damage) { if (state == PlayerLifeState::Dead) return; health.TakeDamage(damage); if (health.IsEmpty()) state = PlayerLifeState::Downed; }
void Player::Heal(float amount) { if (state == PlayerLifeState::Alive) health.Heal(amount); }
bool Player::HasReviveItem() const { return inventory.HasReviveItem(); }
void Player::AddReviveItem() { inventory.AddReviveItem(); }
bool Player::UseReviveItem() { if (state != PlayerLifeState::Alive || !inventory.HasReviveItem()) return false; inventory.RemoveReviveItem(); return true; }
PlayerLifeState Player::GetLifeState() const { return state; }
void Player::Revive(float healthAmount) { if (state != PlayerLifeState::Downed) return; health.Heal(healthAmount); state = PlayerLifeState::Alive; }
void Player::SetDead() { state = PlayerLifeState::Dead; }
