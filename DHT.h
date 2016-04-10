#include <Arduino.h>

#define TYPE_DHT11 1
#define TYPE_DHT22 2

class DHT {
	public:
		float tempC = 0, tempF = 0, humidity = 0;
		
		DHT();
		bool read(int pin, int type) ;
		
	private:
		char tmpData[5] = {0, 0, 0, 0, 0};
		
		bool read_dht11(int pin) ;
}
;