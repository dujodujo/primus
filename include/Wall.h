#ifndef WALL_H
#define WALL_H

#include "Game.h"
#include "Plane.h"

class Wall : public Plane {

protected:
	Ogre::Plane plane;

public:
	Wall(Ogre::Real width, Ogre::Real height, Ogre::Vector3& position, 
		Ogre::Vector3& direction);
	~Wall();

	virtual void update() {};
};

#endif