#ifndef PARTICLE_EFFECT_EXPLOSION_H
#define PARTICLE_EFFECT_EXPLOSION_H

#include "ParticleEffect.h"
#include "Game.h"

class ParticleEffectExplosion : public ParticleEffect {

private:
    Ogre::ParticleSystem* explosion;
	Ogre::Real emissionRate;

public:
    ParticleEffectExplosion(Ogre::SceneNode* particleNode, Ogre::Real size, Ogre::Real time);
    ~ParticleEffectExplosion();

    void update(Ogre::Real dt);
};

#endif