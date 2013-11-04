#include "EntityFactory.h"

EntityFactory::EntityFactory() {}

EntityFactory::~EntityFactory() {
	for(std::vector<Entity*>::iterator iter = entities.begin(); iter != entities.end(); ++iter) {}
	entities.clear();
}

void EntityFactory::update(Ogre::Real dt) {}
