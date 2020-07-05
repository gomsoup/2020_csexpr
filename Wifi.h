#pragma once
#include <SoftwareSerial.h>
#include "ESP8266.h"

#define debug true

#define SSID "Gaybar"
#define PWD "gaykingg"
#define PORT 3000

#define WIFI_RX 7
#define WIFI_TX 8

class Wifi {
public:
	IPAddress host = IPAddress(192,168,0,3);
	SoftwareSerial esp8266 = SoftwareSerial(WIFI_RX, WIFI_TX);
	ESP8266 wifi = ESP8266(esp8266);

	Wifi();

	void WiFiInit();
	boolean WiFiConnectAP();
	boolean WiFiConnectHost();

	void getAPConfiguration();
	void send(String msg);
};

String getStatus(int res);