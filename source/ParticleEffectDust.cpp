#include "ParticleEffectDust.h"
#include "Game.h"

ParticleEffectDust::ParticleEffectDust(Ogre::SceneNode* particleNode, const std::string& ix) : 
  ParticleEffect() {
	sceneNode = particleNode;
	dust = Game::scene->createParticleSystem(60, "particles");
	dust->setSortingEnabled(true);
	dust->setMaterialName("dust");
	dust->setParameter("particle_width", "10");
	dust->setParameter("particle_height", "10");

	Ogre::ParticleAffector* dustMover = dust->addAffector("LinearForce");
	dustMover->setParameter("force_application", "add");
	dustMover->setParameter("force_vector", "0 -2.5 0");

	Ogre::ParticleAffector* dustScaler = dust->addAffector("Scaler");
	Ogre::ParticleAffector* dustRotator = dust->addAffector("Rotator");
	dustRotator->setParameter("rotation_speed_range_start", "0");
	dustRotator->setParameter("rotation_speed_range_end", "20");
	dustRotator->setParameter("rotation_range_start", "0");
	dustRotator->setParameter("rotation_range_end", "360");

	dustEmitter = dust->addEmitter("Box");
	dustEmitter->setParameter("width", "6");
	dustEmitter->setParameter("height", "0");
	dustEmitter->setParameter("depth", "2");
	
	dustEmitter->setAngle(Ogre::Radian(Ogre::Math::PI));
	dustEmitter->setEmissionRate(0);
	dustEmitter->setMinParticleVelocity(0);
	dustEmitter->setMaxParticleVelocity(1);
	dustEmitter->setTimeToLive(16);

	sceneNode->attachObject(dust);
	dust->setEmitting(true);
}

ParticleEffectDust::~ParticleEffectDust() {
	Game::scene->destroyParticleSystem(dust);
	end();
}

void ParticleEffectDust::setRate(Ogre::Real rate) {
	dustEmitter->setEmissionRate(rate*rate*0.05f);

	if(rate > 8) {
		dust->setParameter("particle_width", "12");
		dust->setParameter("particle_height", "12");
	} else if(rate > 2) {
		dust->setParameter("particle_width", "6");
		dust->setParameter("particle_height", "6");
	} else {
		dust->setParameter("particle_width", "3");
		dust->setParameter("particle_height", "3");
	}
}

void ParticleEffectDust::update(Ogre::Real dt) {}