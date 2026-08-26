#include "ReviveSystem.h"
#include <algorithm>

void ReviveSystem::SetProgress(bool active, float seconds)
{
    // ไคลเอนต์รับ progress จาก server เท่านั้น ไม่ตัดสินผลการชุบเอง
    isReviving = active;
    reviveProgress = std::clamp(seconds, 0.0f, ReviveDuration);
}

void ReviveSystem::Draw(Vector2 position) const
{
    if (!isReviving)
        return;

    const int width = 100;
    DrawRectangle(static_cast<int>(position.x) - 50, static_cast<int>(position.y), width, 15, LIGHTGRAY);
    DrawRectangle(static_cast<int>(position.x) - 50, static_cast<int>(position.y),
                  static_cast<int>(width * reviveProgress / ReviveDuration), 15, GREEN);
    DrawRectangleLines(static_cast<int>(position.x) - 50, static_cast<int>(position.y), width, 15, BLACK);
    DrawText("REVIVING", static_cast<int>(position.x) - 45, static_cast<int>(position.y) - 25, 16, BLACK);
}

bool ReviveSystem::IsReviving() const
{
    return isReviving;
}
