#ifndef FLOOR_H
#define FLOOR_H

#include "Game.h"
#include "Plane.h"

/*
const Ogre::Real mpp = 8;
amespace floor {
	const int blockSize = 32;
	const Ogre::Real minBlockHeight = blockSize/2;

	enum BlockTypes { BlockPlain, BlockMountain, BlockRiver, BlockTypesCount };

	enum Types { Plain, Mountain, River };

	const std::string BlockPrefix[BlockTypes::BlockTypesCount] = { "plain", "mountain", "river" };
};
*/

class Floor : public Plane {

protected:
	Ogre::Plane plane;
	Ogre::SceneNode* terrainNode;
	unsigned int sizeWidth;
	unsigned int sizeHeight;

public:
	Floor(Ogre::Real width, Ogre::Real height, Ogre::String planeMesh, Ogre::String planeEntity, 
		Ogre::String materialName, Ogre::String materialTexture);
	~Floor();

	void createFloorModel();
	virtual void update() {};
};

#endif