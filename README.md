# VSD32-S3 — Flashing AT Firmware over UART

This short guide shows you how to download the **AT firmware** image and flash it onto a **VSD32-S3** board (ESP32-C3 Wi-Fi/BLE module) using Espressif’s *Flash Download Tool*.

> **Before you start**  
> Make sure the hardware is wired exactly as shown in the table below.

| VSD32-S3 signal / pin | Connect to           | Notes                                                  |
|-----------------------|----------------------|--------------------------------------------------------|
| **WiFi_P_Tx**         | FTDI232 **Rx**       | UART TX from VSD32-S3 → FTDI RX                        |
| **WiFi_P_Rx**         | FTDI232 **Tx**       | UART RX on VSD32-S3 ← FTDI TX                          |
| **GND**               | FTDI232 **GND**      | Common ground reference                                |
| **WiFi_P_BOOT**       | VSD32-S3 **GND**     | Keep low to boot ESP32-C3 into normal flash-run mode   |

---

## 1. Download the required files

| File | Purpose | Link |
|------|---------|------|
| **factory_MINI-1.bin** | AT firmware image | <https://github.com/VSDSquadron/VSDSquadron_Ultra/blob/main/factory_MINI-1.bin> |
| **flash_download_tool.zip** | Espressif Flash Download Tool (Windows) | <https://github.com/VSDSquadron/VSDSquadron_Ultra/blob/main/flash_download_tool.zip> |

Unzip **flash_download_tool.zip** somewhere convenient (e.g. `C:\esp\flash_tool\`).

---

## 2. Flash the firmware

1. **Open** `flash_download_tool_x.x.x.exe`.  
2. In the first dialog choose the **ChipType** → `ESP32-C3`.  
3. Choose **WorkMode** → `Develop`.  
4. Choose **LoadMode** → `UART`. (see below image)
5. Click **OK** to enter the main window.  

   ![Flash Download Tool – correct settings](1.png)

---

### 3. Verify the connection with **Chip Debug Tool**

After you click **OK** in step&nbsp;5, a new window titled **CHIP DEBUG TOOL V3.9.8** pops up.

1. Click the **`chipInfoDump`** tab.
2. In the **port** drop-down, choose the COM port that the **VSD32-S3** is attached to  
   (if two ports appear, unplug the board to see which one disappears, then re-select it).
3. Leave **baudrate** at **115200**.
4. Press **Chip Info**.

If everything is wired correctly, the log area should show output similar to:

![Chip Debug Tool – chipInfoDump](2.png)

> **Troubleshooting:**  
> • If “chip sync …” never completes, swap **TX/RX** lines or re-check that **WiFi_P_BOOT** is firmly tied low.  
> • Make sure the COM port isn’t already open in another terminal session.

Continue with step 7 to select the firmware binary and start flashing.
