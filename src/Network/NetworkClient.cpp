#include "NetworkClient.h"
#include <cstring>

bool NetworkClient::Start() { client = enet_host_create(nullptr, 1, 1, 0, 0); return client != nullptr; }

bool NetworkClient::Connect(const char* host, unsigned short port)
{
    if (!client) return false;
    ENetAddress address{};
    if (enet_address_set_host(&address, host) != 0) return false;
    address.port = port;
    server = enet_host_connect(client, &address, 1, 0);
    if (!server) return false;
    ENetEvent event;
    return enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT;
}

void NetworkClient::Update()
{
    if (!client) return;
    ENetEvent event;
    while (enet_host_service(client, &event, 0) > 0)
    {
        if (event.type == ENET_EVENT_TYPE_DISCONNECT) { server = nullptr; playerId = -1; }
        else if (event.type == ENET_EVENT_TYPE_RECEIVE)
        {
            if (event.packet->dataLength >= 1)
            {
                const auto type = *reinterpret_cast<const NetworkPacketType*>(event.packet->data);
                if (type == NetworkPacketType::AssignPlayer && event.packet->dataLength == sizeof(PlayerAssignmentPacket))
                {
                    PlayerAssignmentPacket assignment{};
                    std::memcpy(&assignment, event.packet->data, sizeof assignment);
                    playerId = assignment.playerId;
                }
                else if (type == NetworkPacketType::MatchSnapshot && event.packet->dataLength == sizeof(NetworkMatchSnapshot))
                {
                    std::memcpy(&snapshot, event.packet->data, sizeof snapshot);
                    hasSnapshot = true;
                }
            }
            enet_packet_destroy(event.packet);
        }
    }
}

void NetworkClient::Stop()
{
    if (client) { if (server) enet_peer_disconnect(server, 0); enet_host_destroy(client); }
    client = nullptr;
    server = nullptr;
}

bool NetworkClient::IsConnected() const { return server != nullptr; }

void NetworkClient::SendInput(float x, float y, bool collect, bool revive, bool attack, int attackTargetId)
{
    if (!server) return;
    PlayerInputCommand command{};
    command.moveX = x;
    command.moveY = y;
    command.collectPressed = collect;
    command.reviveHeld = revive;
    command.attackPressed = attack;
    command.attackTargetId = attackTargetId;
    command.sequenceNumber = ++sequence;
    enet_peer_send(server, 0, enet_packet_create(&command, sizeof command, 0));
}

int NetworkClient::GetPlayerId() const { return playerId; }
bool NetworkClient::HasSnapshot() const { return hasSnapshot; }
const NetworkMatchSnapshot& NetworkClient::GetSnapshot() const { return snapshot; }
