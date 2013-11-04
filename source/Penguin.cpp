#include "Penguin.h"
#include "Util.h"
#include "Factory.h"

const int numModels = 4;

Penguin::Penguin(Ogre::Vector3 position, Ogre::Quaternion orientation,
  const std::string& name, Ogre::SceneNode* sceneNode,
  Ogre::Real speed, Ogre::Radian turnSpeed,
  Ogre::Entity& entityMesh) :
  MovableEntity(position, orientation, name, sceneNode, speed, turnSpeed),
  selected(false) {
	
	setBoundingSphere();

	std::string selectid = Factory::getID() + "." + name + "/selected";
	Ogre::Entity* pointerMesh = Game::getScene()->createEntity(selectid, "target.mesh");
	pointerMesh->setMaterialName("target");

	node = sceneNode->createChildSceneNode();
    node->attachObject(pointerMesh);
	node->setVisible(selected);
	node->setPosition(position);
}

Penguin::~Penguin() {}


void Penguin::select() {
	Ogre::Vector3 pointerPosition = Game::gameController->getPointerPosition();
	if(boundingBox->contains(pointerPosition)) {
		selected = true;
		node->setVisible(selected);
	} else {
		selected = false;
		node->setVisible(selected);
	}
}

void Penguin::update(Ogre::Real dt) {
	MovableEntity::update(dt);
}