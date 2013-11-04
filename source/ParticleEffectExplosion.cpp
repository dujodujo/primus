#include "ParticleEffectExplosion.h"


ParticleEffectExplosion::ParticleEffectExplosion(Ogre::SceneNode* particleNode, 
  Ogre::Real size, Ogre::Real time) :
  ParticleEffect() {
	this->sceneNode = particleNode;
	this->duration = 0;
	this->durationLimit = time + 0.4f;
	this->emissionRate = 1;

	this->explosion = Game::getScene()->createParticleSystem(10, "particles");
	this->explosion->setSortingEnabled(true);
	this->explosion->setMaterialName("explosion");
	this->explosion->setParameter("particle_width", "6");
	this->explosion->setParameter("particle_height", "1");

	Ogre::ParticleAffector* explosionScaling = explosion->addAffector("Scaler");

	explosionScaling->setParameter("rate", toString(size / (time * 1.25)));

    //rotate
    Ogre::ParticleAffector* explosionRotating = explosion->addAffector("Rotator");
    explosionRotating->setParameter("rotation_speed_range_start", "-180");
    explosionRotating->setParameter("rotation_speed_range_end", "180");
    explosionRotating->setParameter("rotation_range_start", "0");
    explosionRotating->setParameter("rotation_range_end", "360");

    //emit from a sphere
    Ogre::ParticleEmitter* explosionEmitter = explosion->addEmitter("Ellipsoid");
    explosionEmitter->setParameter("width", "4");
    explosionEmitter->setParameter("height", "4");
    explosionEmitter->setParameter("depth", "4");
	explosionEmitter->setAngle(Ogre::Radian(Ogre::Math::PI));
    explosionEmitter->setEmissionRate(emissionRate * 2);
    explosionEmitter->setMinParticleVelocity(1);
    explosionEmitter->setMaxParticleVelocity(4);
    explosionEmitter->setTimeToLive(time);
    explosionEmitter->setDuration(duration);

    sceneNode->attachObject(explosion);
    explosion->setEmitting(true);
}

ParticleEffectExplosion::~ParticleEffectExplosion() {
	Game::getScene()->destroyParticleSystem(explosion);
	end();
}

void ParticleEffectExplosion::update(Ogre::Real dt) {
	duration += dt;
	if(durationLimit > duration) {
		running = false;
	}
}