#ifndef WALL_FACTORY_H
#define WALL_FACTORY_H

#include "EntityFactory.h"
#include "Wall.h"

class Game;

class WallFactory : public EntityFactory {

public:
	enum Direction {YY, XX};

protected:
	std::vector<Wall*> walls;

public:
	WallFactory();
	~WallFactory();

	Wall* createWall(Ogre::Real width, Ogre::Real height, 
		Ogre::Vector3& position, WallFactory::Direction direction);
};

#endif