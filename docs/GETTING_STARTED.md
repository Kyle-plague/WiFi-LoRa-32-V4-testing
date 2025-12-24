# Getting Started with LoRa Development

This guide will walk you through your first LoRa project using the Heltec WiFi LoRa 32 V3 board.

## Prerequisites

Before starting, make sure you have:
- ✅ Arduino IDE installed and configured ([SETUP.md](SETUP.md))
- ✅ Heltec WiFi LoRa 32 V3 board
- ✅ USB-C cable
- ✅ External antenna connected to the U.FL connector
- ✅ (Optional) A second board for two-way communication

## Your First LoRa Project

### Understanding LoRa Basics

**LoRa (Long Range)** is a wireless modulation technique that enables:
- **Long-range** communication (5-10km in rural areas, 1-3km in urban)
- **Low power** consumption (ideal for battery-powered devices)
- **Penetration** through buildings and obstacles
- **License-free** operation (ISM bands)

LoRa is perfect for IoT applications like:
- Remote sensor monitoring
- Environmental data collection
- Asset tracking
- Smart agriculture
- Home automation

### LoRa vs LoRaWAN

**LoRa**: The physical layer radio technology (what we're using)
**LoRaWAN**: A network protocol on top of LoRa with gateways and servers

In this repository, we focus on point-to-point LoRa communication.

## Example 1: LoRa Sender

Let's start with a simple transmitter that sends messages.

### What You'll Learn
- How to initialize the board
- How to configure LoRa parameters
- How to transmit data
- How to use the OLED display

### Steps

1. **Open the Sender Example**
   - In Arduino IDE, go to **File** → **Open**
   - Navigate to `examples/LoRa_Sender/LoRa_Sender.ino`
   - Or use **File** → **Examples** → **Heltec ESP32 Dev-Boards** → **LoRa** → **LoRaSender**

2. **Configure for Your Region**
   
   Find this line in the code:
   ```cpp
   #define BAND 915E6  // 915MHz for US/AU
   ```
   
   Change to your region:
   - USA/Australia: `915E6`
   - Europe: `868E6`
   - China: `433E6`

3. **Upload the Code**
   - Connect your board via USB
   - Select the correct board and port in **Tools**
   - Click the Upload button
   - Wait for "Done uploading"

4. **Observe the Output**
   - The OLED display should show "LoRa Sender"
   - You'll see packet numbers incrementing
   - The LED may blink when transmitting

## Example 2: LoRa Receiver

Now let's create a receiver to listen for messages.

### What You'll Learn
- How to receive LoRa packets
- How to read RSSI (signal strength)
- How to handle incoming data

### Steps

1. **Open the Receiver Example**
   - Open `examples/LoRa_Receiver/LoRa_Receiver.ino`

2. **Configure for Your Region**
   
   Use the same frequency as your sender:
   ```cpp
   #define BAND 915E6
   ```

3. **Upload to a Second Board** (or same board if testing separately)
   
4. **Observe the Output**
   - The display shows "LoRa Receiver"
   - When packets arrive, they appear on screen
   - RSSI values show signal strength

## Example 3: LoRa Ping-Pong

For two-way communication between devices.

### What You'll Learn
- Bidirectional communication
- Acknowledgment systems
- Timing and coordination

### Steps

1. **Prepare Two Boards**
   - You need two Heltec boards for this example

2. **Upload to Both Boards**
   - Open `examples/LoRa_PingPong/LoRa_PingPong.ino`
   - Upload to the first board
   - Upload to the second board

3. **Watch Them Communicate**
   - One board sends "ping"
   - The other responds with "pong"
   - They alternate automatically

## Understanding LoRa Parameters

### Frequency
Choose based on your region (see above). Always follow local regulations.

### Spreading Factor (SF)
- Range: SF7 to SF12
- Higher SF = Longer range, slower data rate
- Lower SF = Shorter range, faster data rate
- **Recommendation**: Start with SF10 for balanced performance

### Bandwidth (BW)
- Common values: 125 kHz, 250 kHz, 500 kHz
- Wider bandwidth = Faster transmission, less range
- **Recommendation**: Start with 125 kHz

### Coding Rate (CR)
- Values: 4/5, 4/6, 4/7, 4/8
- Higher CR = More error correction, slower transmission
- **Recommendation**: Start with 4/5

### Transmit Power
- Range: 2-20 dBm (board supports up to 22 dBm)
- Higher power = Longer range, more battery consumption
- **Recommendation**: Start with 17 dBm

### Sync Word
- Private: 0x12 (default)
- Public: 0x34 (LoRaWAN networks)
- Use same sync word for devices to communicate
- **Recommendation**: Use 0x12 for private networks

## Common Code Patterns

### Board Initialization
```cpp
Heltec.begin(
    true,   // DisplayEnable
    true,   // LoRa Enable
    true,   // Serial Enable
    true,   // PABOOST
    BAND    // LoRa frequency
);
```

### Sending Data
```cpp
LoRa.beginPacket();
LoRa.print("Hello LoRa!");
LoRa.endPacket();
```

### Receiving Data
```cpp
int packetSize = LoRa.parsePacket();
if (packetSize) {
    while (LoRa.available()) {
        String data = LoRa.readString();
        Serial.println(data);
    }
    int rssi = LoRa.packetRssi();
}
```

### Display Text
```cpp
Heltec.display->clear();
Heltec.display->drawString(0, 0, "Hello!");
Heltec.display->display();
```

## Testing Your Setup

### Range Test
1. Upload sender to one board
2. Upload receiver to another
3. Start with boards close together
4. Gradually increase distance
5. Note where connection is lost

### Signal Strength
- RSSI values indicate signal strength
- -30 dBm = Excellent (very close)
- -120 dBm = Weak (far away)
- Below -120 dBm = Usually no connection

## Troubleshooting

### No Packets Received
- ✅ Check both boards use same frequency (BAND)
- ✅ Check antenna is connected
- ✅ Check boards are on same spreading factor
- ✅ Check sync word matches
- ✅ Try increasing transmit power
- ✅ Move boards closer together

### Board Not Responding
- Press Reset button
- Re-upload the code
- Check USB connection
- Verify correct board selected in Tools menu

### Display Issues
- OLED needs 1-2 seconds to initialize
- If blank, try adding `delay(1000)` after `Heltec.begin()`
- Check display enable is `true` in `Heltec.begin()`

### Poor Range
- Ensure external antenna is connected
- Check antenna is appropriate for frequency
- Increase spreading factor (SF)
- Increase transmit power
- Check for obstacles
- Test in open area

## Best Practices

### 1. Power Management
```cpp
// Turn on Vext for external peripherals
pinMode(Vext, OUTPUT);
digitalWrite(Vext, LOW);  // ON

// Turn off when not needed
digitalWrite(Vext, HIGH); // OFF
```

### 2. Duty Cycle
Respect duty cycle limits (typically 1% in Europe, 36 seconds per hour):
```cpp
unsigned long lastSendTime = 0;
unsigned long sendInterval = 5000; // 5 seconds

if (millis() - lastSendTime > sendInterval) {
    // Send packet
    lastSendTime = millis();
}
```

### 3. Error Handling
Always check for successful transmission:
```cpp
if (LoRa.beginPacket()) {
    LoRa.print("Data");
    if (LoRa.endPacket()) {
        Serial.println("Sent successfully");
    }
}
```

### 4. Energy Efficiency
```cpp
// Use sleep modes for battery-powered projects
esp_sleep_enable_timer_wakeup(60 * 1000000); // 60 seconds
esp_deep_sleep_start();
```

## Next Steps

Now that you're familiar with the basics:

1. **Modify Examples**: Change parameters and observe effects
2. **Add Sensors**: Connect sensors and transmit readings
3. **Build a Project**: Create a weather station, tracker, or monitoring system
4. **Experiment**: Try different spreading factors, bandwidths, and ranges
5. **Learn More**: Explore WiFi and Bluetooth capabilities

## Project Ideas

### Beginner
- Temperature sensor transmitter
- Door open/close notification
- Button press remote control

### Intermediate
- Weather station with multiple sensors
- GPS tracker
- Remote display for sensor data

### Advanced
- Mesh network with multiple nodes
- Bidirectional sensor control
- Integration with WiFi/MQTT

## Resources

- [LoRa Examples in This Repo](../examples/)
- [Heltec Documentation](https://heltec-automation-docs.readthedocs.io/)
- [LoRa Alliance](https://lora-alliance.org/)
- [RadioLib Library](https://github.com/jgromes/RadioLib) (Advanced)

## Community and Support

- [Heltec Forum](https://community.heltec.cn/)
- [Arduino Forum](https://forum.arduino.cc/)
- [ESP32 Arduino GitHub](https://github.com/espressif/arduino-esp32)

Happy coding! 🚀
