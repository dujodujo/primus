#ifndef PENGUIN_FACTORY_H
#define PENGUIN_FACTORY_H

#include "MovableEntityFactory.h"

class Penguin;
class Game;

class PenguinFactory : public MovableEntityFactory {

protected:
	std::vector<Penguin*> penguins;

public:
	PenguinFactory();
	~PenguinFactory();

	Penguin* createPenguin(Ogre::Vector3 position, const std::string& name,
		Ogre::Quaternion orientation, Ogre::Real speed, Ogre::Radian turnSpeed);

	std::vector<Penguin*> getPenguins();
};

#endif