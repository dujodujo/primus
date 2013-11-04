#include "Sphere.h"


Sphere::Sphere() :
  radius(1.f),
  center(Ogre::Vector3::ZERO) {
}

Sphere::Sphere(Ogre::Real x, Ogre::Real y, Ogre::Real z, Ogre::Real radius) :
  radius(radius),
  center(Ogre::Vector3(x, y, z)) {
}

Sphere::Sphere(Ogre::Vector3& position, Ogre::Real radius) :
  radius(radius),
  center(position) {
}

bool Sphere::intersects(const Sphere& sphere) const {
	return (sphere.center - this->center).length() <= sphere.radius + this->radius;
}

bool Sphere::contains(const Sphere& sphere) const {
	return (sphere.center - this->center).length() + sphere.radius <= this->radius;
}

bool Sphere::contains(const Ogre::Vector3& point) const {
	return (point - this->center).length() <= this->radius;
}

Ogre::Real Sphere::distance(const Sphere& sphere) {
	Ogre::Real dist = (sphere.center - this->center).length() - this->radius - sphere.radius;
	return dist;
}

void Sphere::update(Ogre::Vector3& position) {
	center = position;
}