#include "Collision.h"
#include "MovableEntity.h"

Collision::Collision(MovableEntity* ea, MovableEntity* eb) :
  targetEntity(ea),
  sourceEntity(eb) {
}

Collision::~Collision() {}

void Collision::update(Ogre::Real dt) {
	const Ogre::Real collisionElasticity = 0.2f;
	
	Ogre::Real sourceWeight = sourceEntity->getWeight();
	Ogre::Real targetWeight = targetEntity->getWeight();
	Ogre::Real weight = (sourceWeight + targetWeight);
	
	Ogre::Vector3 sourceVelocity = sourceEntity->getVelocity();
	Ogre::Vector3 targetVelocity = targetEntity->getVelocity();

	Sphere sourceSphere = sourceEntity->getBoundingSphere();
	Sphere targetSphere = targetEntity->getBoundingSphere();

	Ogre::Vector3 collisionVelocity = sourceSphere.center - targetSphere.center;
	collisionVelocity.normalise();

	Ogre::Real depth = sourceSphere.distance(targetSphere);
	
	move = collisionVelocity * (depth + 1.f);
	//sourceEntity->moveEntity(collisionVelocity * depth);
	//targetEntity->moveEntity(-collisionVelocity * depth);

	sourceEntity->handleCollision(this);
	targetEntity->handleCollision(this);
}