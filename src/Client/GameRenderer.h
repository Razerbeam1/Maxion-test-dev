#pragma once

#include "../Network/NetworkPacket.h"
#include <string>
#include <vector>

// วาด HUD และสนามจาก snapshot ล่าสุด โดยไม่แก้กติกาเกมเอง
class GameRenderer
{
public:
    void Draw(const NetworkMatchSnapshot* snapshot, bool connected, int localPlayerId);

private:
    void UpdateEvents(const NetworkMatchSnapshot& snapshot);
    void DrawPlayer(const NetworkPlayerSnapshot& player, int localPlayerId) const;
    void DrawPlayerPanel(const NetworkPlayerSnapshot& player, int y) const;
    void DrawEvents() const;
    std::vector<std::string> events;
    unsigned int lastEventSequence = 0;
};
