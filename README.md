# Co-op Arena

เกมต่อสู้ร่วมทีมมุมมองจากด้านบน โดย **เซิร์ฟเวอร์เป็นผู้ตัดสินผลจริง** ผู้เล่นส่งเพียงปุ่มที่กด ส่วนการเดิน HP การโจมตี การเก็บของ และการชุบชีวิต จะถูกตรวจและคำนวณที่เซิร์ฟเวอร์

## เปิดเล่นจากไฟล์ `.exe` (ไม่ต้องใช้ VS Code)

ต้องเก็บไฟล์ `.exe` ไว้ในโฟลเดอร์เดียวกัน แล้วเปิดตามลำดับนี้ผ่าน File Explorer

1. ดับเบิลคลิก **`GameServer.exe`**
   - จะเห็นหน้าต่าง Terminal เปิดค้างไว้
   - รอข้อความ `Dedicated server listening on 27015`
   - **อย่าปิดหน้าต่างนี้ระหว่างเล่น** เพราะเป็นเซิร์ฟเวอร์ของเกม
2. ดับเบิลคลิก **`GameClient.exe`**
   - หน้าต่างเกมจะเปิดขึ้นทันที เป็น Player 1
3. หากต้องการเพิ่มผู้เล่นในเครื่องเดียวกัน ให้ดับเบิลคลิก `GameClient.exe` อีกครั้ง
   - หน้าต่างใหม่จะเป็น Player 2 (และเปิดเพิ่มได้ตามจำนวนที่เซิร์ฟเวอร์รองรับ)
4. เมื่อเล่นเสร็จ ให้ปิดหน้าต่างเกมทุกอัน แล้วปิด Terminal ของ `GameServer.exe`

`Game.exe` ไม่ใช่ไฟล์ที่ใช้เปิดเกมในเวอร์ชันนี้ ให้ใช้ `GameServer.exe` และ `GameClient.exe` ตามขั้นตอนข้างต้น

## วิธีเล่น

| ปุ่ม | การทำงาน |
| --- | --- |
| WASD | เดิน |
| E (กดครั้งเดียว) | เก็บกล่อง Revive Kit สีทองเมื่ออยู่ใกล้ |
| E (กดค้าง) | ชุบเพื่อนที่ล้มเมื่ออยู่ใกล้และมี Revive Kit |
| คลิกซ้ายที่ผู้เล่นอื่น | โจมตี ลด HP 20 หน่วย |

ผู้เล่นเริ่มด้วย 100 HP เมื่อ HP เหลือ 0 จะอยู่สถานะ **DOWNED** และเดิน/โจมตี/เก็บของ/ชุบไม่ได้ เพื่อนที่เป็น **ALIVE** และถือ Revive Kit ต้องยืนใกล้แล้วกด E ค้าง 2 วินาที จึงชุบกลับมาที่ 40 HP ได้

กล่อง Revive Kit จะสุ่มเกิดในสนาม เมื่อมีคนเก็บแล้วจะเกิดใหม่หลัง 5 วินาที

## เล่นข้ามเครื่องในเครือข่ายเดียวกัน

เครื่องเจ้าบ้านเปิด `GameServer.exe` ก่อน เครื่องอื่นต้องเปิด Command Prompt หรือ PowerShell ในโฟลเดอร์นี้ แล้วระบุ IP ของเครื่องเจ้าบ้าน:

```powershell
.\GameClient.exe 192.168.1.10
```

ใช้ UDP port `27015` ดังนั้นเครื่องเจ้าบ้านต้องอนุญาตพอร์ตนี้ผ่าน Windows Firewall หากเล่นเครื่องเดียวกัน ไม่ต้องระบุ IP และเปิด `GameClient.exe` ด้วยการดับเบิลคลิกได้เลย

## ไฟล์ในโฟลเดอร์นี้

| ไฟล์ | หน้าที่ |
| --- | --- |
| `GameServer.exe` | เปิดเซิร์ฟเวอร์ใน Terminal — เปิดก่อนเสมอ |
| `GameClient.exe` | เปิดหน้าต่างเกมของผู้เล่น |
| `GameWorldTests.exe` | ทดสอบกติกาเกมสำหรับผู้พัฒนา |
| `CODE_OVERVIEW.txt` | เอกสารสรุปการทำงานและความเชื่อมโยงของโค้ดทุกส่วน |

## สำหรับผู้พัฒนา

ซอร์สโค้ดอยู่ใน `src` แบ่งเป็น 3 ส่วน: กติกาเกมฝั่ง server (`GameWorld`, `Player`), เครือข่าย (`NetworkServer`, `NetworkClient`), และหน้าจอฝั่งผู้เล่น (`Game`, `ClientInput`, `GameRenderer`) รายละเอียดครบทุกไฟล์อยู่ที่ `CODE_OVERVIEW.txt`

หากแก้ C++ แล้วต้องสร้าง `.exe` ใหม่ โปรเจกต์ใช้ C++17, Raylib และ ENet โดย build ผ่าน MSYS2 UCRT64:

```powershell
g++ -std=c++17 -I./src src/server_main.cpp src/Network/NetworkServer.cpp src/Game/GameWorld.cpp src/Player/Player.cpp src/Player/Movement/PlayerMovement.cpp src/Player/Health/PlayerHealth.cpp src/Player/Inventory/PlayerInventory.cpp -o GameServer.exe -lenet -lws2_32 -lwinmm
g++ -std=c++17 -I./src src/main.cpp src/Game/Game.cpp src/Client/ClientInput.cpp src/Client/GameRenderer.cpp src/Network/NetworkClient.cpp -o GameClient.exe -lraylib -lenet -lopengl32 -lgdi32 -lwinmm
g++ -std=c++17 -I./src src/Test/GameWorldTests.cpp src/Game/GameWorld.cpp src/Player/Player.cpp src/Player/Movement/PlayerMovement.cpp src/Player/Health/PlayerHealth.cpp src/Player/Inventory/PlayerInventory.cpp -o GameWorldTests.exe
```

หลัง build ให้ดับเบิลคลิก `GameWorldTests.exe` หรือรันผ่าน PowerShell ผลที่ถูกต้องคือ `GameWorld rule tests passed`
