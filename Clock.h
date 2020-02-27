/*
 * Clock.h
 * Incapsulates clock data.
 * Current timestamp is to be get from TimestampProvider.
 * After counting a minute the client is notified by means of the listener object.
 */

#ifndef CLOCK_H_
#define CLOCK_H_
#include <Arduino.h>
#include "TimestampProvider.h"
#include "ClockListener.h"

class Clock {
private:
	byte hours = 0;
	byte minutes = 0;
	unsigned long lastChange = 0;
	TimestampProvider &timestamp;
	ClockListener &listener;

public:
	static const unsigned long HOURS = 24;
	static const unsigned long MINUTES = 60;
	static const unsigned long SECONDS = 60;
	static const unsigned long MILLIS = 1000;
	Clock(TimestampProvider &tsp, ClockListener &listener);
	void initialize(byte hours, byte minutes);
	byte getHours() const;
	byte getMinutes() const;
	void increaseHours();
	void increaseMinutes();
	void update();
};

#endif /* CLOCK_H_ */
