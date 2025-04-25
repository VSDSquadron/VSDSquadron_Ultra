/*
 * esp32c6_read_flash_id.ino
 * Reads an external SPI-flash JEDEC ID (0x9F) and prints it.
 * Works on ESP32-C6 WROOM DevKit, Arduino-ESP32 core 3.x+
 */

#include <SPI.h>

constexpr uint8_t SCK_PIN  = 21;   // HSPI SCLK
constexpr uint8_t MOSI_PIN = 19;   // HSPI MOSI
constexpr uint8_t MISO_PIN = 20;   // HSPI MISO
constexpr uint8_t CS_PIN   = 18;   // Chip-Select – wire to flash /CS

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);          // sanity blink
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);

  Serial.begin(115200);
  delay(200);                            // give USB-CDC a moment

  Serial.println(F("\n🛠️  ESP32-C6 external-flash probe"));
  Serial.println(F("hello, world – the serial port is alive!\n"));

  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, CS_PIN);
  SPI.beginTransaction(SPISettings(20'000'000, MSBFIRST, SPI_MODE0));

  digitalWrite(CS_PIN, LOW);
  SPI.transfer(0x9F);                    // JEDEC-ID command
  uint8_t mf  = SPI.transfer(0);
  uint8_t mem = SPI.transfer(0);
  uint8_t cap = SPI.transfer(0);
  digitalWrite(CS_PIN, HIGH);
  SPI.endTransaction();

  Serial.printf("JEDEC ID  : %02X %02X %02X\r\n", mf, mem, cap);
  Serial.printf("Combined  : 0x%02X%02X%02X\r\n\n", mf, mem, cap);

  // Quick double-blink = success
  for (int i = 0; i < 2; ++i) {
    digitalWrite(LED_BUILTIN, HIGH); delay(120);
    digitalWrite(LED_BUILTIN, LOW);  delay(120);
  }
}

void loop() {
  // heartbeat blink every 2 s
  digitalWrite(LED_BUILTIN, HIGH); delay(100);
  digitalWrite(LED_BUILTIN, LOW);  delay(1900);
}
