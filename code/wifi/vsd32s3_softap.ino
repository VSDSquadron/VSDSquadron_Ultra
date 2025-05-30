/***************************************************************************
 *  vsd32s3_softap.ino
 *  Bring up ESP32-C3 as a Wi-Fi Access Point:  SSID = “VSD32-S3”,  PASS = “vsd12345”
 ***************************************************************************/

// ------------ user-configurable section ----------------------------------
const char  AP_SSID[] = "VSD32-S3";
const char  AP_PASS[] = "vsd12345";
const uint8_t AP_CHANNEL = 1;       // 1-13 (most countries)
const uint8_t AP_ENCRYPT = 3;       // 0=open, 2=WPA_PSK, 3=WPA2_PSK, 4=WPA/WPA2
const uint32_t BAUD_RATE  = 115200;
const uint32_t CMD_TIMEOUT = 3000;  // ms ­– wait for replies
// -------------------------------------------------------------------------

#include "UARTClass.h"

// UART-0 (console) already exists as Serial
UARTClass Serial1(1);               // UART-1 link to ESP32-C3 AT firmware

/*-------------------------------------------------------------*/
/* Helper: send AT command, append CR/LF, mirror reply to PC   */
void send_command(const char *cmd)
{
  Serial1.print(cmd);
  Serial1.print("\r\n");

  unsigned long t0 = millis();
  while (millis() - t0 < CMD_TIMEOUT) {
    while (Serial1.available()) {
      Serial.write(Serial1.read());
      t0 = millis();               // keep window open while data flows
    }
  }
}
/*-------------------------------------------------------------*/
void setup()
{
  Serial.begin(BAUD_RATE);          // PC console
  Serial1.begin(BAUD_RATE);         // ESP32-C3 link
  delay(500);

  Serial.println("\n=== ESP32-C3 Soft-AP bring-up ===");

  send_command("AT");               // ping firmware
  send_command("ATE0");             // echo off (optional)

  send_command("AT+CWMODE=2");      // 2 = Soft-AP mode

  // Configure the Access Point
  char cmd[128];
  snprintf(cmd, sizeof(cmd),
           "AT+CWSAP=\"%s\",\"%s\",%u,%u",
           AP_SSID, AP_PASS, AP_CHANNEL, AP_ENCRYPT);
  send_command(cmd);

  // Optional: show IP address (defaults to 192.168.4.1)
  send_command("AT+CIFSR");

  Serial.println("\nSoft-AP ready — clients can now join “VSD32-S3”.");
}

void loop()
{
  /* Nothing else to do; the ESP32-C3 keeps the AP alive.
     If you need more commands later, just call send_command() here. */
}
