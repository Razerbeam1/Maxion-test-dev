#pragma once

#include "raylib.h"

// แสดงความคืบหน้าการชุบจากข้อมูลที่เซิร์ฟเวอร์ยืนยันแล้ว
class ReviveSystem
{
public:
    void SetProgress(bool active, float seconds);
    void Draw(Vector2 position) const;
    bool IsReviving() const;

private:
    bool isReviving = false;
    float reviveProgress = 0.0f;
    static constexpr float ReviveDuration = 2.0f;
};
