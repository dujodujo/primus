#include "Timer.h"
#include "Game.h"

Timer::Timer(Ogre::Timer* t) :
  timer(t) {
	Timer::reset();
}

Timer::~Timer() {}

long long int Timer::getTicks() {
	int step = timer->getMilliseconds() - start - ticks;
	start += step;
	ticks = (long long int)timer->getMilliseconds() - start;
	return ticks;
}

void Timer::reset() {
	timer->reset();
	start = timer->getMilliseconds();
	ticks = start;
}