#include <SPI.h>
#include <LoRa.h>
#include <TinyGPS++.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// LoRa Pins
#define SS    18
#define RST   14
#define DIO0  26

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// GPS
TinyGPSPlus gps;
HardwareSerial GPS_Serial(1);

// Message to send
char  message[] = "HELLO FROM ESP32 TX";

void setup() {
  Serial.begin(115200);

  // GPS init
  GPS_Serial.begin(9600, SERIAL_8N1, 16, 17);

  // OLED init
  Wire.begin(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed");
    while (1);
  }

  // LoRa init
  SPI.begin(5, 19, 23, SS);
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed");
    while (1);
  }

  Serial.println("System Ready");
}

void loop() {

  // Read GPS
  while (GPS_Serial.available()) {
    gps.encode(GPS_Serial.read());
  }

  // 🔹 Send ONLY message via LoRa
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();

  Serial.println("Message Sent");

  // 🔹 OLED Display
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // Show message
  display.setCursor(0, 0);
  display.println("TX Msg:");
  display.println(message);

  // Show GPS locally
  if (gps.location.isValid()) {
    display.setCursor(0, 30);
    display.print("Lat:");
    display.println(gps.location.lat(), 5);

    display.setCursor(0, 50);
    display.print("Lng:");
    display.println(gps.location.lng(), 5);
  } else {
    display.setCursor(0, 40);
    display.println("Waiting GPS...");
  }

  display.display();

  delay(2000);
}