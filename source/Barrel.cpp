#include "Barrel.h"
#include "Util.h"
#include "Factory.h"

const int numModels = 4;

Barrel::Barrel(Ogre::Vector3 position, Ogre::Quaternion orientation,
  const std::string& name, Ogre::SceneNode* sceneNode,
  Ogre::Real speed, Ogre::Radian turnSpeed,
  Ogre::Entity& entityMesh) :
  MovableEntity(position, orientation, name, sceneNode, speed, turnSpeed),
  selected(false),
  node(NULL) {

	animation = NULL;
	loadAnimation();

	for(unsigned int i = 0; i < numModels; ++i) {
		modelNodes.push_back(sceneNode);
		animationState = entityMesh.getAnimationState("Sneak");
		animationState->setEnabled(true);
		animationState->setLoop(true);
		animationSpeeds.push_back(Ogre::Real(1.5f));
		animationStates.push_back(animationState);
	}
	
	std::string selectid = Factory::getID() + "." + name + "/selected";
	Ogre::Entity* pointerMesh = Game::getScene()->createEntity(selectid, "target.mesh");
	pointerMesh->setMaterialName("target");

	node = sceneNode->createChildSceneNode();
    node->attachObject(pointerMesh);
	node->setVisible(selected);
	node->setPosition(position);
}

Barrel::~Barrel() {}

void Barrel::loadAnimation() {
	Ogre::SkeletonPtr skeleton = Ogre::SkeletonManager::getSingleton().load("jaiqua.skeleton", 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	animation = skeleton->getAnimation("Sneak");
}

void Barrel::select() {
	Ogre::Vector3 pointerPosition = Game::gameController->getPointerPosition();
	if(boundingBox->contains(pointerPosition)) {
		selected = true;
		node->setVisible(selected);
	} else {
		selected = false;
		node->setVisible(selected);
	}
}

void Barrel::update(Ogre::Real dt) {
	MovableEntity::update(dt);
	for(unsigned int i = 0; i < numModels; ++i) {
		animationStates[i]->addTime(animationSpeeds[i] * dt);
		if(animationStates[i]->getTimePosition() >= 8) {
			animationStates[i]->setTimePosition(0);
		}
	}
}