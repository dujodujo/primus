#include "PenguinFactory.h"
#include "Penguin.h"
#include "Game.h"


PenguinFactory::PenguinFactory() {}

PenguinFactory::~PenguinFactory() {}

Penguin* PenguinFactory::createPenguin(Ogre::Vector3 position, 
  const std::string& name, Ogre::Quaternion orientation,
  Ogre::Real speed, Ogre::Radian turnSpeed) {
	std::string id = Factory::getID() + "." + name;

	Ogre::Entity* entityMesh = Game::getScene()->createEntity(id, name + ".mesh");
	Ogre::SceneNode* sceneNode = Game::getScene()->getRootSceneNode()->createChildSceneNode();
	sceneNode->attachObject(entityMesh);
	sceneNode->showBoundingBox(true);
	sceneNode->setPosition(position);
	sceneNode->setOrientation(orientation);
	//sceneNode->setScale(0.4f, 0.4f, 0.4f);

	penguins.push_back(new Penguin(position, orientation, id, sceneNode, 
		speed, turnSpeed, *entityMesh));
	return penguins.back();
}

std::vector<Penguin*> PenguinFactory::getPenguins() {
	return this->penguins;
}