#ifndef PARTICLE_H
#define PARTICLE_H

#include "Util.h"

class ParticleEffect {

protected:
	Ogre::SceneNode* sceneNode;
	Ogre::Real duration;
	Ogre::Real durationLimit;

	bool running;

public:
	ParticleEffect();
	virtual ~ParticleEffect();

	void end();
	bool isRunning();

	virtual void update(Ogre::Real dt) = 0;
};

#endif