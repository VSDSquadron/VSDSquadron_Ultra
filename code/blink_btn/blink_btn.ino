/* 4‑bit Manual Up/Down Counter (GPIO 16‑19 LEDs, 20=Up, 21=Down)
 * LOW = button pressed (INPUT_PULLUP)
 * LEDs are active‑LOW: LOW=ON, HIGH=OFF
 */

 const uint8_t ledPins[4]  = {16, 17, 18, 19};  // LSB … MSB
 const uint8_t btnUpPin    = 21;               // increment
 const uint8_t btnDownPin  = 20;               // decrement
 uint8_t count = 0;                            // 0 – 15
 
 void setup() {
   // LEDs off (HIGH) and inputs with pull‑ups
   for (uint8_t i = 0; i < 4; ++i) {
     pinMode(ledPins[i], OUTPUT);
     digitalWrite(ledPins[i], HIGH);
   }
   pinMode(btnUpPin,   INPUT_PULLUP);
   pinMode(btnDownPin, INPUT_PULLUP);
 }
 
 void updateLEDs() {
   // Invert bits: 1→LOW(on), 0→HIGH(off)
   for (uint8_t bit = 0; bit < 4; ++bit) {
     bool bitVal = bitRead(count, bit);
     digitalWrite(ledPins[bit], bitVal ? LOW : HIGH);
   }
 }
 
 void loop() {
   if (digitalRead(btnUpPin) == LOW) {
     count = (count + 1) & 0x0F;   // wrap 0–15
     updateLEDs();
     delay(200);                   // crude debounce
   }
   if (digitalRead(btnDownPin) == LOW) {
     count = (count - 1) & 0x0F;   // underflow wraps, thanks to &0x0F
     updateLEDs();
     delay(200);
   }
 }
 