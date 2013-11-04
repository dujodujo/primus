#include "AnimationTrack.h"

AnimationTrack::AnimationTrack() : 
  active(false) {
	Ogre::SceneNode* cameraNode = Game::getScene()->getRootSceneNode()->createChildSceneNode();
	cameraNode->attachObject(Game::camera->getCamera());

	Ogre::Animation* animation = Game::getScene()->createAnimation("CameraTrack", 30);
	
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	track = animation->createNodeTrack(0, cameraNode);

	track->createNodeKeyFrame(0)->setTranslate(Ogre::Vector3(0, 0, 0));
	track->createNodeKeyFrame(2.5)->setTranslate(Ogre::Vector3(20, 20, 0));
	track->createNodeKeyFrame(5)->setTranslate(Ogre::Vector3(40, 40, 0));
	track->createNodeKeyFrame(7.5)->setTranslate(Ogre::Vector3(60, 60, 0));
	track->createNodeKeyFrame(10)->setTranslate(Ogre::Vector3(80, 80, 0));
	track->createNodeKeyFrame(12.5)->setTranslate(Ogre::Vector3(100, 100, 0));
	track->createNodeKeyFrame(15)->setTranslate(Ogre::Vector3(120, 120, 0));
	track->createNodeKeyFrame(17.5)->setTranslate(Ogre::Vector3(140, 140, 0));
	track->createNodeKeyFrame(20)->setTranslate(Ogre::Vector3(160, 160, 0));
	track->createNodeKeyFrame(22.5)->setTranslate(Ogre::Vector3(180, 160, 0));
	track->createNodeKeyFrame(25)->setTranslate(Ogre::Vector3(180, 100, 0));
	track->createNodeKeyFrame(27.5)->setTranslate(Ogre::Vector3(180, 80, 0));
	track->createNodeKeyFrame(30)->setTranslate(Ogre::Vector3(200, 200, 0));

	Ogre::AnimationState* animationState = Game::getScene()->createAnimationState("CameraTrack");
	animationState->setEnabled(true);
}

AnimationTrack::~AnimationTrack() {}