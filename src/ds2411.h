#ifndef DS2411_H
#define DS2411_H

/* Arduino libraries */
#include <Arduino.h>

/* C liraries */
#include <errno.h>

class ds2411 {

public:
	ds2411();
	void setup(const int pin);
	int read(uint8_t bytes[8]);

private:
	bool m_pin_defined;
	int m_pin;
};

#endif
