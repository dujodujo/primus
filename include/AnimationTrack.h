#ifndef ANIMATION_TRACK_H
#define ANIMATION_TRACK_H

#include "Game.h"

class AnimationTrack {

private:
	bool active;
	Ogre::NodeAnimationTrack* track;

public:
	AnimationTrack();
	virtual ~AnimationTrack();

	bool activate();
};

#endif