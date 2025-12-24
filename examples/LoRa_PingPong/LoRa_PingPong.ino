/*
 * LoRa Ping-Pong Example
 * 
 * This example demonstrates two-way LoRa communication using the
 * Heltec WiFi LoRa 32 V3 board.
 * 
 * Two devices alternate sending "ping" and "pong" messages to each other.
 * When a device receives a message, it waits briefly and responds.
 * 
 * Features:
 * - Automatic role assignment (first to transmit becomes initiator)
 * - RSSI display
 * - Round-trip time calculation
 * - Packet counter
 * 
 * Hardware Required:
 * - Two Heltec WiFi LoRa 32 V3 boards
 * - External antennas connected to both boards
 * 
 * Instructions:
 * 1. Connect external antennas to both boards
 * 2. Set BAND to your region's frequency
 * 3. Upload to both boards
 * 4. Power on both boards (one starts as initiator)
 * 5. Watch them ping-pong!
 * 
 * Author: Learning Repository
 * License: MIT
 */

#include "heltec.h"

// LoRa frequency - MUST BE SAME ON BOTH DEVICES
// 433E6 for Asia
// 868E6 for Europe
// 915E6 for North America/Australia
#define BAND 915E6

// State machine
enum State {
  IDLE,
  WAIT_FOR_RESPONSE,
  SEND_RESPONSE
};

State currentState = IDLE;

// Packet tracking
unsigned int packetCounter = 0;
unsigned int receivedCounter = 0;

// Timing
unsigned long lastSendTime = 0;
unsigned long sendInterval = 2000;  // Initial send interval
unsigned long roundTripStart = 0;
unsigned long roundTripTime = 0;

// Data
String lastMessage = "";
int lastRSSI = 0;
bool isMaster = false;

void setup() {
  // Initialize Heltec board
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
  Heltec.display->drawString(0, 0, "LoRa Ping-Pong");
  Heltec.display->drawString(0, 10, "Initializing...");
  Heltec.display->display();
  
  // Configure LoRa parameters
  LoRa.setSpreadingFactor(10);      // SF10
  LoRa.setSignalBandwidth(125E3);   // 125 kHz
  LoRa.setCodingRate4(5);           // 4/5
  LoRa.setPreambleLength(8);        // 8 symbols
  LoRa.setSyncWord(0x12);           // Private network
  LoRa.setTxPower(17, RF_PACONFIG_PASELECT_PABOOST);
  
  // Set to receive mode
  LoRa.receive();
  
  Serial.println("LoRa Ping-Pong Initialized");
  Serial.print("Frequency: ");
  Serial.print(BAND / 1E6);
  Serial.println(" MHz");
  
  // Decide role based on a delay
  // One device will start sending first (becomes master)
  randomSeed(analogRead(0));
  unsigned long startDelay = random(1000, 3000);
  
  Serial.print("Starting in ");
  Serial.print(startDelay);
  Serial.println(" ms");
  
  delay(startDelay);
  
  // Check if we've received anything
  if (LoRa.parsePacket() == 0) {
    // Nothing received, we'll be the master (initiator)
    isMaster = true;
    currentState = IDLE;
    lastSendTime = 0; // Will send immediately
    Serial.println("Role: MASTER (Initiator)");
  } else {
    // Received something, we're slave (responder)
    isMaster = false;
    currentState = IDLE;
    Serial.println("Role: SLAVE (Responder)");
  }
  
  updateDisplay();
}

void loop() {
  // Check for incoming packets
  int packetSize = LoRa.parsePacket();
  
  if (packetSize) {
    // Packet received
    receivedCounter++;
    
    // Read message
    lastMessage = "";
    while (LoRa.available()) {
      lastMessage += (char)LoRa.read();
    }
    
    lastRSSI = LoRa.packetRssi();
    
    // Calculate round-trip time if we're waiting for response
    if (currentState == WAIT_FOR_RESPONSE) {
      roundTripTime = millis() - roundTripStart;
    }
    
    // Print received data
    Serial.println("Received: " + lastMessage);
    Serial.print("RSSI: ");
    Serial.print(lastRSSI);
    Serial.println(" dBm");
    
    if (currentState == WAIT_FOR_RESPONSE) {
      Serial.print("Round-trip: ");
      Serial.print(roundTripTime);
      Serial.println(" ms");
    }
    
    // Change state to send response
    currentState = SEND_RESPONSE;
    lastSendTime = millis();
    
    // Blink LED
    digitalWrite(LED, HIGH);
    delay(50);
    digitalWrite(LED, LOW);
    
    updateDisplay();
  }
  
  // State machine
  switch (currentState) {
    case IDLE:
      // If master, send first ping after interval
      if (isMaster && (millis() - lastSendTime > sendInterval)) {
        sendPing();
        currentState = WAIT_FOR_RESPONSE;
      }
      break;
      
    case WAIT_FOR_RESPONSE:
      // Waiting for response - handled by packet reception above
      // Timeout after 10 seconds
      if (millis() - roundTripStart > 10000) {
        Serial.println("Timeout waiting for response");
        currentState = IDLE;
        updateDisplay();
      }
      break;
      
    case SEND_RESPONSE:
      // Wait a bit before responding
      if (millis() - lastSendTime > 500) {
        sendPong();
        currentState = WAIT_FOR_RESPONSE;
      }
      break;
  }
  
  delay(10);
}

void sendPing() {
  packetCounter++;
  
  String message = "Ping #" + String(packetCounter);
  
  Serial.println("Sending: " + message);
  
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();
  
  roundTripStart = millis();
  lastSendTime = millis();
  
  // Blink LED
  digitalWrite(LED, HIGH);
  delay(50);
  digitalWrite(LED, LOW);
  
  updateDisplay();
}

void sendPong() {
  packetCounter++;
  
  String message = "Pong #" + String(packetCounter);
  
  Serial.println("Sending: " + message);
  
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();
  
  roundTripStart = millis();
  lastSendTime = millis();
  
  // Blink LED
  digitalWrite(LED, HIGH);
  delay(50);
  digitalWrite(LED, LOW);
  
  updateDisplay();
}

void updateDisplay() {
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  
  // Title
  Heltec.display->drawString(0, 0, "LoRa Ping-Pong");
  
  // Role
  String role = isMaster ? "Role: Master" : "Role: Slave";
  Heltec.display->drawString(0, 12, role);
  
  // Stats
  String stats = "TX:" + String(packetCounter) + " RX:" + String(receivedCounter);
  Heltec.display->drawString(0, 24, stats);
  
  // Last message
  if (lastMessage.length() > 0) {
    String msg = lastMessage;
    if (msg.length() > 18) {
      msg = msg.substring(0, 18);
    }
    Heltec.display->drawString(0, 36, msg);
  }
  
  // RSSI
  if (lastRSSI != 0) {
    Heltec.display->drawString(0, 48, "RSSI: " + String(lastRSSI) + " dBm");
  }
  
  // Round-trip time
  if (roundTripTime > 0 && currentState != WAIT_FOR_RESPONSE) {
    Heltec.display->drawString(70, 48, "RTT:" + String(roundTripTime) + "ms");
  }
  
  Heltec.display->display();
}
