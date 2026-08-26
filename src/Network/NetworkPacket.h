#pragma once
#include <cstdint>

enum class NetworkPacketType : std::uint8_t { AssignPlayer = 1, PlayerInput = 2, MatchSnapshot = 3 };
#pragma pack(push, 1)
// ไคลเอนต์ส่งคำสั่งเท่านั้น ห้ามส่งตำแหน่งหรือ HP
struct PlayerInputCommand
{
    NetworkPacketType type = NetworkPacketType::PlayerInput;
    float moveX = 0, moveY = 0;
    std::uint8_t collectPressed = 0, reviveHeld = 0, attackPressed = 0;
    std::int32_t attackTargetId = -1;
    std::uint32_t sequenceNumber = 0;
};
struct NetworkPlayerSnapshot { std::int32_t playerId; float x, y, health, maxHealth; std::uint8_t lifeState, hasReviveItem, connected; };
struct NetworkItemSnapshot { std::uint8_t exists; float x, y; };
// สถานะจริงจาก server เพื่อให้ทุก client เห็นผลเหมือนกัน
struct NetworkMatchSnapshot
{
    NetworkPacketType type = NetworkPacketType::MatchSnapshot;
    NetworkPlayerSnapshot players[16];
    NetworkItemSnapshot reviveItem;
    std::uint8_t reviveInProgress;
    std::int32_t reviverId, reviveTargetId;
    float reviveProgress;
    std::uint8_t eventType;
    std::int32_t eventActorId, eventTargetId;
    std::uint32_t eventSequence;
};
struct PlayerAssignmentPacket { NetworkPacketType type = NetworkPacketType::AssignPlayer; std::int32_t playerId; };
#pragma pack(pop)
