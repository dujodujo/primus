#include "MovableEntityFactory.h"
#include "MovableEntity.h"
#include "Game.h"


MovableEntityFactory::MovableEntityFactory() {
}

MovableEntityFactory::~MovableEntityFactory() {}

MovableEntity* MovableEntityFactory::createMovableEntity(Ogre::Vector3 position, 
  const std::string& name, Ogre::Quaternion orientation,
  Ogre::Real speed, Ogre::Radian turnSpeed) {
	std::string id = Factory::getID() + "." + name;

	Ogre::Entity* entityMesh = Game::getScene()->createEntity(id, "sphere.mesh");
	Ogre::SceneNode* sceneNode = Game::getScene()->getRootSceneNode()->createChildSceneNode();
	sceneNode->attachObject(entityMesh);

	sceneNode->setPosition(position);
	sceneNode->setOrientation(orientation);

	entities.push_back(new MovableEntity(position, orientation, id, sceneNode, speed, turnSpeed));
	
	return entities.back();
}

std::vector<MovableEntity*> MovableEntityFactory::getMovableEntities() {
	return entities;
}