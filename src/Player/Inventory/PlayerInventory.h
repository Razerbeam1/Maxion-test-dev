#pragma once

class PlayerInventory
{
private:
    bool hasReviveItem;

public:
    PlayerInventory();

    bool HasReviveItem() const;

    void AddReviveItem();
    void RemoveReviveItem();
};