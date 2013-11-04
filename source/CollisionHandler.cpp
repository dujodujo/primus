#include "CollisionHandler.h"
#include "Collision.h"
#include "MovableEntity.h"
#include "Sphere.h"

CollisionHandler::CollisionHandler() {
}

CollisionHandler::~CollisionHandler() {
}

void CollisionHandler::addEntities(MovableEntity* entity) {
	entities.push_back(entity);
}

void CollisionHandler::removeEntities(MovableEntity* entity) {
	entities.remove(entity);
}

void CollisionHandler::update(Ogre::Real dt) {
	updateCollisions();
	detectCollisions();
		
	for(unsigned int i = 0; i < collisions.size(); ++i) {
		collisions[i]->update(dt);
		delete (collisions[i]);
	}
	collisions.clear();
}

void CollisionHandler::updateCollisions() {
	possibleCollisions.clear();

	std::list<MovableEntity*>::iterator sourceEntity;
	std::list<MovableEntity*>::iterator targetEntity;

	for(sourceEntity = entities.begin(); sourceEntity != entities.end(); ++sourceEntity) {
		//const Ogre::AxisAlignedBox* firstbox = (*sourceEntity)->getBoundingBox();
		Sphere firstSphere = (*sourceEntity)->getBoundingSphere();
		for(targetEntity = entities.begin(); targetEntity != entities.end(); ++targetEntity) {
			//const Ogre::AxisAlignedBox* secondbox = (*targetEntity)->getBoundingBox();
			Sphere secondSphere = (*targetEntity)->getBoundingSphere();
			//check if entities are different
			if((*sourceEntity) != (*targetEntity)) {
				//check if collision is already on the list
				if(!(*targetEntity)->collisionDetected(*sourceEntity)) {
					//check if collision is already on the list
					if(firstSphere.intersects(secondSphere)) {
						(*sourceEntity)->addCollisionEntity(*targetEntity);
						possibleCollisions.push_back(collisionPair(*sourceEntity, *targetEntity));
					}
				}
			}
		}
	}
}

void CollisionHandler::detectCollisions() {
	for(unsigned int i = 0; i < possibleCollisions.size(); ++i) {
		MovableEntity* source = possibleCollisions[i].sourceEntity;
		MovableEntity* target = possibleCollisions[i].targetEntity;

		const Ogre::AxisAlignedBox* sourceBox = source->getBoundingBox();
		const Ogre::AxisAlignedBox* targetBox = target->getBoundingBox();

		if(sourceBox->intersects(*targetBox)) {
			collisions.push_back(new Collision(source, target));
		}
	}
}