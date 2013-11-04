#ifndef BARREL_H
#define BARREL_H

#include "MovableEntity.h"

class Barrel : public MovableEntity {

private:
	Ogre::AnimationState* animationState;
	Ogre::Animation* animation;

	Ogre::Vector3 sneakStartPosition;
	Ogre::Vector3 sneakEndPosition;

	std::vector<Ogre::SceneNode* > modelNodes;
	std::vector<Ogre::AnimationState* > animationStates;
	std::vector<Ogre::Real> animationSpeeds;
		
	Ogre::SceneNode* node;

	bool selected;

public:
	Barrel(Ogre::Vector3 position, Ogre::Quaternion orientation,
		const std::string& name, Ogre::SceneNode* sceneNode,
		Ogre::Real speed, Ogre::Radian turnSpeed,
		Ogre::Entity& entityMesh);
	~Barrel();

	void loadAnimation();
	void select();

	void update(Ogre::Real dt);
};

#endif