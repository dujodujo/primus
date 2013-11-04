#include "WallFactory.h"

WallFactory::WallFactory() {}

WallFactory::~WallFactory() {}

Wall* WallFactory::createWall(Ogre::Real width, Ogre::Real height, 
  Ogre::Vector3& position, WallFactory::Direction direction) {
	std::string id = Factory::getID();

	Ogre::Vector3 dir = Ogre::Vector3::ZERO;
	
	if(direction == WallFactory::Direction::XX) {
		dir = Ogre::Vector3::UNIT_X;
	} else if(direction == WallFactory::Direction::YY) {
		dir = Ogre::Vector3::UNIT_Y;
	}

	walls.push_back(new Wall(width, height, position, dir));
	return walls.back();
}