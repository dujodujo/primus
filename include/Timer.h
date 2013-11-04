#ifndef TIMER_H
#define TIMER_H

#include "Util.h"
#include <OgreTimer.h>

class Timer {

protected:
	long long int start;
	long long int ticks;
	Ogre::Timer* timer;

public:
	Timer(Ogre::Timer* timer);
	~Timer();

	long long int getTicks();
	void reset();
};

#endif