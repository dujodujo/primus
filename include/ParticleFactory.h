#ifndef PARTICLE_FACTORY_H
#define PARTICLE_FACTORY_H

#include "Factory.h"

class ParticleEffect;
class ParticleEffectExplosion;

class ParticleFactory : public Factory {

protected:
    std::vector<ParticleEffect*> effects;

public:
    ParticleFactory();
    virtual ~ParticleFactory();

    ParticleEffect* createExplosion(Ogre::SceneNode* sceneNode, Ogre::Real size, Ogre::Real time);
    ParticleEffect* createExplosion(Ogre::Vector3 position, Ogre::Real size, Ogre::Real time);
	ParticleEffect* createDust(Ogre::SceneNode* sceneNode, const std::string& ix);

	void update(Ogre::Real a_dt);

	std::vector<ParticleEffect*> getParticleEffects();
};

#endif
