#ifndef PARTICLE_EFFECT_DUST_H
#define PARTICLE_EFFECT_DUST_H

#include "ParticleEffect.h"

class ParticleEffectDust : public ParticleEffect {

private:
	Ogre::ParticleSystem* dust;
	Ogre::ParticleEmitter* dustEmitter;

public:
	ParticleEffectDust(Ogre::SceneNode* sceneNode, const std::string& ix);
	~ParticleEffectDust();

	void setRate(Ogre::Real rate);
	void update(Ogre::Real dt);
};

#endif