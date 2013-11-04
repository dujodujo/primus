#include "Wall.h"
#include "Factory.h"

Wall::Wall(Ogre::Real width, Ogre::Real height, Ogre::Vector3& position, Ogre::Vector3& dir) :
  Plane(width, height),
  plane(Ogre::Vector3::UNIT_Z, 0) {

	Ogre::MeshManager::getSingleton().createPlane("wall", 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane, width, height, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Y);
	
	Ogre::Entity* wallMesh = Game::getScene()->createEntity(Factory::getID() + "/wallEntity", "wall");
	Ogre::SceneNode* sceneNode = Game::getScene()->getRootSceneNode()->createChildSceneNode();
	sceneNode->attachObject(wallMesh);
	sceneNode->setPosition(position);
	sceneNode->setDirection(dir);
}

Wall::~Wall() {}