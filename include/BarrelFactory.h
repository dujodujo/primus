#ifndef BARREL_FACTORY_H
#define BARREL_FACTORY_H

#include "MovableEntityFactory.h"

class Barrel;
class Game;

class BarrelFactory : public MovableEntityFactory {

protected:
	std::vector<Barrel*> barrels;

public:
	BarrelFactory();
	~BarrelFactory();

	Barrel* createBarrel(Ogre::Vector3 position, const std::string& name,
		Ogre::Quaternion orientation, Ogre::Real speed, Ogre::Radian turnSpeed);

	std::vector<Barrel*> getBarrels();
};

#endif