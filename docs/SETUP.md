# Arduino IDE Setup Guide

This guide will help you set up the Arduino IDE for development with the Heltec WiFi LoRa 32 V3 board.

## Prerequisites

- Arduino IDE 2.0 or later (recommended) or Arduino IDE 1.8.x
- USB-C cable for connecting the board
- Computer with Windows, macOS, or Linux

## Step 1: Install Arduino IDE

### Download and Install

1. Visit the [Arduino IDE download page](https://www.arduino.cc/en/software)
2. Download the appropriate version for your operating system
3. Install the Arduino IDE following the installer instructions

## Step 2: Install ESP32 Board Support

### Add ESP32 Board Manager URL

1. Open Arduino IDE
2. Go to **File** → **Preferences** (or **Arduino IDE** → **Settings** on macOS)
3. In the "Additional Board Manager URLs" field, add:
   ```
   https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/releases/download/0.0.7/package_heltec_esp32_index.json
   ```
   
   **Note**: If you already have URLs there, separate them with commas or use the window icon to add a new line.

4. Click **OK** to save

### Install Heltec ESP32 Boards

1. Go to **Tools** → **Board** → **Boards Manager**
2. In the search box, type `Heltec ESP32`
3. Find "**Heltec ESP32 Series Dev-boards**" in the results
4. Click **Install** (this may take several minutes)
5. Wait for the installation to complete

## Step 3: Select Your Board

1. Connect your Heltec WiFi LoRa 32 V3 board to your computer via USB-C
2. Go to **Tools** → **Board** → **Heltec ESP32 Arduino**
3. Select **"WiFi LoRa 32(V3)"** from the list

## Step 4: Configure Board Settings

After selecting the board, configure these settings in the **Tools** menu:

- **Board**: "WiFi LoRa 32(V3)"
- **Upload Speed**: "921600"
- **CPU Frequency**: "240MHz (WiFi/BT)"
- **Flash Frequency**: "80MHz"
- **Flash Mode**: "QIO"
- **Flash Size**: "8MB (64Mb)"
- **Partition Scheme**: "Default 4MB with spiffs (1.2MB APP/1.5MB SPIFFS)"
- **Core Debug Level**: "None" (or "Info" for debugging)
- **PSRAM**: "QSPI PSRAM"
- **Port**: Select the COM port (Windows) or /dev/cu.* (macOS) or /dev/ttyUSB* (Linux) that appears when you connect the board

## Step 5: Install Required Libraries

### Automatic Installation (Recommended)

The Heltec board package includes the necessary libraries. However, you may want to install additional libraries:

1. Go to **Tools** → **Manage Libraries** or **Sketch** → **Include Library** → **Manage Libraries**
2. Search for and install these libraries:
   - **Heltec ESP32 Dev-Boards** (should already be installed)
   - **RadioLib** (optional, for advanced LoRa features)

### Manual Verification

The required libraries should be automatically available:
- `LoRa.h` - For LoRa communication
- `heltec.h` - For board initialization
- `U8g2lib.h` - For OLED display

## Step 6: Install USB Drivers (If Needed)

### Windows Users

If your board is not recognized:

1. Download and install [CP210x USB to UART Bridge VCP Drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)
2. Restart your computer after installation
3. Reconnect the board

### macOS Users

Modern macOS versions typically include the necessary drivers. If your board is not recognized:

1. Download drivers from the Silicon Labs website
2. You may need to allow the driver in **System Preferences** → **Security & Privacy**

### Linux Users

Most Linux distributions include the necessary drivers. If needed:

```bash
sudo usermod -a -G dialout $USER
```

Log out and log back in for the changes to take effect.

## Step 7: Test Your Setup

1. Open **File** → **Examples** → **Heltec ESP32 Dev-Boards** → **LoRa** → **LoRaSender**
2. Click the **Upload** button (right arrow icon) or press **Ctrl+U** (Cmd+U on macOS)
3. Wait for the sketch to compile and upload
4. The OLED display should show "LoRa Sender" and transmit packets

## Troubleshooting

### Board Not Detected

- Try a different USB cable (some cables are charging-only)
- Try a different USB port
- Install/reinstall USB drivers
- Hold the "Boot" button while connecting the USB cable

### Compilation Errors

- Verify you have selected the correct board: **WiFi LoRa 32(V3)**
- Check that the Heltec ESP32 board package is properly installed
- Update the board package to the latest version
- Close and restart Arduino IDE

### Upload Fails

- Hold the "Boot" button (GPIO0) during upload
- Lower the upload speed to 115200
- Check that the correct COM port is selected
- Press the "Reset" button before uploading

### Out of Memory Errors

- Change Partition Scheme to one with more app space
- Remove unused libraries and code

## Additional Resources

- [Heltec Official Documentation](https://heltec-automation-docs.readthedocs.io/)
- [Arduino IDE Documentation](https://docs.arduino.cc/)
- [ESP32 Arduino Core Documentation](https://docs.espressif.com/projects/arduino-esp32/)

## Next Steps

Once your setup is complete:
1. Review [HARDWARE.md](HARDWARE.md) to understand the board's capabilities
2. Follow [GETTING_STARTED.md](GETTING_STARTED.md) for your first project
3. Try the examples in the `examples/` directory
