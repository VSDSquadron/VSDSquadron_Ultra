/*
   @file  Flash_ReadJEDEC.ino
   @brief Read JEDEC-ID (0x9F) from an SPI-Flash and print it.

   ▸ Board      : VEGA ARIES (RISC-V)
   ▸ Library    : Built-in <SPI.h>
   ▸ Wiring     : 3 V3 –> 3 V3
                  GND  –> GND
                  MISO –> MISO0
                  MOSI –> MOSI0
                  SCK  –> SCLK0
                  CS   –> GPIO-10   ← change if you prefer another pin
*/

#include <SPI.h>

#define CS_PIN 10          // Chip-Select (flash CS ↔ GPIO-10)
SPIClass SPI(3);           // Use SPI bus 0 on the ARIES

// ─── HELPERS ──────────────────────────────────────────────────────────────
void printHexByte(uint8_t b) {
  if (b < 0x10) Serial.print('0');
  Serial.print(b, HEX);
}

// ─── SET-UP ───────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  while (!Serial) { }                // wait for USB-CDC

  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);        // deselect flash

  SPI.begin();                       // SCLK0/MOSI0/MISO0 auto-configured
  SPI.beginTransaction(SPISettings(
      8'000'000,                     // 8 MHz is comfy for most flashes
      MSBFIRST,
      SPI_MODE0
  ));

  Serial.println(F("\n🛠️  SPI-Flash JEDEC-ID Reader v1.0"));
  Serial.print (F("Wiring: CS→"));
  Serial.println(CS_PIN);
  Serial.println(F("-----------------------------------"));
}

// ─── MAIN LOOP ────────────────────────────────────────────────────────────
void loop() {
  // Pull CS low, issue 0x9F (JEDEC ID), read three bytes
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(0x9F);
  uint8_t mfr  = SPI.transfer(0x00);   // Manufacturer
  uint8_t type = SPI.transfer(0x00);   // Memory type
  uint8_t cap  = SPI.transfer(0x00);   // Capacity
  digitalWrite(CS_PIN, HIGH);

  // Pretty-print once every second
  Serial.print  (F("JEDEC ID  : "));
  printHexByte(mfr);  Serial.print(' ');
  printHexByte(type); Serial.print(' ');
  printHexByte(cap);  Serial.println();

  uint32_t id = (uint32_t)mfr << 16 | type << 8 | cap;
  Serial.print  (F("Combined  : 0x"));
  Serial.println(id, HEX);
  Serial.println();

  delay(1000);                      // Slow it down for readability
}
