#include "Wifi.h"
#include "SerialManager.h"

Wifi wifi = Wifi();

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  wifi.WiFiInit();
  if(!wifi.WiFiConnectAP()) return;
  if(!wifi.WiFiConnectHost()) return;
  wifi.getAPConfiguration();
  Serial.println("WIFI SETUP DONE");
}

void loop() {
  wifi.send("PASS");
  delay(100);
  wifi.send("URGT");
  delay(100);
  wifi.send("OVRP");
  delay(100);
  // put your main code here, to run repeatedly:
}
