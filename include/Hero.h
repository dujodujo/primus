#ifndef HERO_H
#define HERO_H

#include "MovableEntity.h"
#include "ParticleEffectDust.h"
#include "ParticleFactory.h"
#include "Animations.h"
#include "AnimationTrack.h"

#include <math.h>

class Hero : public MovableEntity {

private:
	/*
	ParticleEffectDust* dust;
	Ogre::AnimationState* animationState;
	Ogre::Animation* animation;

	int numModels;
	std::vector<Ogre::SceneNode* > modelNodes;
	std::vector<Ogre::AnimationState* > animationStates;
	std::vector<Ogre::Real> animationSpeeds;
	*/
	AnimationTrack* animationTrack;

public:
	Hero(Ogre::Vector3 position, Ogre::Quaternion orientation,
		const std::string& name, Ogre::Real speed, Ogre::Radian turnSpeed);
	~Hero();

	void loadAnimation();
	void startAnimation();

	void moveHero(Ogre::Real dt);
	void handleCollision(Collision* collision);
	
	void update(Ogre::Real dt);
};

#endif