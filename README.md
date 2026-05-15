# MeshSat-X — Satellite-Based Mesh Network Communication

## Overview

MeshSat-X is an ESP32-based wireless communication system using LoRa technology for long-range data transmission and GPS-based location tracking.

The project demonstrates:

* LoRa wireless communication
* GPS integration using TinyGPS++
* OLED display interfacing
* UART communication
* Real-time message transmission
* Basic satellite/mesh-network inspired communication architecture

Two ESP32 boards are used:

* Transmitter Node (TX)
* Receiver Node (RX)

---

# Features

## Transmitter Node

* Sends LoRa messages wirelessly
* Reads live GPS coordinates
* Displays transmitted message and GPS data on OLED
* Uses UART-based GPS communication

---

## Receiver Node

* Receives LoRa packets
* Displays received data on OLED
* Shows RSSI signal strength
* Activates LED and buzzer on packet reception
* Displays GPS data locally

---

# Hardware Used

## Components

* ESP32 Development Board
* LoRa SX1278 Module (433 MHz)
* Neo-6M GPS Module
* SSD1306 OLED Display
* Buzzer
* LED
* Jumper Wires

---

# Technologies Used

* Arduino Framework
* SPI Communication
* I2C Communication
* UART Communication
* LoRa Wireless Communication
* TinyGPS++ Library
* Adafruit SSD1306 Library

---

# Pin Configuration

## LoRa Module

| ESP32 Pin | LoRa Pin |
| --------- | -------- |
| 18        | NSS/SS   |
| 14        | RST      |
| 26        | DIO0     |
| 23        | MOSI     |
| 19        | MISO     |
| 5         | SCK      |

---

## GPS Module

| ESP32 Pin | GPS |
| --------- | --- |
| 16        | RX  |
| 17        | TX  |

---

## OLED Display

| ESP32 Pin | OLED |
| --------- | ---- |
| 21        | SDA  |
| 22        | SCL  |

---

# Working Principle

## Transmitter Side

1. ESP32 reads GPS coordinates from Neo-6M module.
2. Message is transmitted through LoRa module.
3. OLED displays:

   * transmitted message
   * latitude
   * longitude

---

## Receiver Side

1. ESP32 continuously scans for LoRa packets.
2. Upon receiving:

   * message is displayed on OLED
   * RSSI signal strength is shown
   * buzzer and LED activate
3. GPS coordinates are also displayed locally.

---

# Concepts Demonstrated

* Long-range wireless communication
* Mesh-network inspired architecture
* Embedded communication systems
* GPS tracking
* Real-time monitoring
* Multi-protocol interfacing
* IoT and satellite communication concepts

---

# Libraries Used

```text id="psn0l5"
SPI.h
LoRa.h
TinyGPS++.h
Wire.h
Adafruit_GFX.h
Adafruit_SSD1306.h
```

---

# Future Improvements

* Multi-node mesh routing
* Actual satellite uplink integration
* AES encryption for secure communication
* Sensor data transmission
* Battery-powered remote nodes
* MQTT/cloud integration
* Autonomous drone communication support

---

# Applications

* Disaster communication systems
* Remote telemetry
* Wildlife monitoring
* UAV/drone communication
* IoT sensor networks
* Satellite-inspired mesh communication
* Rural communication systems

---

# Author

Sanchit Bhojwani
B.Tech Electronics and Communication Engineering (ECE)
Embedded Systems | Robotics | IoT | Wireless Communication
