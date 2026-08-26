#include "NetworkServer.h"
#include "NetworkPacket.h"
#include <cstring>
#include <iostream>

NetworkServer::NetworkServer() = default;

bool NetworkServer::Start(unsigned short port)
{
    ENetAddress address{};
    address.host = ENET_HOST_ANY;
    address.port = port;
    server = enet_host_create(&address, GameWorld::PlayerCount, 1, 0, 0);
    if (!server) return false;
    std::cout << "Dedicated server listening on " << port << " (max 4 players)\n";
    return true;
}

void NetworkServer::Update(float deltaTime)
{
    if (!server) return;
    ENetEvent event;
    while (enet_host_service(server, &event, 0) > 0)
    {
        if (event.type == ENET_EVENT_TYPE_CONNECT)
        {
            int id = -1;
            for (int candidate = 0; candidate < GameWorld::PlayerCount; ++candidate)
                if (peers[candidate] == nullptr) { id = candidate; break; }
            if (id < 0) { enet_peer_disconnect(event.peer, 0); continue; }
            peers[id] = event.peer;
            event.peer->data = reinterpret_cast<void*>(static_cast<intptr_t>(id + 1));
            world.SetPlayerConnected(id, true);
            SendAssignment(event.peer, id);
        }
        else if (event.type == ENET_EVENT_TYPE_DISCONNECT)
        {
            const int id = static_cast<int>(reinterpret_cast<intptr_t>(event.peer->data)) - 1;
            if (id >= 0 && id < GameWorld::PlayerCount) { peers[id] = nullptr; world.SetPlayerConnected(id, false); }
        }
        else if (event.type == ENET_EVENT_TYPE_RECEIVE)
        {
            const int id = static_cast<int>(reinterpret_cast<intptr_t>(event.peer->data)) - 1;
            if (id >= 0 && id < GameWorld::PlayerCount && event.packet->dataLength == sizeof(PlayerInputCommand))
            {
                PlayerInputCommand command{};
                std::memcpy(&command, event.packet->data, sizeof command);
                if (command.type == NetworkPacketType::PlayerInput)
                {
                    const bool accepted = world.ApplyInput(id, command.moveX, command.moveY, command.collectPressed != 0,
                                                           command.reviveHeld != 0, command.sequenceNumber, command.attackPressed != 0,
                                                           command.attackTargetId);
                     // การคลิกโจมตีลด HP เป้าหมาย 20 หน่วย หลัง server ตรวจคำสั่งแล้ว
                    if (accepted && command.attackPressed)
                        world.DamagePlayer(command.attackTargetId, 20.0f, id);
                }
            }
            enet_packet_destroy(event.packet);
        }
    }
    world.Update(deltaTime);
    SendSnapshot();
}

void NetworkServer::SendAssignment(ENetPeer* peer, int id)
{
    PlayerAssignmentPacket packet{NetworkPacketType::AssignPlayer, id};
    enet_peer_send(peer, 0, enet_packet_create(&packet, sizeof packet, ENET_PACKET_FLAG_RELIABLE));
}

void NetworkServer::SendSnapshot()
{
    NetworkMatchSnapshot snapshot{};
    for (int id = 0; id < GameWorld::PlayerCount; ++id)
    {
        const Player& player = world.GetPlayer(id);
        const Vector2D pos = player.GetPosition();
        snapshot.players[id] = {id, pos.x, pos.y, player.GetHealth(), player.GetMaxHealth(),
                                static_cast<std::uint8_t>(player.GetLifeState()),
                                static_cast<std::uint8_t>(player.HasReviveItem()),
                                static_cast<std::uint8_t>(world.IsPlayerConnected(id))};
    }
    const auto& item = world.GetItem();
    snapshot.reviveItem = {static_cast<std::uint8_t>(item.exists), item.position.x, item.position.y};
    const auto& revive = world.GetReviveProgress();
    snapshot.reviveInProgress = revive.active;
    snapshot.reviverId = revive.reviverId;
    snapshot.reviveTargetId = revive.targetId;
    snapshot.reviveProgress = revive.progress;
    const auto& lastEvent = world.GetLastEvent();
    snapshot.eventType = static_cast<std::uint8_t>(lastEvent.type);
    snapshot.eventActorId = lastEvent.actorId;
    snapshot.eventTargetId = lastEvent.targetId;
    snapshot.eventSequence = lastEvent.sequence;
    for (ENetPeer* peer : peers)
        if (peer) enet_peer_send(peer, 0, enet_packet_create(&snapshot, sizeof snapshot, 0));
}

void NetworkServer::Stop()
{
    if (!server) return;
    enet_host_destroy(server);
    server = nullptr;
    for (ENetPeer*& peer : peers) peer = nullptr;
}

bool NetworkServer::IsRunning() const { return server != nullptr; }
const GameWorld& NetworkServer::GetWorld() const { return world; }
