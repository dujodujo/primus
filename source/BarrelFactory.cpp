#include "BarrelFactory.h"
#include "Barrel.h"
#include "Game.h"


BarrelFactory::BarrelFactory() {}

BarrelFactory::~BarrelFactory() {}

Barrel* BarrelFactory::createBarrel(Ogre::Vector3 position, 
  const std::string& name, Ogre::Quaternion orientation,
  Ogre::Real speed, Ogre::Radian turnSpeed) {
	std::string id = Factory::getID() + "." + name;

	Ogre::Entity* entityMesh = Game::getScene()->createEntity(id, name+".mesh");
	Ogre::SceneNode* sceneNode = Game::getScene()->getRootSceneNode()->createChildSceneNode();
	sceneNode->attachObject(entityMesh);
	sceneNode->showBoundingBox(true);
	sceneNode->setPosition(position);
	sceneNode->setOrientation(orientation);
	sceneNode->setScale(0.4f, 0.4f, 0.4f);

	barrels.push_back(new Barrel(position, orientation, id, sceneNode, speed, turnSpeed, *entityMesh));
	return barrels.back();
}

std::vector<Barrel*> BarrelFactory::getBarrels() {
	return this->barrels;
}