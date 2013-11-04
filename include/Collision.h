#ifndef COLLISION_H
#define COLLISION_H

#include "Util.h"


class MovableEntity;

class Collision {

private:
	MovableEntity* targetEntity;
	MovableEntity* sourceEntity;

	Ogre::Vector3 velocity;
	Ogre::Real collisionSpeed;

public:
	Ogre::Vector3 move;
	
public:
	Collision(MovableEntity* entityA, MovableEntity* entityB);
	~Collision();
	
	Ogre::Vector3 getVelocity() { return velocity; }

	void update(Ogre::Real dt);
};

#endif