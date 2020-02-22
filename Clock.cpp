/*
 * Clock.cpp
 *
 *  Created on: 1 февр. 2020 г.
 *      Author: user
 */

#include "Clock.h"

Clock::Clock(TimestampProvider &_tsp, ClockListener &_listener) :
	timestamp(_tsp),
	listener(_listener){

}

byte Clock::getHours() const {
	return hours;
}

byte Clock::getMinutes() const {
	return minutes;
}

void Clock::increaseHours() {
	++hours;
	if (hours == HOURS)
		hours = 0;
	lastChange = timestamp.getTimestamp();
}

void Clock::increaseMinutes() {
	++minutes;
	if (minutes == MINUTES)
		minutes = 0;
	lastChange = timestamp.getTimestamp();
}

void Clock::update() {
	if (timestamp.getTimestamp() >= (lastChange + SECONDS*MILLIS)) {
		++minutes;
		if (minutes == MINUTES) {
			minutes = 0;
			++hours;
			if (hours == HOURS) {
				hours = 0;
			}
		}
		listener.notify();
		lastChange += SECONDS*MILLIS;
	}
}

void Clock::initialize(byte _hours, byte _minutes) {
	hours = _hours < HOURS ? _hours : 0;
	minutes = _minutes < MINUTES ? _minutes : 0;
	lastChange = timestamp.getTimestamp();
}
