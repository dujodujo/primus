#include "Plane.h"
#include "Game.h"

Plane::Plane(Ogre::Real width, Ogre::Real height) :
  width(width),
  height(height),
  planeArea(width * height) {

}

Plane::~Plane() {}

Ogre::Real Plane::getWidth() {
	return this->width;
}

Ogre::Real Plane::getHeight() {
	return this->height;
}
