#ifndef MOVABLE_ENTITY_FACTORY_H
#define MOVABLE_ENTITY_FACTORY_H

#include "Factory.h"

class MovableEntity;
class Game;

class MovableEntityFactory : public Factory {

protected:
	std::vector<MovableEntity*> entities;

public:
	MovableEntityFactory();
	~MovableEntityFactory();

	MovableEntity* createMovableEntity(Ogre::Vector3 position, 
		const std::string& name, Ogre::Quaternion orientation,
		Ogre::Real speed, Ogre::Radian turnSpeed);

	std::vector<MovableEntity*> getMovableEntities();
};

#endif