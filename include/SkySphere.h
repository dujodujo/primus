#ifndef SKY_SPHERE_H
#define SKY_SPHERE_H

#include <Ogre.h>
#include "Game.h"

class SkySphere {

protected:
	Ogre::Real radius;

public:
	SkySphere(const std::string& material, Ogre::Real radius);
	~SkySphere();

	void loadSphere();

	void setVisible(bool visible);
	void update(Ogre::Real radius);
};

#endif