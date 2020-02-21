/*
 * Template class for loading/saving settings data from/to EEPROM.
 */

#ifndef SETTINGSPROVIDER_H_
#define SETTINGSPROVIDER_H_

#include <Arduino.h>
#include <EEPROM.h>

//#define DEBUG

template<class T>
class SettingsProvider {
private:
	unsigned int addrCurrent;
	const unsigned int addrLastAvailable;
public:
	SettingsProvider() : addrLastAvailable(EEPROM.length() - sizeof(T)) {
		addrCurrent = addrLastAvailable + 1;
	}
	void load(T &data);
	void save(T &data);
};

template<class T>
inline void SettingsProvider<T>::load(T &data) {
	// looking for existing data
	unsigned int addr;
	for (addr = 0; addr <= addrLastAvailable; addr++) {
		if (EEPROM.read(addr) != 0xFF)
			break;
	}
	if (addr <= addrLastAvailable) {
		EEPROM.get(addr, data);
		addrCurrent = addr;
	}
	#ifdef DEBUG
		Serial.print("Settings<T>::load: sizeof(T)=");
		Serial.println(sizeof(T));
		Serial.print("Settings<T>::load: addrCurrent=");
		Serial.println(addrCurrent);
	#endif
}

template<class T>
inline void SettingsProvider<T>::save(T &data) {
	if (addrCurrent <= addrLastAvailable) {
		EEPROM.write(addrCurrent++, 0xFF);
	}
	if (addrCurrent > addrLastAvailable) {
		addrCurrent = 0;
	}
	EEPROM.put(addrCurrent, data);
	#ifdef DEBUG
		Serial.print("Settings<T>::save: addrCurrent=");
		Serial.println(addrCurrent);
	#endif
}

#endif /* SETTINGSPROVIDER_H_ */
