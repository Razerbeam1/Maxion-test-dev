#include "../Game/GameWorld.h"
#include <cassert>
#include <iostream>

void ConnectTwo(GameWorld& world)
{
    world.SetPlayerConnected(0, true);
    world.SetPlayerConnected(1, true);
}

int main()
{
    GameWorld world;
    ConnectTwo(world);
    world.DamagePlayer(0, 100.0f);
    const Vector2D downedPosition = world.GetPlayer(0).GetPosition();
    assert(!world.ApplyInput(0, 1, 0, false, false, 1)); // ล้มแล้วเดินไม่ได้
    world.Update(0.1f);
    assert(world.GetPlayer(0).GetPosition().x == downedPosition.x);
    world.SetPlayerDeadForTest(0);
    assert(!world.ApplyInput(0, 0, 0, true, false, 2)); // ผู้เล่นที่ตายแล้วไม่สามารถเก็บไอเท็มได้.

    GameWorld contested;
    ConnectTwo(contested);
    const Vector2D itemPosition = contested.GetItem().position;
    contested.SetPlayerPositionForTest(0, itemPosition);
    contested.SetPlayerPositionForTest(1, itemPosition);
    assert(contested.ApplyInput(0, 0, 0, true, false, 1));
    assert(!contested.ApplyInput(1, 0, 0, true, false, 1)); // คนที่สองไม่ได้ไอเท็ม
    assert(!contested.ApplyInput(0, 0, 0, false, false, 1)); // sequence ซ้ำ


    GameWorld revive;
    ConnectTwo(revive);
    const Vector2D reviveItemPosition = revive.GetItem().position;
    revive.SetPlayerPositionForTest(0, reviveItemPosition);
    assert(revive.ApplyInput(0, 0, 0, true, false, 1)); // ต้องมีไอเท็มก่อนชุบ
    revive.DamagePlayer(1, 100.0f);
    revive.SetPlayerPositionForTest(0, {100, 100});
    revive.SetPlayerPositionForTest(1, {110, 100});
    assert(revive.ApplyInput(0, 0, 0, false, true, 2));
    revive.Update(0.5f);
    assert(revive.GetReviveProgress().active);
    assert(revive.ApplyInput(0, 0, 0, false, false, 3)); // ปล่อย E ยกเลิก
    assert(!revive.GetReviveProgress().active);
    revive.ApplyInput(0, 0, 0, false, true, 4);
    revive.Update(0.5f);
    revive.DamagePlayer(0, 20.0f, 1);
    assert(!revive.GetReviveProgress().active); // โดนโจมตีแล้วชุบยกเลิก

    std::cout << "GameWorld rule tests passed\n";
}
