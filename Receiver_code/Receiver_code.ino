#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TinyGPS++.h>

// Create GPS object
TinyGPSPlus gps;

// Use UART1 of ESP32
HardwareSerial GPS_Serial(1);

// OLED size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// I2C address (usually 0x3C)
#define OLED_ADDR 0x3C

// Create display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define SS    18
#define RST   14
#define DIO0  26

#define LED_PIN    25   // Changed LED pin to 25
#define BUZZER_PIN 22   // Buzzer pin

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);  // SDA, SCL
  GPS_Serial.begin(9600, SERIAL_8N1, 16, 17);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED init failed");
    while (1);
  }
  delay(1000);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  SPI.begin(5, 19, 23, SS);  // MOSI=23, MISO=19, SCK=5
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed");
    while (1);
  }

  Serial.println("LoRa Receiver Ready");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  String received = "";
  display.clearDisplay();
  display.setTextSize(1); 
  display.setTextColor(WHITE);

  while (GPS_Serial.available()) {
    gps.encode(GPS_Serial.read());
  }

  // Check if location is available

  if (packetSize) {
    // Turn ON LED and buzzer
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);

    Serial.print("Received: ");
    while (LoRa.available()) {
      received += (char)LoRa.read();
    }

    Serial.print("Received: ");
    Serial.print(received);

// OLED
    display.setCursor(0, 0);
    display.println("Received:");
    display.println(received);
    Serial.print(" | RSSI: ");
    Serial.println(LoRa.packetRssi());
    display.setCursor(0, 25);
    display.println("RSSI:");
    display.println(LoRa.packetRssi());

    if (gps.location.isValid()) {

    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);

    display.setCursor(0, 40);
    display.println("GPS Latitude:");
    display.println(gps.location.lat());

    display.setCursor(0, 52);
    display.println("GPS Longitude:");
    display.println(gps.location.lng());

    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
  }
    display.display();

    delay(500); // keep LED & buzzer ON for 0.5 sec

    // Turn OFF LED and buzzer
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }
}
