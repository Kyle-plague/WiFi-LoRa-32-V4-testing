# Hardware Documentation - Heltec WiFi LoRa 32 V3

## Board Overview

The Heltec WiFi LoRa 32 V3 is an integrated development board combining WiFi, Bluetooth, and LoRa wireless communication capabilities with an OLED display.

![Board Layout](https://resource.heltec.cn/download/WiFi_LoRa_32_V3/HTIT-WB32LA(F)_V3.png)

## Technical Specifications

### Microcontroller
- **Chip**: ESP32-S3FN8
- **CPU**: Dual-core Xtensa LX7 up to 240MHz
- **SRAM**: 512KB
- **Flash**: 8MB
- **PSRAM**: 8MB

### LoRa Module
- **Chip**: Semtech SX1262
- **Frequency Bands**: 
  - 433MHz (CN)
  - 470-510MHz (CN)
  - 863-870MHz (EU)
  - 902-928MHz (US/AU)
- **Transmit Power**: +22dBm max
- **Receiver Sensitivity**: -148dBm
- **Maximum Range**: 5-10km (line of sight, depending on conditions)

### Display
- **Type**: OLED
- **Size**: 0.96 inch
- **Resolution**: 128x64 pixels
- **Driver**: SSD1306
- **Interface**: I2C

### Connectivity
- **WiFi**: 2.4GHz 802.11 b/g/n
- **Bluetooth**: BLE 5.0
- **LoRa**: Long Range radio

### Power
- **USB-C**: 5V power and programming
- **Battery**: JST 1.25mm connector for Li-Po battery
- **Charging**: Built-in battery charging circuit
- **Power Management**: Vext for external peripherals

### GPIO and Interfaces
- **GPIO Pins**: Multiple digital I/O pins
- **ADC**: Multiple analog input channels
- **I2C**: For OLED and expansion
- **SPI**: For LoRa module and expansion
- **UART**: For serial communication

## Pin Mapping

### LoRa Module Pins
```
SX1262 <-> ESP32-S3
NSS    <-> GPIO 8
RESET  <-> GPIO 12
DIO1   <-> GPIO 14
BUSY   <-> GPIO 13
MISO   <-> GPIO 11
MOSI   <-> GPIO 10
SCK    <-> GPIO 9
```

### OLED Display Pins
```
OLED <-> ESP32-S3
SDA  <-> GPIO 17
SCL  <-> GPIO 18
RST  <-> GPIO 21
```

### Other Important Pins
```
Vext Control -> GPIO 36 (Controls power to external peripherals)
LED          -> GPIO 35 (Built-in LED)
Button       -> GPIO 0 (BOOT/FLASH button)
```

### Available GPIO for User Projects
These pins are available for your use:
- GPIO 1, 2, 3, 4, 5, 6, 7
- GPIO 33, 34, 37, 38, 39, 40, 41, 42
- GPIO 45, 46, 47, 48

⚠️ **Note**: Some pins have special functions or boot-time requirements. Refer to the ESP32-S3 datasheet for details.

## Board Features

### Vext Power Control
GPIO 36 controls power to the Vext pin (3.3V output). This is useful for:
- Powering external sensors
- Saving battery by turning off peripherals
- Controlling external devices

Usage:
```cpp
pinMode(Vext, OUTPUT);
digitalWrite(Vext, LOW);  // Turn on Vext (LOW = ON)
digitalWrite(Vext, HIGH); // Turn off Vext (HIGH = OFF)
```

### Battery Management
- JST 1.25mm 2-pin connector for single-cell Li-Po battery
- Built-in charging when USB is connected
- Battery voltage monitoring available via ADC

### OLED Display
The integrated OLED display is perfect for:
- Status information
- Sensor data visualization
- Menu interfaces
- Debugging output

## LoRa Configuration

### Supported Frequency Bands

Select the appropriate frequency band for your region:

| Region | Frequency | Notes |
|--------|-----------|-------|
| USA | 902-928 MHz | ISM band, FCC Part 15 |
| Europe | 863-870 MHz | ETSI EN300.220 |
| China | 433 MHz or 470-510 MHz | Local regulations apply |
| Australia | 915-928 MHz | ACMA regulations |

### LoRa Parameters

Common configurations:

**Long Range (Slower Speed)**
- Spreading Factor: 12
- Bandwidth: 125 kHz
- Coding Rate: 4/5
- Range: Maximum (5-10km)
- Data Rate: ~250 bps

**Short Range (Faster Speed)**
- Spreading Factor: 7
- Bandwidth: 250 kHz
- Coding Rate: 4/5
- Range: ~2km
- Data Rate: ~5470 bps

**Balanced**
- Spreading Factor: 10
- Bandwidth: 125 kHz
- Coding Rate: 4/5
- Range: ~4km
- Data Rate: ~980 bps

## Power Consumption

Typical power consumption:

| Mode | Current |
|------|---------|
| Active WiFi TX | ~200mA |
| Active LoRa TX (+22dBm) | ~120mA |
| Active LoRa RX | ~15mA |
| Light Sleep | ~2-3mA |
| Deep Sleep | ~10-20µA |
| Deep Sleep (minimum) | ~2.5µA |

## Programming Modes

### Normal Operation
- Simply connect via USB-C
- Upload code normally

### Flash/Boot Mode
If automatic upload fails:
1. Hold the "BOOT" button (GPIO0)
2. Press the "RESET" button briefly
3. Release the "BOOT" button
4. Upload your code

## Mechanical Specifications

- **Dimensions**: 25.5mm x 71mm
- **Weight**: ~15g (without battery)
- **Mounting**: 4x mounting holes
- **Antenna**: U.FL/IPEX connector for external antenna (included)

## Safety and Compliance

⚠️ **Important Notes**:
- Always use appropriate antenna for LoRa (never transmit without antenna)
- Comply with local radio regulations
- Do not exceed duty cycle limits in your region
- Use proper ESD precautions when handling the board
- Do not exceed voltage ratings on GPIO pins (3.3V max)

## Resources and Datasheets

- [ESP32-S3 Technical Reference](https://www.espressif.com/sites/default/files/documentation/esp32-s3_technical_reference_manual_en.pdf)
- [SX1262 Datasheet](https://www.semtech.com/products/wireless-rf/lora-core/sx1262)
- [Heltec Official Docs](https://heltec-automation-docs.readthedocs.io/)
- [Schematic Diagram](https://resource.heltec.cn/download/WiFi_LoRa_32_V3/HTIT-WB32LA(F)_V3_Schematic_Diagram.pdf)

## Additional Features

### Antenna Options
- Internal PCB antenna (limited range)
- External antenna via U.FL connector (recommended for better range)

### Development Features
- USB to UART bridge for easy programming
- Boot and Reset buttons
- Status LED
- Built-in OLED for debugging

## Getting Started

Now that you understand the hardware, proceed to:
1. [SETUP.md](SETUP.md) - Set up your development environment
2. [GETTING_STARTED.md](GETTING_STARTED.md) - Build your first project
3. `examples/` - Try example sketches
