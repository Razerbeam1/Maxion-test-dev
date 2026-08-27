#include "GameRenderer.h"
#include "raylib.h"
#include <cmath>

namespace
{
// โทนหลักของ client ใช้สีเทาเป็นพื้น สีที่เหลือสงวนไว้บอกสถานะที่สำคัญ
constexpr Color BackgroundColor = {24, 24, 24, 255};
constexpr Color HeaderColor = {36, 36, 36, 255};
constexpr Color ArenaColor = {30, 30, 30, 255};
constexpr Color SidePanelColor = {34, 34, 34, 255};
constexpr Color BorderColor = {76, 76, 76, 255};
constexpr float ArenaX = 40.0f;
constexpr float ArenaY = 110.0f;
constexpr float ArenaWidth = 880.0f;
constexpr float ArenaHeight = 570.0f;
const char* LifeText(unsigned char state) { return state == 0 ? "ALIVE" : state == 1 ? "DOWNED" : "DEAD"; }
std::string PlayerName(int id) { return "PLAYER " + std::to_string(id + 1); }
}

void GameRenderer::Draw(const NetworkMatchSnapshot* snapshot, bool connected, int localPlayerId)
{
    BeginDrawing();
    ClearBackground(BackgroundColor);
    DrawRectangleRounded({40, 25, 1160, 58}, 0.12f, 8, HeaderColor);
    DrawText("CO-OP ARENA", 65, 48, 20, RAYWHITE);
    DrawText("SERVER  TICK", 350, 50, 16, SKYBLUE);
    DrawText(connected ? "CONNECTED" : "DISCONNECTED", 1030, 50, 16, connected ? LIME : ORANGE);

    DrawRectangleRounded({ArenaX, ArenaY, ArenaWidth, ArenaHeight}, 0.03f, 6, ArenaColor);
    DrawRectangleLinesEx({ArenaX, ArenaY, ArenaWidth, ArenaHeight}, 2, BorderColor);

    if (snapshot != nullptr)
    {
        UpdateEvents(*snapshot);
        if (snapshot->reviveItem.exists)
        {
            const Vector2 item = {ArenaX + snapshot->reviveItem.x, ArenaY + snapshot->reviveItem.y};
            DrawPoly(item, 4, 20, 0, {255, 195, 65, 255});
            DrawText("REVIVE KIT", static_cast<int>(item.x) - 35, static_cast<int>(item.y) + 30, 15, RAYWHITE);
        }
        for (const NetworkPlayerSnapshot& player : snapshot->players)
            if (player.connected) DrawPlayer(player, localPlayerId);

        if (snapshot->reviveInProgress)
        {
            DrawText("REVIVING", 60, 640, 16, RAYWHITE);
            DrawRectangle(180, 642, static_cast<int>(220 * snapshot->reviveProgress / 2.0f), 14, LIME);
            DrawRectangleLines(180, 642, 220, 14, RAYWHITE);
        }
        // Show a pickup hint only when the local player is in range.
        if (localPlayerId >= 0 && snapshot->reviveItem.exists)
        {
            const NetworkPlayerSnapshot& local = snapshot->players[localPlayerId];
            const float dx = local.x - snapshot->reviveItem.x, dy = local.y - snapshot->reviveItem.y;
            if (local.connected && dx * dx + dy * dy <= 80.0f * 80.0f)
                DrawText("PRESS E TO PICK UP REVIVE KIT", 300, 90, 16, {255, 205, 75, 255});
        }
    }

    DrawRectangleRounded({950, 110, 250, 570}, 0.04f, 6, SidePanelColor);
    DrawText("TEAM STATUS", 975, 130, 20, RAYWHITE);
    if (snapshot != nullptr)
    {
        int panelY = 165;
        for (const NetworkPlayerSnapshot& player : snapshot->players)
            if (player.connected && panelY < 570) { DrawPlayerPanel(player, panelY); panelY += 75; }
    }
    DrawEvents();
    DrawText("WASD: MOVE | E: PICK UP / HOLD TO REVIVE", 55, 695, 15, SKYBLUE);
    DrawText("CLICK ANOTHER PLAYER: DEAL 20 DAMAGE", 430, 695, 15, SKYBLUE);
    EndDrawing();
}

void GameRenderer::DrawPlayer(const NetworkPlayerSnapshot& player, int localPlayerId) const
{
    const float x = ArenaX + player.x, y = ArenaY + player.y;
    // ใช้สีเพียงสีเดียวแยกผู้เล่นของเราออกจากคนอื่น; Downed ใช้ส้มเพื่อให้เห็นสถานะ
    const Color color = player.playerId == localPlayerId ? LIGHTGRAY : GRAY;
    DrawCircle(static_cast<int>(x + 20), static_cast<int>(y + 20), 24, Fade(color, 0.25f));
    DrawCircle(static_cast<int>(x + 20), static_cast<int>(y + 20), 19, player.lifeState == 1 ? ORANGE : color);
    DrawText(TextFormat("P%d  %.0f HP", player.playerId + 1, player.health), static_cast<int>(x - 8), static_cast<int>(y + 50), 15, RAYWHITE);
    if (player.lifeState == 1) DrawText("DOWNED", static_cast<int>(x - 5), static_cast<int>(y - 25), 16, ORANGE);
}

void GameRenderer::DrawPlayerPanel(const NetworkPlayerSnapshot& player, int y) const
{
    DrawText(PlayerName(player.playerId).c_str(), 975, y, 17, RAYWHITE);
    DrawText(LifeText(player.lifeState), 975, y + 23, 15, player.lifeState == 1 ? ORANGE : SKYBLUE);
    DrawRectangle(975, y + 48, 190, 13, {65, 65, 65, 255});
    DrawRectangle(975, y + 48, static_cast<int>(190 * player.health / player.maxHealth), 13, LIGHTGRAY);
    DrawText(TextFormat("%.0f / %.0f", player.health, player.maxHealth), 1080, y + 65, 13, LIGHTGRAY);
    DrawText(player.hasReviveItem ? "REVIVE KIT: READY" : "REVIVE KIT: EMPTY", 975, y + 40, 8, player.hasReviveItem ? GOLD : GRAY);
}

void GameRenderer::UpdateEvents(const NetworkMatchSnapshot& snapshot)
{
    if (snapshot.eventSequence == 0 || snapshot.eventSequence == lastEventSequence) return;
    lastEventSequence = snapshot.eventSequence;
    const int actor = snapshot.eventActorId + 1, target = snapshot.eventTargetId + 1;
    std::string text;
    switch (snapshot.eventType)
    {
        case 1: text = "P" + std::to_string(actor) + " joined the match"; break;
        case 2: text = "P" + std::to_string(actor) + " left the match"; break;
        case 3: text = "P" + std::to_string(actor) + " attacked P" + std::to_string(target); break;
        case 4: text = "P" + std::to_string(target) + " is downed"; break;
        case 5: text = "P" + std::to_string(actor) + " picked up a revive kit"; break;
        case 6: text = "P" + std::to_string(actor) + " started reviving P" + std::to_string(target); break;
        case 7: text = "Revive cancelled"; break;
        case 8: text = "P" + std::to_string(actor) + " revived P" + std::to_string(target); break;
        default: return;
    }
    events.insert(events.begin(), text);
    if (events.size() > 3) events.pop_back();
}

void GameRenderer::DrawEvents() const
{
    DrawText("EVENTS", 975, 590, 17, RAYWHITE);
    int y = 612;
    for (const std::string& event : events) { DrawText(event.c_str(), 975, y, 13, SKYBLUE); y += 19; }
}
