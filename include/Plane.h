#ifndef PLANE_H
#define PLANE_H

#include "Util.h"

class Plane {

protected:
	Ogre::Real width;
	Ogre::Real height;
	Ogre::Real planeArea;

public:
	Plane(Ogre::Real w, Ogre::Real h);
	virtual ~Plane();

	Ogre::Real getWidth();
	Ogre::Real getHeight();

	virtual void update() = 0;
};

#endif