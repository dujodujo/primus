#include "GameController.h"

GameController::GameController() : 
  turnRate(0.f),
  throttle(0.f),
  pointerPosition(Ogre::Vector3(0,0,0)) {
}

GameController::~GameController() {}

void GameController::setThrottle(Ogre::Real throttle) {
	this->throttle = throttle;
	if(throttle > 1) {
		throttle = 1;
	} else if(throttle < -1) {
		throttle = -1;
	}
}

Ogre::Real GameController::getThrottle() const {
	return throttle;
}

void GameController::setTurnRate(Ogre::Real turnRate) {
	this->turnRate = turnRate;
}

Ogre::Real GameController::getTurnSpeed() const {
	return turnRate;
}