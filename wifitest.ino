#include "Wifi.h"
#include "SerialManager.h"

Wifi wifi = Wifi();
SerialManager bt = SerialManager(2, 3);

void setup() {
  // put your setup code here, to run once:
  wifi.WiFiInit();
  wifi.WiFiConnectAP();
  wifi.WiFiConnectHost();

  Serial.println("WIFI SETUP DONE");
  wifi.send("\n\r");

  
}

void loop() {
  if(Serial.available()){
    char msg = Serial.read();
    if(msg != 'O')
      wifi.send("URGT");
  }
  // put your main code here, to run repeatedly:
}
