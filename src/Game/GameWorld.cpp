#include "GameWorld.h"
#include <algorithm>
#include <cmath>
#include <random>

namespace
{
constexpr float PlayerSize = 40.0f;
constexpr float ItemRange = 80.0f;
constexpr float ReviveRange = 90.0f;
constexpr float ReviveDuration = 2.0f;
constexpr float ReviveHealth = 40.0f;
constexpr float ItemRespawnSeconds = 5.0f;
std::mt19937 randomEngine(std::random_device{}());
}

GameWorld::GameWorld()
{
    item.position = RandomSpawnPosition();
    for (int id = 0; id < PlayerCount; ++id) players[id].SetPosition(RandomSpawnPosition());
}

void GameWorld::Update(float deltaTime)
{
    const float dt = std::clamp(deltaTime, 0.0f, 0.1f);
    for (int id = 0; id < PlayerCount; ++id)
    {
        if (connected[id] && players[id].GetLifeState() == PlayerLifeState::Alive)
            players[id].Move(movementX[id], movementY[id], dt, ArenaWidth, ArenaHeight, PlayerSize);
        UpdateRevive(id, reviveHeld[id], dt);
    }
    // ไอเท็มกลับมาเกิดแบบสุ่มหลังถูกเก็บ
    if (!item.exists && (itemRespawnTimer -= dt) <= 0.0f)
    {
        item.exists = true;
        item.position = RandomSpawnPosition();
    }
}

bool GameWorld::ApplyInput(int id, float moveX, float moveY, bool collectPressed,
                           bool held, unsigned int sequenceNumber, bool attackPressed, int attackTargetId)
{
    if (!ValidPlayerId(id) || !connected[id] || sequenceNumber <= lastSequence[id]) return false;
    lastSequence[id] = sequenceNumber;
    Player& player = players[id];
    if (player.GetLifeState() != PlayerLifeState::Alive) return false;

    if (attackPressed && (!ValidPlayerId(attackTargetId) || attackTargetId == id || !connected[attackTargetId])) return false;
     // ตรวจการเก็บก่อน เพื่อให้คำสั่งไกลเกินระยะไม่เปลี่ยนสถานะอื่น
    if (collectPressed && !TryCollectItem(id)) return false;
    const float length = std::sqrt(moveX * moveX + moveY * moveY);
    movementX[id] = length > 1.0f ? moveX / length : moveX;
    movementY[id] = length > 1.0f ? moveY / length : moveY;
    reviveHeld[id] = held;
    if (!held && revive.active && revive.reviverId == id) CancelRevive();
    return true;
}

bool GameWorld::DamagePlayer(int id, float damage, int attackerId)
{
    if (!ValidPlayerId(id) || !connected[id] || damage <= 0.0f || players[id].GetLifeState() != PlayerLifeState::Alive) return false;
    players[id].TakeDamage(damage);
    AddEvent(players[id].GetLifeState() == PlayerLifeState::Downed ? WorldEventType::Downed : WorldEventType::Attacked, attackerId, id);
    if (revive.active && (revive.reviverId == id || revive.targetId == id)) CancelRevive();
    return true;
}

void GameWorld::SetPlayerConnected(int id, bool isConnected)
{
    if (!ValidPlayerId(id)) return;
    connected[id] = isConnected;
    movementX[id] = movementY[id] = 0.0f;
    reviveHeld[id] = false;
    // สร้างตำแหน่งใหม่เฉพาะตอนผู้เล่น join จริง
    if (isConnected) players[id].SetPosition(RandomSpawnPosition());
    if (revive.active && (revive.reviverId == id || revive.targetId == id)) CancelRevive();
    AddEvent(isConnected ? WorldEventType::Joined : WorldEventType::Left, id);
}

bool GameWorld::IsPlayerConnected(int id) const { return ValidPlayerId(id) && connected[id]; }
Player& GameWorld::GetPlayer(int id) { return players[id]; }
const Player& GameWorld::GetPlayer(int id) const { return players[id]; }
const ReviveItemState& GameWorld::GetItem() const { return item; }
const ReviveProgressState& GameWorld::GetReviveProgress() const { return revive; }
const WorldEvent& GameWorld::GetLastEvent() const { return lastEvent; }
void GameWorld::SetPlayerPositionForTest(int id, Vector2D pos) { if (ValidPlayerId(id)) players[id].SetPosition(pos); }
void GameWorld::SetPlayerDeadForTest(int id) { if (ValidPlayerId(id)) players[id].SetDead(); }
bool GameWorld::ValidPlayerId(int id) const { return id >= 0 && id < PlayerCount; }

bool GameWorld::TryCollectItem(int id)
{
    Player& player = players[id];
    if (!item.exists || DistanceSquared(player.GetPosition(), item.position) > ItemRange * ItemRange) return false;
    player.AddReviveItem();
    item.exists = false;
    itemRespawnTimer = ItemRespawnSeconds;
    AddEvent(WorldEventType::ItemCollected, id);
    return true;
}

int GameWorld::FindReviveTarget(int reviverId) const
{
    int closestId = -1;
    float closestDistance = ReviveRange * ReviveRange;
    for (int id = 0; id < PlayerCount; ++id)
    {
        if (id == reviverId || !connected[id] || players[id].GetLifeState() != PlayerLifeState::Downed) continue;
        const float distance = DistanceSquared(players[reviverId].GetPosition(), players[id].GetPosition());
        if (distance <= closestDistance) { closestDistance = distance; closestId = id; }
    }
    return closestId;
}

void GameWorld::UpdateRevive(int id, bool held, float deltaTime)
{
    if (!held || !connected[id]) return;
    const int targetId = FindReviveTarget(id);
    const Player& reviver = players[id];
    if (!reviver.HasReviveItem() || reviver.GetLifeState() != PlayerLifeState::Alive || targetId < 0)
    {
        if (revive.active && revive.reviverId == id) CancelRevive();
        return;
    }
    if (!revive.active)
    {
        revive = {true, id, targetId, 0.0f};
        AddEvent(WorldEventType::ReviveStarted, id, targetId);
    }
    if (revive.reviverId != id || revive.targetId != targetId) return;
    revive.progress += deltaTime;
    if (revive.progress >= ReviveDuration)
    {
        players[targetId].Revive(ReviveHealth);
        players[id].UseReviveItem();
        AddEvent(WorldEventType::Revived, id, targetId);
        revive = {};
    }
}

void GameWorld::CancelRevive()
{
    if (revive.active) AddEvent(WorldEventType::ReviveCancelled, revive.reviverId, revive.targetId);
    revive = {};
}

Vector2D GameWorld::RandomSpawnPosition()
{
    std::uniform_real_distribution<float> x(40.0f, ArenaWidth - 80.0f);
    std::uniform_real_distribution<float> y(60.0f, ArenaHeight - 80.0f);
    return {x(randomEngine), y(randomEngine)};
}

void GameWorld::AddEvent(WorldEventType type, int actorId, int targetId)
{
    lastEvent = {type, actorId, targetId, lastEvent.sequence + 1};
}
