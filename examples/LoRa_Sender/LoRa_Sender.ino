/*
 * LoRa Sender Example
 * 
 * This example demonstrates basic LoRa transmission using the
 * Heltec WiFi LoRa 32 V3 board.
 * 
 * The sketch sends a packet every few seconds containing:
 * - A counter value
 * - A message string
 * 
 * Hardware Required:
 * - Heltec WiFi LoRa 32 V3 board
 * - External antenna connected to U.FL connector
 * 
 * Instructions:
 * 1. Connect external antenna to the board
 * 2. Set BAND to your region's frequency
 * 3. Upload to your board
 * 4. Open Serial Monitor at 115200 baud
 * 5. Watch OLED display for status
 * 
 * Author: Learning Repository
 * License: MIT
 */

#include "heltec.h"

// LoRa frequency - CHANGE THIS FOR YOUR REGION
// 433E6 for Asia
// 868E6 for Europe
// 915E6 for North America/Australia
#define BAND 915E6

// Packet counter
unsigned int packetCounter = 0;

// Timing
unsigned long lastSendTime = 0;
unsigned long sendInterval = 3000; // Send packet every 3 seconds

void setup() {
  // Initialize Heltec board
  // Parameters: (Display, LoRa, Serial, PABOOST, LoRa Frequency)
  Heltec.begin(
    true,  // DisplayEnable - Enable OLED
    true,  // LoRa Enable - Enable LoRa
    true,  // Serial Enable - Enable Serial output
    true,  // PABOOST - Use PA_BOOST for transmit
    BAND   // LoRa frequency
  );
  
  // Display welcome message
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 0, "LoRa Sender");
  Heltec.display->drawString(0, 10, "Initializing...");
  Heltec.display->display();
  
  // Configure LoRa parameters
  LoRa.setSpreadingFactor(10);      // SF10 (7-12, higher=longer range)
  LoRa.setSignalBandwidth(125E3);   // 125 kHz bandwidth
  LoRa.setCodingRate4(5);           // 4/5 coding rate
  LoRa.setPreambleLength(8);        // 8 symbols
  LoRa.setSyncWord(0x12);           // Private network sync word
  LoRa.setTxPower(17, RF_PACONFIG_PASELECT_PABOOST); // 17dBm output power
  
  Serial.println("LoRa Sender Initialized");
  Serial.print("Frequency: ");
  Serial.print(BAND / 1E6);
  Serial.println(" MHz");
  Serial.println("Starting transmission...");
  
  delay(1000);
}

void loop() {
  // Check if it's time to send another packet
  if (millis() - lastSendTime > sendInterval) {
    sendLoRaPacket();
    lastSendTime = millis();
  }
  
  // Small delay to prevent excessive CPU usage
  delay(10);
}

void sendLoRaPacket() {
  // Build the message
  String message = "Hello LoRa #" + String(packetCounter);
  
  // Print to Serial
  Serial.println("Sending packet: " + message);
  
  // Send LoRa packet
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();
  
  // Update display
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  
  Heltec.display->drawString(0, 0, "LoRa Sender");
  Heltec.display->drawString(0, 15, "Packets Sent:");
  Heltec.display->drawString(0, 28, String(packetCounter));
  Heltec.display->drawString(0, 41, "Last: " + String(packetCounter));
  Heltec.display->drawString(0, 54, "Power: 17dBm");
  
  Heltec.display->display();
  
  // Increment counter
  packetCounter++;
  
  // Blink LED to indicate transmission
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
}
