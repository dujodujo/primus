#include "ParticleEffect.h"
#include "Game.h"

ParticleEffect::ParticleEffect() :
  duration(0),
  durationLimit(0),
  running(true),
  sceneNode(NULL) {
}

ParticleEffect::~ParticleEffect() {}

void ParticleEffect::end() {
	Game::getScene()->destroySceneNode(sceneNode);
}

bool ParticleEffect::isRunning() {
	return running;
}