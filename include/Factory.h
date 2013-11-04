#ifndef FACTORY_H
#define FACTORY_H

#include "Util.h"

class Factory {

protected:
	static unsigned int id;

public:
	void destroyModel(Ogre::SceneNode* sceneNode);
	static std::string getID();
};

#endif