# Co-op Arena — เซิร์ฟเวอร์เป็นผู้ตัดสิน (Authoritative Server)

เกมสนามประลองมุมมองจากด้านบน ไคลเอนต์ Raylib เชื่อมต่อไปยัง ENet dedicated server โดยไคลเอนต์ส่งได้เพียงอินพุต ส่วนตำแหน่ง พลังชีวิต ช่องเก็บของ การเก็บไอเท็ม และผลการชุบชีวิตเป็นสถานะที่เซิร์ฟเวอร์คำนวณและส่งกลับมา

## โครงสร้างโปรเจกต์

ส่วน Core (`GameWorld`, `Player`, `PlayerMovement`, `PlayerHealth`, `PlayerInventory`, `Vector2D`) เป็น C++17 ล้วนและไม่มี `raylib.h` จึงใช้ใน dedicated server ได้โดยไม่ต้องมีหน้าต่างกราฟิก

`NetworkServer` เป็นเจ้าของ `GameWorld` สร้างผู้เล่นเมื่อ ENet peer join จริง กำหนด ID ตามลำดับ แล้วประมวลผลคำสั่งตามลำดับที่ได้รับ ก่อนส่ง `NetworkMatchSnapshot` ซึ่งเป็นสถานะจริงให้ทุกไคลเอนต์ ผู้เล่นที่ยังไม่ join จะไม่ถูกวาดบนแผนที่ รองรับสูงสุด 16 คนต่อเซิร์ฟเวอร์ (ปรับ `GameWorld::PlayerCount` ได้)

ส่วน Client แบ่งหน้าที่แบบ OOP ดังนี้:

- `Game` ควบคุมวงรอบโปรแกรมและประสานส่วนต่าง ๆ
- `ClientInput` อ่านคีย์บอร์ดและสร้าง `ClientInputState`
- `NetworkClient` รับ/ส่ง ENet และเก็บ snapshot ล่าสุด
- `GameRenderer` วาดสนาม ผู้เล่น ไอเท็ม HUD และแถบชุบชีวิตจาก snapshot เท่านั้น

ไคลเอนต์ส่งแกนการเคลื่อนที่ ปุ่มเก็บ/ใช้แบบกดครั้งเดียว สถานะกดชุบค้าง และหมายเลขลำดับคำสั่ง (sequence number) เซิร์ฟเวอร์ไม่เชื่อ player ID ในแพ็กเก็ต แต่ใช้ peer ที่เชื่อมต่ออยู่แทน และทิ้งแพ็กเก็ตเก่าหรือซ้ำ

## กติกาและการตรวจสอบคำสั่ง

ผู้เล่นมี 3 สถานะ: `Alive`, `Downed`, `Dead` เมื่อ HP เป็นศูนย์ ผู้เล่นจะ Downed ก่อน ผู้เล่น Downed หรือ Dead เคลื่อนที่ เก็บไอเท็ม ใช้ไอเท็ม และชุบไม่ได้ ส่วน Dead ชุบกลับไม่ได้

กล่องสีทองเป็นไอเท็มชุบชีวิต ผู้เล่นต้องอยู่ในระยะจึงเก็บได้ด้วย E และไอเท็มจะสุ่มเกิดใหม่หลังถูกเก็บ 5 วินาที การเก็บพร้อมกันแก้ด้วยลำดับที่เซิร์ฟเวอร์ได้รับ: คนแรกที่คำสั่งถูกต้องรับไอเท็มและไอเท็มหายไป คำสั่งหลังจากนั้นหรือคำสั่งซ้ำจะไม่เปลี่ยนสถานะ

ผู้เล่น Alive ต้องมีกล่องชุบชีวิตและกด E ค้างใกล้เพื่อนที่ Downed เป็นเวลา 2 วินาทีเพื่อชุบให้มี 40 HP ความคืบหน้าอยู่บนเซิร์ฟเวอร์และจะยกเลิกทันทีเมื่อปล่อย E, ออกนอกระยะ, เป้าหมายไม่ Downed แล้ว หรือผู้ชุบ/เป้าหมายได้รับดาเมจ การคลิกผู้เล่นคนอื่นจะส่งคำสั่งโจมตีที่ server ตรวจสอบและลด HP เป้าหมาย 20 หน่วย

## การบิลด์ (MSYS2 UCRT64)

เปิด PowerShell ที่โฟลเดอร์โปรเจกต์ แล้วรัน:

```powershell
g++ -std=c++17 -I./src src/server_main.cpp src/Network/NetworkServer.cpp src/Game/GameWorld.cpp src/Player/Player.cpp src/Player/Movement/PlayerMovement.cpp src/Player/Health/PlayerHealth.cpp src/Player/Inventory/PlayerInventory.cpp -o GameServer.exe -lenet -lws2_32 -lwinmm
g++ -std=c++17 -I./src src/main.cpp src/Game/Game.cpp src/Client/ClientInput.cpp src/Client/GameRenderer.cpp src/Network/NetworkClient.cpp -o GameClient.exe -lraylib -lenet -lopengl32 -lgdi32 -lwinmm
g++ -std=c++17 -I./src src/Test/GameWorldTests.cpp src/Game/GameWorld.cpp src/Player/Player.cpp src/Player/Movement/PlayerMovement.cpp src/Player/Health/PlayerHealth.cpp src/Player/Inventory/PlayerInventory.cpp -o GameWorldTests.exe
```

## วิธีลองเล่นเอง

1. เปิด PowerShell หน้าต่างที่ 1 แล้วรัน `./GameServer.exe` — ต้องเห็นข้อความว่า server ฟังที่ port 27015
2. เปิด PowerShell หน้าต่างที่ 2 รัน `./GameClient.exe` — หน้าต่างเกมแรกจะเป็น Player 1 (สีน้ำเงิน)
3. เปิด PowerShell หน้าต่างที่ 3 รัน `./GameClient.exe` — หน้าต่างเกมที่สองจะเป็น Player 2 (สีแดง)
4. เดินด้วย WASD, เดินเข้าหากล่องสีทองแล้วกด E เพื่อเก็บ, กด E ค้างใกล้เพื่อนที่ล้มเพื่อชุบ, และคลิกผู้เล่นคนอื่นเพื่อลด HP 20 หน่วย

หากเซิร์ฟเวอร์อยู่เครื่องอื่น ให้ใช้ `./GameClient.exe 192.168.1.10` แทน โดยพอร์ตคือ `27015` และต้องอนุญาต firewall ให้ UDP port นี้

## วิธีรันเทสต์

หลังบิลด์ตามคำสั่งด้านบน ให้รัน:

```powershell
./GameWorldTests.exe
```

ผลที่ถูกต้องคือ `GameWorld rule tests passed` เทสต์นี้ไม่เปิดหน้าต่างและไม่ต้องรัน server โดยครอบคลุมการปฏิเสธการเคลื่อนที่/ใช้ไอเท็มเมื่อ Downed หรือ Dead, ช่องว่าง, การแย่งและการส่งซ้ำของการเก็บไอเท็ม, revive เมื่อไกลหรือตาย, การปล่อยปุ่มชุบ และการโดนดาเมจระหว่างชุบ

## ข้อจำกัดปัจจุบัน

snapshot ยังไม่มี interpolation, สถานะแมตช์ไม่คงอยู่เมื่อผู้เล่นหลุด และจำนวนผู้เล่นถูกกำหนดเป็น 16 คนเพื่อควบคุมขนาดแพ็กเก็ต ENet
