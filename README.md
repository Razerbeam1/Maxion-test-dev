# Co-op Arena 

เกมต่อสู้แบบทีมมองจากด้านบน ผู้เล่นเดิน เก็บ `Revive Kit` โจมตี และชุบเพื่อนที่ล้มได้ Server เป็นคนคำนวณผลจริง ส่วนหน้าต่างของผู้เล่นรับปุ่มและแสดงผล

## วิธีเปิดเล่น

เก็บไฟล์ `.exe` ไว้โฟลเดอร์เดียวกัน แล้วทำตามลำดับนี้

1.  `GameServer.exe` เปิดค้างไว้  ใน Terminal
2.  `GameClient.exe` เพื่อเปิดหน้าต่างเกม 
3. เปิด `GameClient.exe` ซ้ำเพื่อเพิ่มผู้เล่นในเครื่องเดียวกัน


ปุ่มเล่น

| ปุ่ม | การทำงาน |
| --- | --- |
| `W A S D` | ควบคุม |
| กด `E`  | เก็บกล่อง Revive Kit เมื่ออยู่ใกล้ |
| Hold `E` | Revivew player |
| LMB | โจมตี ลด HP 20 |

## เล่นข้ามเครื่อง

เครื่องเจ้าบ้านเปิด `GameServer.exe` ก่อน เครื่องอื่นเปิด PowerShell ในโฟลเดอร์นี้แล้วใช้ IP ของเจ้าบ้าน:

```powershell
.\GameClient.exe 192.168.1.10
```

ต้องอนุญาต UDP port `27015` ใน Windows Firewall ของเจ้าบ้าน หากเล่นเครื่องเดียวกัน ไม่ต้องใส่ IP

## ไฟล์ `.exe` ใช้ทำอะไร

| ไฟล์ | หน้าที่ | การใช้งาน |
| --- | --- | --- |
| `GameServer.exe` | server รับคำสั่ง ตรวจทุกกติกา และส่งสถานะให้ผู้เล่น | เปิดก่อนและเปิดค้าง |
| `GameClient.exe` | หน้าต่างเกม อ่านปุ่ม ส่งคำสั่ง และวาดภาพ | เปิดหลัง server |
| `GameWorldTests.exe` | ตรวจสอบกติกาอัตโนมัติสำหรับผู้พัฒนา ไม่มีหน้าต่างเกม | รันจาก PowerShell |
| `Game.exe` | ไฟล์เก่าที่ไม่มีซอร์ส/คำสั่ง build ปัจจุบันอ้างถึง | ไม่ใช้ |
| `ClientTest.exe` | ไฟล์เก่าที่ไม่มีซอร์ส/คำสั่ง build ปัจจุบันอ้างถึง | ไม่ใช้ |
| `ServerTest.exe` | ไฟล์เก่าที่ไม่มีซอร์ส/คำสั่ง build ปัจจุบันอ้างถึง | ไม่ใช้ |

ไฟล์ที่ใช้เล่นจริงคือ `GameServer.exe` และ `GameClient.exe` เท่านั้น

จุดที่ปรับแต่ง

แก้แล้วต้อง build `GameClient.exe` ใหม่ตามคำสั่งด้านล่างก่อนเปิดเล่น

| อยากแก้ | ไฟล์/จุดที่แก้ | หมายเหตุ |
| --- | --- | --- |
| สีพื้นหลัง หัวข้อ สนาม และแผงด้านขวา | `src/Client/GameRenderer.cpp` ตัวแปร `BackgroundColor`, `HeaderColor`, `ArenaColor`, `SidePanelColor`, `BorderColor` |
| สีตัวผู้เล่น/คนอื่น/คนล้ม | `GameRenderer.cpp` ฟังก์ชัน `DrawPlayer` | ตัวเราใช้ `LIGHTGRAY`, คนอื่น `GRAY`, คนล้ม `ORANGE` |
| สีและขนาดแถบ HP | `GameRenderer.cpp` ฟังก์ชัน `DrawPlayerPanel` | แก้สี `DrawRectangle` และความกว้าง 190 ได้ |
| ตำแหน่ง/ขนาดสนาม | `GameRenderer.cpp` ค่าคงที่ `ArenaX`, `ArenaY`, `ArenaWidth`, `ArenaHeight` | ถ้าเปลี่ยน offset ต้องแก้ offset ใน `ClientInput.cpp` ให้ตรงกัน |
| ข้อความบนหน้าจอ | `GameRenderer.cpp` ฟังก์ชัน `Draw` 
| ปุ่มเดิน | `src/Client/ClientInput.cpp` ฟังก์ชัน `ClientInput::Read` | เปลี่ยน `KEY_W`, `KEY_A`, `KEY_S`, `KEY_D` |
| ปุ่มเก็บ/ชุบ | `ClientInput.cpp` ใน `collectPressed` และ `reviveHeld` | `IsKeyPressed` คือกดครั้งเดียว, `IsKeyDown` คือกดค้าง |
| ปุ่มโจมตี | `ClientInput.cpp` เงื่อนไข `IsMouseButtonPressed(MOUSE_BUTTON_LEFT)` | เปลี่ยนเป็นปุ่มเมาส์อื่นได้ |
| ความเร็วเดิน | `src/Player/Movement/PlayerMovement.cpp` ค่าเริ่มต้น `250.0f` | เป็นกฎฝั่ง server ต้อง build `GameServer.exe` และ test ใหม่ด้วย |
| ความเสียหายจากการโจมตี | `src/Network/NetworkServer.cpp` ค่า `20.0f` ตอนเรียก `DamagePlayer` | เป็นกฎฝั่ง server ไม่ใช่แค่การวาดจอ |
| ระยะเก็บของ/ชุบ และเวลา | `src/Game/GameWorld.cpp` ค่าคงที่ `ItemRange`, `ReviveRange`, `ReviveDuration`, `ItemRespawnSeconds` | แก้แล้วต้อง build server และ `GameWorldTests.exe` |

ถ้าแก้เฉพาะสีหรือข้อความ ให้ build client อย่างเดียวก็พอ ถ้าแก้กติกาเกมให้ build server และรัน `GameWorldTests.exe` ตรวจอีกครั้ง

Build  C++

ใช้ C++17, Raylib และ ENet ผ่าน MSYS2 UCRT64:

```powershell
g++ -std=c++17 -I./src src/server_main.cpp src/Network/NetworkServer.cpp src/Game/GameWorld.cpp src/Player/Player.cpp src/Player/Movement/PlayerMovement.cpp src/Player/Health/PlayerHealth.cpp src/Player/Inventory/PlayerInventory.cpp -o GameServer.exe -lenet -lws2_32 -lwinmm
g++ -std=c++17 -I./src src/main.cpp src/Game/Game.cpp src/Client/ClientInput.cpp src/Client/GameRenderer.cpp src/Network/NetworkClient.cpp -o GameClient.exe -lraylib -lenet -lopengl32 -lgdi32 -lwinmm
g++ -std=c++17 -I./src src/Test/GameWorldTests.cpp src/Game/GameWorld.cpp src/Player/Player.cpp src/Player/Movement/PlayerMovement.cpp src/Player/Health/PlayerHealth.cpp src/Player/Inventory/PlayerInventory.cpp -o GameWorldTests.exe
```

บรรทัดแรกสร้าง server (กติกา+เครือข่าย ไม่ต้องวาดจอ), บรรทัดสองสร้าง client (Raylib+เครือข่าย ไม่ตัดสิน HP เอง), บรรทัดสามสร้าง test (กติกาอย่างเดียว จึงไม่มีหน้าต่าง) `-I./src` คือที่อยู่ header, `-o` คือชื่อไฟล์ผลลัพธ์, `-lenet`/`-lraylib` คือไลบรารีที่ต้องเชื่อม ส่วน `.exe` เก่า 3 ตัวด้านบนไม่มีคำสั่ง build ในโปรเจกต์นี้
