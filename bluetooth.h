#pragma once
#include <SoftwareSerial.h>

class bluetooth {
public:
	SoftwareSerial *bt;
	String name;
	int RX, TX;
	int baudrate = 9600;

	bluetooth(String _name, int _RX, int _TX, int _baudrate) {
		RX = _RX; TX = _TX;
		name = _name;
		baudrate = _baudrate;
		bt = new SoftwareSerial(RX, TX);

		bt->begin(baudrate);
	}
	
	~bluetooth() {
		delete(bt);
	}

	boolean available() {
		return bt->available();
	}

	String bt_read() {
		int stime = millis();
		String buf = "";

		while (millis() - stime < 1000) {
			if (bt->available()) {
				char c = (char)bt->read();
				buf += c;
			}
		}

		return buf;
	}

	void bt_write(String _str) {
		for (int i = 0; i < _str.length(); i++)
			bt->write((char)_str[i]);
		
		delay(50);
	}

	void testSerial() {
		bt_write("AT");
		String buf = bt_read();
		Serial.println(buf);

		if (buf == "OK") Serial.println("BT OK");
		else Serial.println("BT NOT READY");
	}

	void init() {
		Serial.println("--SET NAME--");
		bt_write("AT+NAME" + name);
		Serial.println(bt_read());
		
		Serial.println("--SET PASSWD--");
		bt_write("AT+PIN1234");
		Serial.println(bt_read());
	}

};