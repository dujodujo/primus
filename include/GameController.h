#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "Util.h"

class GameController {

protected:
	Ogre::Real turnRate;
	Ogre::Real throttle;
	Ogre::Vector3 pointerPosition;

public:
	GameController();
	~GameController();

	void setTurnRate(Ogre::Real turnRate);
	Ogre::Real getTurnSpeed() const;

	void setThrottle(Ogre::Real throttle);
	Ogre::Real getThrottle() const;

	void setPointerPosition(Ogre::Vector3 pp) { pointerPosition = pp; }
	Ogre::Vector3 getPointerPosition() { return pointerPosition; }
};

#endif