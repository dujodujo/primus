#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "Util.h"

class Collision;
class MovableEntity;
class Sphere;

struct collisionPair {
	collisionPair(MovableEntity* te, MovableEntity* se) : 
		targetEntity(te), 
		sourceEntity(se) {}
	MovableEntity* targetEntity;
	MovableEntity* sourceEntity;
};

class CollisionHandler {

private:
	std::vector<collisionPair> possibleCollisions;
	std::vector<Collision*> collisions;
	std::list<MovableEntity*> entities;

public:
	CollisionHandler();
	~CollisionHandler();

	void addEntities(MovableEntity* entity);
	void removeEntities(MovableEntity* entity);

	void updateCollisions();
	void detectCollisions();

	void update(Ogre::Real dt);
};

#endif