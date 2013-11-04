#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "Game.h"
#include <vector>

const unsigned int numAnimations = 2;
const std::string animationsName[numAnimations] = {"stand", "walk"};

class Animations {

private:
	std::vector<Ogre::AnimationState* > animations[numAnimations];
	enum AnimationStates {STAND, WALK};

	AnimationStates currentAnimation;
	AnimationStates targetAnimation;

	Ogre::Real stopSpeed;

public:
	Animations(Ogre::SceneNode* sceneNode);
	~Animations();

	void walk(Ogre::Real speed);
	
	void getAnimation(Ogre::SceneNode* sceneNode);
	bool changeAnimation();

	void update(Ogre::Real dt);
};

#endif