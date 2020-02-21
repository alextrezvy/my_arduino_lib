/*
 * TimestampProvider.h
 * An interface to share the same timestamp global variable between several objects.
 *
 */

#ifndef TIMESTAMPPROVIDER_H_
#define TIMESTAMPPROVIDER_H_

class TimestampProvider {
public:
	virtual unsigned long getTimestamp() const = 0;
	virtual ~TimestampProvider(){};
};

#endif /* TIMESTAMPPROVIDER_H_ */
