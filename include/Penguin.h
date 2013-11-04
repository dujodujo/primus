#ifndef PENGUIN_H
#define PENGUIN_H

#include "MovableEntity.h"
#include "AnimationTrack.h"

class AnimationTrack;

class Penguin : public MovableEntity {

private:
	bool selected;
	Ogre::SceneNode* node;

public:
	Penguin(Ogre::Vector3 position, Ogre::Quaternion orientation,
		const std::string& name, Ogre::SceneNode* sceneNode,
		Ogre::Real speed, Ogre::Radian turnSpeed,
		Ogre::Entity& entityMesh);
	~Penguin();

	void select();

	void update(Ogre::Real dt);
};

#endif