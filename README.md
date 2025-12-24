# WiFi LoRa 32 V3 - Learning Repository

This repository is dedicated to learning about LoRa development and ESP32 programming using the **Heltec WiFi LoRa 32 V3** development board in the Arduino IDE.

## 📡 About the Board

The Heltec WiFi LoRa 32 V3 is a powerful development board featuring:
- **ESP32-S3FN8** chip (dual-core Xtensa LX7 processor)
- **SX1262** LoRa transceiver (supports 433MHz/470-510MHz/863-870MHz/902-928MHz bands)
- **0.96" OLED Display** (128x64 pixels)
- **WiFi & Bluetooth** connectivity
- **USB-C** interface
- **Li-Po battery management** with charging circuit

🛒 [Purchase Link](https://a.co/d/23w1kb1)

## 🚀 Quick Start

1. **Setup Arduino IDE** - Follow [docs/SETUP.md](docs/SETUP.md) for detailed installation instructions
2. **Hardware Overview** - Learn about the board in [docs/HARDWARE.md](docs/HARDWARE.md)
3. **Getting Started** - Begin with [docs/GETTING_STARTED.md](docs/GETTING_STARTED.md)
4. **Try Examples** - Explore the [examples/](examples/) directory

## 📂 Repository Structure

```
WiFi-LoRa-32-V4-testing/
├── examples/               # Arduino sketch examples
│   ├── LoRa_Sender/       # Basic LoRa transmitter
│   ├── LoRa_Receiver/     # Basic LoRa receiver
│   └── LoRa_PingPong/     # Bidirectional communication example
├── docs/                   # Documentation
│   ├── SETUP.md           # Arduino IDE setup guide
│   ├── HARDWARE.md        # Hardware documentation
│   └── GETTING_STARTED.md # Getting started guide
└── README.md              # This file
```

## 📖 Examples

### Basic Examples
- **LoRa_Sender**: Simple LoRa transmitter that sends packets periodically
- **LoRa_Receiver**: Simple LoRa receiver that listens for incoming packets
- **LoRa_PingPong**: Two-way communication example (ping-pong between two devices)

## 🔧 Development Goals

This repository serves as a learning platform for:
- Understanding LoRa communication protocols
- Working with the ESP32-S3 microcontroller
- Using the Arduino IDE for embedded development
- Implementing wireless communication projects
- Exploring the SX1262 LoRa transceiver capabilities

## 📚 Resources

- [Heltec Official Documentation](https://heltec.org/project/wifi-lora-32-v3/)
- [LoRa Alliance](https://lora-alliance.org/)
- [ESP32-S3 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-s3_datasheet_en.pdf)
- [SX1262 Datasheet](https://www.semtech.com/products/wireless-rf/lora-core/sx1262)

## 📝 License

MIT License - Feel free to use this code for learning and development purposes.

## 🤝 Contributing

This is a personal learning repository, but suggestions and improvements are welcome!
