/* 4‑bit LED Up‑Counter  (GPIO 16,17,18,19)
 * Yatharth’s “binary blinkenlights” demo – one tick every 250 ms.
 */

const uint8_t ledPins[4] = {16, 17, 18, 19};   // LSB … MSB
uint8_t count = 0;                              // 0‑15 and wrap

void setup() {
  for (uint8_t i = 0; i < 4; ++i) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], HIGH);   // start with everything OFF
  }
}

void loop() {
  // show count (invert bits because LEDs are active‑LOW)
  for (uint8_t bit = 0; bit < 4; ++bit) {
    digitalWrite(ledPins[bit], bitRead(count, bit) ? LOW : HIGH);
  }

  delay(250);                       // half‑second tick
  count = (count + 1) & 0x0F;       // next value, wrap at 15
}
 