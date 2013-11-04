#include "ParticleFactory.h"
#include "ParticleEffectExplosion.h"
#include "ParticleEffectDust.h"
#include "Game.h"

ParticleFactory::ParticleFactory() {}

ParticleFactory::~ParticleFactory() {
	for(unsigned int i = 0;  i < effects.size(); i++) {
		delete effects[i];
	}
	effects.clear();
}

void ParticleFactory::update(Ogre::Real dt) {
	/*
	std::vector<ParticleEffect*>::iterator iter;
	for(iter; iter != effects.end(); iter++) {
		(*iter)->update(dt);
		if(!(*iter)->isRunning()) {
			delete *iter;
			this->effects.erase(iter);
		}
	}
	*/
}

ParticleEffect* ParticleFactory::createExplosion(Ogre::SceneNode* sceneNode, Ogre::Real size, Ogre::Real time) {
	Ogre::SceneNode* particleNode = Game::getScene()->getRootSceneNode()->createChildSceneNode();
	particleNode->setPosition(sceneNode->getPosition());
	effects.push_back(new ParticleEffectExplosion(particleNode, size, time));
	return effects.back();
}

ParticleEffect* ParticleFactory::createExplosion(Ogre::Vector3 position, Ogre::Real size, Ogre::Real time) {
	Ogre::SceneNode* particleNode = Game::getScene()->getRootSceneNode()->createChildSceneNode();
	particleNode->setPosition(position);
	effects.push_back(new ParticleEffectExplosion(particleNode, size, time));
	return effects.back();
}

ParticleEffect* ParticleFactory::createDust(Ogre::SceneNode* sceneNode, const std::string& ix) {
	Ogre::SceneNode* particleNode = sceneNode->createChildSceneNode();
	effects.push_back(new ParticleEffectDust(particleNode, ix));
	return effects.back();
}

std::vector<ParticleEffect*> ParticleFactory::getParticleEffects() {
	return effects;
}
