#ifndef FACIAL_ANIMATION_H
#define FACIAL_ANIMATIOIN_H

#include "Game.h"

class FacialAnimation {

private:
	Ogre::MeshPtr facialMesh;
	Ogre::AnimationState* speakAnimationState;
	Ogre::AnimationState* manualAnimationState;
	Ogre::VertexPoseKeyFrame* manualKeyFrame;

	bool playAnimation;

public:
	FacialAnimation();
	~FacialAnimation();

};

#endif