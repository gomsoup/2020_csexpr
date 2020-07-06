#pragma once
#include <SoftwareSerial.h>
#include "ESP8266.h"

#define debug false

#define SSID "iPhone"
#define PWD "123456789a"
#define PORT 4000

#define WIFI_RX 7
#define WIFI_TX 8

class Wifi {
public:
	IPAddress host = IPAddress(15,164,39,255);
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
String getRole(ESP8266Role role);
String getProtocol(ESP8266Protocol protocol);
