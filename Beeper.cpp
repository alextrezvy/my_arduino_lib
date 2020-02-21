/*
 * Beeper.cpp
 *
 */

#include "Beeper.h"

Beeper::Beeper(byte _pin) :
		pin(_pin),
		isBeeping(false),
		currentLevel(low),
		lastChange(0),
		frequency(0),
		period(0) {}

void Beeper::start(unsigned int _frequency, unsigned int _period) {
	frequency = _frequency;
	period = _period;
	tone(pin, frequency);
	lastChange = millis();
	isBeeping = true;
	currentLevel = high;
}

void Beeper::stop() {
	noTone(pin);
	pinMode(pin, INPUT); // supresses noise
	isBeeping = false;
}

void Beeper::update() {
	if (isBeeping) {
		if (millis() > lastChange + period/2) {
			switch (currentLevel) {
			case low:
				tone(pin, frequency);
				currentLevel = high;
				break;
			case high:
				noTone(pin);
				pinMode(pin, INPUT);
				currentLevel = low;
				break;
			}
			lastChange += period/2;
		}
	}
}
