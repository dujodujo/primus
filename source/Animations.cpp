#include "Animations.h"

Animations::Animations(Ogre::SceneNode* sceneNode) : 
  currentAnimation(AnimationStates::STAND), 
  targetAnimation(AnimationStates::STAND),
  stopSpeed(0.0001f) {

	getAnimation(sceneNode);

	//start animation
	unsigned int size = animations[currentAnimation].size();
	for(unsigned int i = 0; i < size; ++i) {
		animations[currentAnimation][i]->setEnabled(true);
	}
}

Animations::~Animations() {}

void Animations::walk(Ogre::Real s) {
	Ogre::Real speed = Ogre::Math::Abs(s);
	if(speed < stopSpeed) {
		targetAnimation = AnimationStates::STAND;
	} else {
		targetAnimation = AnimationStates::WALK;
	}
}
	
void Animations::getAnimation(Ogre::SceneNode* sceneNode) {
	for(unsigned int i = 0; i < numAnimations; ++i) {
		Ogre::SceneNode::ObjectIterator iter = sceneNode->getAttachedObjectIterator();
		while(iter.hasMoreElements()) {
			Ogre::Entity* animationEntity = static_cast<Ogre::Entity*>(iter.getNext());
		}
		Ogre::SceneNode::ChildNodeIterator iterator = sceneNode->getChildIterator();
		while(iterator.hasMoreElements()) {
			getAnimation(static_cast<Ogre::SceneNode* >(iterator.getNext()));
		}
	}
}

bool Animations::changeAnimation() {
	if(currentAnimation != targetAnimation) {
		Ogre::Real animationTime = animations[currentAnimation][0]->getTimePosition();

		currentAnimation = targetAnimation;
		unsigned int size = animations[currentAnimation].size();
		for(unsigned int i = 0; i < size; ++i) {
			animations[currentAnimation][i]->setEnabled(true);
			animations[currentAnimation][i]->setWeight(true);
			animations[currentAnimation][i]->setTimePosition(animationTime);
		}
	}
	return true;
}

void Animations::update(Ogre::Real dt) {
	changeAnimation();
}