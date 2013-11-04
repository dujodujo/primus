#include "FacialAnimation.h"

FacialAnimation::FacialAnimation() {

	Ogre::MeshPtr facialMesh = Ogre::MeshManager::getSingleton().load("facial.mesh", 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Ogre::Animation* animation = facialMesh->createAnimation("Manual", 0);
	animation->createVertexTrack(4, Ogre::VAT_POSE)->createVertexPoseKeyFrame(0);

	for(unsigned int i = 0; i < 15; i++) {
		manualKeyFrame->addPoseReference(i, 0);
	}

	Ogre::Entity* head = Game::getScene()->createEntity("Head", "facial.mesh");
	Game::getScene()->getRootSceneNode()->createChildSceneNode()->attachObject(head);

	speakAnimationState = head->getAnimationState("Speak");
	manualAnimationState = head->getAnimationState("Manual");

	playAnimation = true;
}

FacialAnimation::~FacialAnimation() {}