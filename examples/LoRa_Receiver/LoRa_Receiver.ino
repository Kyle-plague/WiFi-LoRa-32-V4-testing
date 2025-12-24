/*
 * LoRa Receiver Example
 * 
 * This example demonstrates basic LoRa reception using the
 * Heltec WiFi LoRa 32 V3 board.
 * 
 * The sketch listens for incoming LoRa packets and displays:
 * - Received message content
 * - RSSI (signal strength)
 * - SNR (signal-to-noise ratio)
 * - Packet count
 * 
 * Hardware Required:
 * - Heltec WiFi LoRa 32 V3 board
 * - External antenna connected to U.FL connector
 * 
 * Instructions:
 * 1. Connect external antenna to the board
 * 2. Set BAND to match your transmitter
 * 3. Upload to your board
 * 4. Open Serial Monitor at 115200 baud
 * 5. Watch OLED display for incoming packets
 * 
 * Author: Learning Repository
 * License: MIT
 */

#include "heltec.h"

// LoRa frequency - MUST MATCH SENDER
// 433E6 for Asia
// 868E6 for Europe
// 915E6 for North America/Australia
#define BAND 915E6

// Packet counter
unsigned int packetCounter = 0;

// Display update
bool newPacketReceived = false;
String lastMessage = "";
int lastRSSI = 0;
float lastSNR = 0;

void setup() {
  // Initialize Heltec board
  // Parameters: (Display, LoRa, Serial, PABOOST, LoRa Frequency)
  Heltec.begin(
    true,  // DisplayEnable - Enable OLED
    true,  // LoRa Enable - Enable LoRa
    true,  // Serial Enable - Enable Serial output
    true,  // PABOOST - Use PA_BOOST
    BAND   // LoRa frequency
  );
  
  // Display welcome message
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 0, "LoRa Receiver");
  Heltec.display->drawString(0, 10, "Initializing...");
  Heltec.display->display();
  
  // Configure LoRa parameters - MUST MATCH SENDER
  LoRa.setSpreadingFactor(10);      // SF10 (7-12)
  LoRa.setSignalBandwidth(125E3);   // 125 kHz bandwidth
  LoRa.setCodingRate4(5);           // 4/5 coding rate
  LoRa.setPreambleLength(8);        // 8 symbols
  LoRa.setSyncWord(0x12);           // Private network sync word
  
  // Set LoRa to receive mode
  LoRa.receive();
  
  Serial.println("LoRa Receiver Initialized");
  Serial.print("Frequency: ");
  Serial.print(BAND / 1E6);
  Serial.println(" MHz");
  Serial.println("Listening for packets...");
  
  delay(1000);
  
  // Update display
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "LoRa Receiver");
  Heltec.display->drawString(0, 15, "Waiting for");
  Heltec.display->drawString(0, 28, "packets...");
  Heltec.display->display();
}

void loop() {
  // Check if a packet has been received
  int packetSize = LoRa.parsePacket();
  
  if (packetSize) {
    // Packet received!
    packetCounter++;
    
    // Read the packet
    lastMessage = "";
    while (LoRa.available()) {
      lastMessage += (char)LoRa.read();
    }
    
    // Get signal quality metrics
    lastRSSI = LoRa.packetRssi();
    lastSNR = LoRa.packetSnr();
    
    // Print to Serial
    Serial.println("==== Packet Received ====");
    Serial.print("Packet #");
    Serial.println(packetCounter);
    Serial.print("Message: ");
    Serial.println(lastMessage);
    Serial.print("RSSI: ");
    Serial.print(lastRSSI);
    Serial.println(" dBm");
    Serial.print("SNR: ");
    Serial.print(lastSNR);
    Serial.println(" dB");
    Serial.print("Size: ");
    Serial.print(packetSize);
    Serial.println(" bytes");
    Serial.println("========================");
    
    // Update display
    updateDisplay();
    
    // Blink LED to indicate reception
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);
  }
  
  // Small delay
  delay(10);
}

void updateDisplay() {
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  
  // Title
  Heltec.display->drawString(0, 0, "LoRa Receiver");
  
  // Packet count
  Heltec.display->drawString(0, 12, "RX: " + String(packetCounter));
  
  // Message (truncate if too long)
  String displayMsg = lastMessage;
  if (displayMsg.length() > 18) {
    displayMsg = displayMsg.substring(0, 18) + "...";
  }
  Heltec.display->drawString(0, 24, displayMsg);
  
  // RSSI
  String rssiStr = "RSSI: " + String(lastRSSI) + " dBm";
  Heltec.display->drawString(0, 36, rssiStr);
  
  // Signal quality indicator
  String quality;
  if (lastRSSI > -50) {
    quality = "Excellent";
  } else if (lastRSSI > -80) {
    quality = "Good";
  } else if (lastRSSI > -100) {
    quality = "Fair";
  } else {
    quality = "Weak";
  }
  Heltec.display->drawString(0, 48, "Signal: " + quality);
  
  Heltec.display->display();
}
