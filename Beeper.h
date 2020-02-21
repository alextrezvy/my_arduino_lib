/*
 * Beeper.h
 * Generates a periodic tone until stop() is called.
 */

#ifndef BEEPER_H_
#define BEEPER_H_
#include <Arduino.h>

enum Level {
	low,
	high
};

class Beeper {
private:
	byte pin;
	bool isBeeping;
	Level currentLevel;
	unsigned long lastChange;
	unsigned int frequency;
	unsigned int period;

public:
	Beeper(byte pin);
	void start(unsigned int frequency, unsigned int period);
	void stop();
	void update();
};

#endif /* BEEPER_H_ */
