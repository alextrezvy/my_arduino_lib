/*
 * Beeper.cpp
 *
 */

#include "Beeper.h"

Beeper::Beeper(byte _pin) :
		pin(_pin),
		isBeeping(false),
		currentLevel(BL_LOW),
		lastChange(0),
		frequency(0),
		period(0) {}

void Beeper::start(unsigned int _frequency, unsigned int _period) {
	frequency = _frequency;
	period = _period;
	tone(pin, frequency);
	lastChange = millis();
	isBeeping = true;
	currentLevel = BL_HIGH;
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
			case BL_LOW:
				tone(pin, frequency);
				currentLevel = BL_HIGH;
				break;
			case BL_HIGH:
				noTone(pin);
				pinMode(pin, INPUT);
				currentLevel = BL_LOW;
				break;
			}
			lastChange += period/2;
		}
	}
}
