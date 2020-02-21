/*
 * ClockListener.h
 *
 */

#ifndef CLOCKLISTENER_H_
#define CLOCKLISTENER_H_

class ClockListener {
public:
	virtual void notify() const = 0;
	virtual ~ClockListener(){};
};

#endif /* CLOCKLISTENER_H_ */
