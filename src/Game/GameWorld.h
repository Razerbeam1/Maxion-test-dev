#pragma once

#include "../Player/player.h"

enum class WorldEventType : unsigned char { None, Joined, Left, Attacked, Downed, ItemCollected, ReviveStarted, ReviveCancelled, Revived };
struct WorldEvent { WorldEventType type = WorldEventType::None; int actorId = -1; int targetId = -1; unsigned int sequence = 0; };
struct ReviveItemState { bool exists = true; Vector2D position{640.0f, 360.0f}; };
struct ReviveProgressState { bool active = false; int reviverId = -1; int targetId = -1; float progress = 0.0f; };

// สถานะแมตช์จริงทั้งหมด ทำงานฝั่ง dedicated server
class GameWorld
{
public:
    // Configurable maximum number of players in one match.
    static constexpr int PlayerCount = 16;
    static constexpr float ArenaWidth = 900.0f;
    static constexpr float ArenaHeight = 600.0f;

    GameWorld();
    void Update(float deltaTime);
    // ตรวจ input ก่อนเปลี่ยนตำแหน่ง เก็บไอเท็ม หรือเริ่มชุบ
    bool ApplyInput(int playerId, float moveX, float moveY, bool collectPressed,
                    bool reviveHeld, unsigned int sequenceNumber, bool attackPressed = false, int attackTargetId = -1);
    bool DamagePlayer(int playerId, float damage, int attackerId = -1);
    void SetPlayerConnected(int playerId, bool connected);
    bool IsPlayerConnected(int playerId) const;

    Player& GetPlayer(int playerId);
    const Player& GetPlayer(int playerId) const;
    const ReviveItemState& GetItem() const;
    const ReviveProgressState& GetReviveProgress() const;
    const WorldEvent& GetLastEvent() const;
    void SetPlayerPositionForTest(int playerId, Vector2D position);
    void SetPlayerDeadForTest(int playerId);

private:
    bool ValidPlayerId(int playerId) const;
    bool TryCollectItem(int playerId);
    int FindReviveTarget(int reviverId) const;
    Vector2D RandomSpawnPosition();
    void UpdateRevive(int playerId, bool held, float deltaTime);
    void CancelRevive();
    void AddEvent(WorldEventType type, int actorId, int targetId = -1);

    Player players[PlayerCount];
    bool connected[PlayerCount]{};
    ReviveItemState item;
    ReviveProgressState revive;
    WorldEvent lastEvent;
    unsigned int lastSequence[PlayerCount]{};
    float movementX[PlayerCount]{};
    float movementY[PlayerCount]{};
    bool reviveHeld[PlayerCount]{};
    float itemRespawnTimer = 0.0f;
};
