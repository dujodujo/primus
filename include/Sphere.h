#ifndef SPHERE_H
#define SPHERE_H

#include "Util.h"

struct Sphere {

	Ogre::Vector3 center;
	Ogre::Real radius;

	Sphere();
	Sphere(Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Real radius);
	Sphere(Ogre::Vector3& position, Ogre::Real radius);

	bool intersects(const Sphere& sphere) const;
	bool contains(const Sphere& sphere) const;
	bool contains(const Ogre::Vector3& point) const;

	Ogre::Real distance(const Sphere& sphere);

	void update(Ogre::Vector3& position);
};

#endif