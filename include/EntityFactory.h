#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include "Factory.h"
#include "Hero.h"

class EntityFactory : public Factory {

private:
	std::vector<Entity*> entities;

public:
	EntityFactory();
	~EntityFactory();

	void update(Ogre::Real dt);
};

#endif