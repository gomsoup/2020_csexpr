#pragma once
#include <SoftwareSerial.h>

class SerialManager {
public:
	int RX, TX;
	SoftwareSerial *serial;

	SerialManager();
	SerialManager(int _RX, int _TX) {
		RX = _RX; TX = _TX;
		serial = new SoftwareSerial(RX, TX);
	}

	boolean available() {
		return serial->available();
	}

	String read() {
		unsigned long stime = millis();
		String buf = "";

		while ( (millis() - stime) < 1000) {
			if (serial->available()) {
				char c = (char)serial->read();
				buf += c;
			}
		}

		return buf;
	}

	void write(String msg) {
		for (int i = 0; i < msg.length(); i++)
			serial->write((char)msg[i]);

		delay(10);
	}
};