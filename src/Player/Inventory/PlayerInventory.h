#pragma once

class PlayerInventory
{
private:
    bool hasHealItem;

public:
    PlayerInventory();

    bool HasHealItem() const;

    void AddHealItem();
    void RemoveHealItem();
};