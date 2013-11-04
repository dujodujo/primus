#include "Factory.h"
#include "Game.h"

unsigned int Factory::id = 0;

void Factory::destroyModel(Ogre::SceneNode* sceneNode) {
	Ogre::SceneNode::ObjectIterator it = sceneNode->getAttachedObjectIterator();
    while (it.hasMoreElements()) {
        Ogre::MovableObject* movableEntity = static_cast<Ogre::MovableObject*>(it.getNext());
        sceneNode->getCreator()->destroyMovableObject(movableEntity);
    }

    //destroy children if any
    Ogre::SceneNode::ChildNodeIterator it2 = sceneNode->getChildIterator();
    while (it2.hasMoreElements()) {
        Ogre::SceneNode* childNode = static_cast<Ogre::SceneNode*>(it2.getNext());
        destroyModel(childNode);
    }

    //at last remove the scene node
    Game::scene->destroySceneNode(sceneNode);
}

std::string Factory::getID() {
	std::string stringid;
	std::stringstream stream;
	stream << std::setfill('0') << std::setw(4) << ++id;
	stream >> stringid;
	return stringid;
}