#include "Wifi.h"
#include "SerialManager.h"

Wifi wifi = Wifi();

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  wifi.WiFiInit();
  delay(500);
  wifi.WiFiConnectAP();
  wifi.WiFiConnectHost();
  wifi.getAPConfiguration();
  Serial.println("WIFI SETUP DONE");
}

void loop() {
  wifi.send("PASS");
  delay(5000);
}
