// #define DEBUG
#define DEBUG_OUTPUT Serial

#include "DHT.h"

DHT::DHT() {

}

bool DHT::read(int pin, int type) {
	tempC = tempF = humidity = 0;
	
	bool ros = false;
	switch (type) {
		case TYPE_DHT11:
			ros = read_dht11(pin);
			break;
		default:
			ros = false;
	}
	return ros;
}

bool DHT::read_dht11(int pin) {
	char bit = digitalPinToBitMask(pin);
	char port = digitalPinToPort(pin);
	volatile uint8_t *PRT = portInputRegister(port);
	
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	delay(20);
	digitalWrite(pin, HIGH);
	delayMicroseconds(40);
	pinMode(pin, INPUT_PULLUP);
	
	int timeCount=0;
	while((*PRT & bit) == HIGH && timeCount<255) {
		timeCount++;
		delayMicroseconds(1);
	}

	if (timeCount<255) {
		for (int i=0;i<41;i++) {
			timeCount=0;
			while((*PRT & bit) == LOW) ;
			while((*PRT & bit) != LOW && timeCount < 255) {
				timeCount++;
				delayMicroseconds(1);
			}
			
			if (timeCount >= 255)
				break;
				
			if (i>0 && i<42) {
				tmpData[(i-1) / 8] <<= 1;
				tmpData[(i-1) / 8] |= (timeCount>16 ? 1 : 0);
			}
		}
	}
	
#ifdef DEBUG
    DEBUG_OUTPUT.println("timeCount: " + String(timeCount));
	DEBUG_OUTPUT.println("tmpData[0]: " + String(tmpData[0], HEX));
	DEBUG_OUTPUT.println("tmpData[1]: " + String(tmpData[1], HEX));
	DEBUG_OUTPUT.println("tmpData[2]: " + String(tmpData[2], HEX));
	DEBUG_OUTPUT.println("tmpData[3]: " + String(tmpData[3], HEX));
	DEBUG_OUTPUT.println("tmpData[4]: " + String(tmpData[4], HEX));
#endif
	
	if (timeCount >= 255 || (tmpData[4] != ((tmpData[0] + tmpData[1] + tmpData[2] + tmpData[3])&0xFF))) {
		tempC = tempF = humidity = 0;
		return false;
	}
	
	humidity = tmpData[0];
	tempC = tmpData[2];
	tempF =  tempC * 9.0 / 5.0 + 32.0;
	
	return true;
}