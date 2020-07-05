#include "Wifi.h"

Wifi::Wifi() {
}

void Wifi::WiFiInit()
{
#ifdef debug
	Serial.begin(9600);
#endif
	//wifi = ESP8266(esp8266);

	Serial.println("WiFiInit...");
	esp8266.begin(9600);
	wifi.begin();
	wifi.setTimeout(1000);

#ifdef debug
	wifi.setMode(ESP8266_WIFI_STATION);
	wifi.quitAP();
#endif
}


boolean Wifi::WiFiConnectAP() {
	Serial.println("WiFiConnectAP...");
	String res = getStatus(wifi.joinAP(SSID, PWD));
	if (res == "OK") return true;

	Serial.println("AP Connection failed. Result code : " + res);
	Serial.println("Check SSID, PWD in Wifi.h");

	return false;
}

boolean Wifi::WiFiConnectHost() {
	Serial.println("WiFiConnectHost...");
	String res = getStatus(wifi.connect(ESP8266_PROTOCOL_TCP, host, PORT));
	if (res == "OK") return true;

	Serial.println("HOST Connection lost. Result code : " + res);
	Serial.println("Check out HOST is up right now");

	return false;
}

String getStatus(int res) {
	if (res == ESP8266_COMMAND_OK) return "OK";

	switch (res) {
	case ESP8266_COMMAND_ALREADY_CONNECTED:
		return String(ESP8266_COMMAND_ALREADY_CONNECTED) + "(ALREADY CONNECTED)";
		break;
	case ESP8266_COMMAND_ERROR:
		return String(ESP8266_COMMAND_ERROR) + "(ERROR)";
		break;
	case ESP8266_COMMAND_FAIL:
		return String(ESP8266_COMMAND_FAIL) + "(FAIL)";
		break;
	case ESP8266_COMMAND_INVALID:
		return String(ESP8266_COMMAND_INVALID) + "(INVALID)";
		break;
	case ESP8266_COMMAND_NO_CHANGE:
		return String(ESP8266_COMMAND_NO_CHANGE) + "(NO_CHANGE)";
		break;
	case ESP8266_COMMAND_NO_LINK:
		return String(ESP8266_COMMAND_NO_LINK) + "(NO_LINK)";
		break;
	case ESP8266_COMMAND_TIMEOUT:
		return String(ESP8266_COMMAND_TIMEOUT) + "(TIMEOUT)";
		break;
	case ESP8266_COMMAND_TOO_LONG:
		return String(ESP8266_COMMAND_TOO_LONG) + "(TOO_LONG)";
		break;
	default:
		return String(-1) + "UNKNOWN";
	}
}

void Wifi::getAPConfiguration() {
	char ssid[32] = {};
	char password[63] = {};
	uint8_t channel;
	ESP8266Encryption encryption;

	Serial.print("getAPConfiguration: ");
	Serial.print(getStatus(wifi.getAPConfiguration(ssid, password, channel, encryption)));
	Serial.print(" : ");
	Serial.print(ssid);
	Serial.print(" - ");
	Serial.print(password);
	Serial.print(" - ");
	Serial.print(channel);
	Serial.print(" - ");
	Serial.println(encryption);
}

void Wifi::send(String msg){
	wifi.send(msg);
}