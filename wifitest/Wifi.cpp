#include "Wifi.h"

Wifi::Wifi() {
}

void Wifi::WiFiInit()
{
#ifdef debug
	Serial.begin(9600);
#endif
	wifi = ESP8266(esp8266);

	Serial.println("WiFiInit...");
	esp8266.begin(9600);
	wifi.begin();
	wifi.setTimeout(5000);
#ifdef debug
	wifi.setMode(ESP8266_WIFI_STATION);
	wifi.quitAP();
#endif

  wifi.restart();
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
	if (res == "OK") {
	  return true;
    send("HIDA");
    send("HIDA");
	}
  
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
  ESP8266ConnectionStatus connectionStatus;
  ESP8266Connection connections[5];
  unsigned int connectionCount;
  Serial.print("getAPConfiguration: ");
  Serial.print(getStatus(wifi.getConnectionStatus(connectionStatus, connections, connectionCount)));
  Serial.print(" : ");
  Serial.println(connectionCount);
  for (int i = 0; i < connectionCount; i++) {
    Serial.print(" - Connection: ");
    Serial.print(connections[i].id);
    Serial.print(" - ");
    Serial.print(getProtocol(connections[i].protocol));
    Serial.print(" - ");
    Serial.print(connections[i].ip);
    Serial.print(":");
    Serial.print(connections[i].port);
    Serial.print(" - ");
    Serial.println(getRole(connections[i].role));
  }
}

void Wifi::send(String msg){
  Serial.println("WIFI_SEND: " + msg);
	String res = getStatus(wifi.send(msg));
  
  while(!wifi.available()) {}

  char c[11];
  wifi.read(c, 1000);
  String buf(c);

  if(buf.length() > 0) Serial.println("WIFI_RECV : " + buf);
}

String getRole(ESP8266Role role)
{
  switch (role) {
    case ESP8266_ROLE_CLIENT:
      return "CLIENT";
      break;
 
    case ESP8266_ROLE_SERVER:
      return "SERVER";
      break;
 
    default:
      return "UNKNOWN ROLE";
      break;
  }
}
 
String getProtocol(ESP8266Protocol protocol)
{
  switch (protocol) {
    case ESP8266_PROTOCOL_TCP:
      return "TCP";
      break;
 
    case ESP8266_PROTOCOL_UDP:
      return "UDP";
      break;
 
    default:
      return "UNKNOWN PROTOCOL";
      break;
  }
}
