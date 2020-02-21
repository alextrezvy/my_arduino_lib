/*
 *  Class incapsulates routines for displaying of N digit number on a 7-segment LED display.
 *	Class also allows to toggle additional LEDs with common cathode,
 *	connected in parallel with a digit (pinPosition).
 *  "display()" method displays one number at a time.
 *
 *  "NOS" stands for "number of segments" (per digit).
 *  "NOD" stands for "number of digits" (in display).
 */

#ifndef UVCOUNTERDISPLAY_H
#define UVCOUNTERDISPLAY_H
#include <Arduino.h>

enum BlinkState {
	off,
	on
};

template<byte NOS, byte NOD>
class UVCounterDisplay {
private:
	static const byte DIGITS[];
	byte pinSegment[NOS];  // toggles a segment
	byte pinPosition[NOD]; // toggles a digit or LED at a position
	byte currentDigits[NOD];// representation of the value
	boolean isLed[NOD];     // is i-th LED ON or OFF
	byte position; // a digit to display
	byte pinCathode; // common cathode for both LEDs
	bool isBlinking;
	unsigned long blinkPeriod;
	BlinkState blinkState;
	unsigned long lastChange;

public:
	UVCounterDisplay(
			const byte _pinSeg[NOS],
			const byte _pinPos[NOD],
			const byte _pinCathode) {
		for (byte i=0; i < NOS; i++) {
			pinSegment[i] = _pinSeg[i];
		}
		for (byte i=0; i < NOD; i++) {
			pinPosition[i] = _pinPos[i];
			currentDigits[i] = 0;
			isLed[i] = false;
		}
		position = 0;
		pinCathode = _pinCathode;
		isBlinking = false;
		blinkState = off;
		blinkPeriod = 0;
		lastChange = 0;
		pinMode(pinCathode, OUTPUT);
	}

	/**
	 * "led" is an index of a digit connected to LED  (0...3).
	 */
	void ledOn(byte led) {
		isLed[led] = true;
	}

	/**
	 * "led" is an index of a digit connected to LED  (0...3).
	 */
	void ledOff(byte led) {
		isLed[led] = false;
	}


	void setValue(unsigned int _value) {
		for (byte i=0; i < NOD; i++) {
			currentDigits[i] = _value % 10;
			_value = _value / 10;
		}
	}

	void display() {
		// turning off all positions
		for (byte i=0; i < NOD; i++) {
			pinMode(pinPosition[i], OUTPUT);
			digitalWrite(pinPosition[i], HIGH);
		}
		bool showValue;
		if (!isBlinking) {
			showValue = true;
		} else {
			if (millis() > lastChange + blinkPeriod/2) {
				switch (blinkState) {
				case off:
					blinkState = on;
					break;
				case on:
					blinkState = off;
					break;
				}
				lastChange = millis();
			}
			showValue = blinkState == on ? true : false;
		}
		if (showValue) {
			byte symbol = DIGITS[currentDigits[position]];
			for (byte i=0; i < NOS; i++) {
				pinMode(pinSegment[i], OUTPUT);
				digitalWrite(pinSegment[i], bitRead(symbol, i));
			}
			digitalWrite(pinPosition[position], LOW);
			// toggling LEDs
			digitalWrite(pinCathode, isLed[position] ? LOW : HIGH);
			position++;
			if (position == NOD)
				position = 0;
		}
	}

	void blinkStart(const unsigned int period = 500) {
		isBlinking = true;
		blinkState = off;
		blinkPeriod = period;
		lastChange = millis();
	}

	void blinkStop() {
		isBlinking = false;
	}

};


#endif
