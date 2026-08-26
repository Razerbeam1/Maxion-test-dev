#include "HUD.h"

void HUD::DrawHealth(float health, float maxHealth)
{
    // =========================
    // HP Text
    // =========================

    DrawText(
        TextFormat(
            "HP: %.0f / %.0f",
            health,
            maxHealth
        ),
        20,
        20,
        24,
        BLACK
    );

    // =========================
    // HP Bar Background
    // =========================

    DrawRectangle(
        20,
        50,
        250,
        25,
        LIGHTGRAY
    );

    // =========================
    // HP Bar
    // =========================

    float healthPercent = health / maxHealth;

    DrawRectangle(
        20,
        50,
        (int)(250 * healthPercent),
        25,
        GREEN
    );

    // =========================
    // HP Bar Border
    // =========================

    DrawRectangleLines(
        20,
        50,
        250,
        25,
        BLACK
    );
}

void HUD::DrawInventory(bool hasReviveItem)
{
    // =========================
    // Inventory Title
    // =========================

    DrawText(
        "Inventory",
        20,
        100,
        24,
        BLACK
    );

    // =========================
    // Inventory Slot
    // =========================

    DrawRectangle(
        20,
        135,
        120,
        70,
        LIGHTGRAY
    );

    DrawRectangleLines(
        20,
        135,
        120,
        70,
        BLACK
    );

    // =========================
    // Item
    // =========================

    if (hasReviveItem)
    {
        DrawText(
            "REVIVE",
            40,
            160,
            20,
            GREEN
        );
    }
    else
    {
        DrawText(
            "EMPTY",
            40,
            160,
            20,
            DARKGRAY
        );
    }
}