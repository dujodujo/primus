#ifndef ROBOT_H
#define ROBOT_H

#include "MovableEntity.h"
#include "Factory.h"
#include "Game.h"

#include <string>
#include <queue>
#include <deque>

class Robot : public MovableEntity {

private:
	std::deque<Ogre::Vector3> walkingList;
	Ogre::AnimationState* animationState;
	
	Ogre::Entity* robotMesh;
	Ogre::Vector3 destination;

public:
	Robot(Ogre::Vector3 position, Ogre::Quaternion orientation, const std::string& name);
	~Robot();

	void moveRobot(Ogre::Real dt);
	bool nextLocation();
	void update(Ogre::Real dt);
};

#endif