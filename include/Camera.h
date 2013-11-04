#ifndef CAMERA_H
#define CAMERA_H

#include "Util.h"
#include <OgreMath.h>

class Camera {

public:
	enum CameraStyle {FreeLook, Orbit, Manual};

	Ogre::Camera* camera;
	Ogre::Vector3 position;
	CameraStyle style;
	Ogre::SceneNode* target;
	bool orbit;
	bool zoom;
	Ogre::Real speed;
	Ogre::Vector3 velocity;

	bool forward;
	bool back;
	bool left;
	bool right;
	bool up;
	bool down;

	//Ogre::Vector3 cameraOffset;
	//Ogre::Vector3 lookAt;
	//Ogre::Vector3 lookAtOffset;

	Ogre::Real cameraDistance;
	Ogre::Radian cameraFov;

	//Ogre::SceneNode* cameraNode;
	//Ogre::SceneNode* cameraYawNode;
	//Ogre::SceneNode* cameraPitchNode;
	//Ogre::SceneNode* cameraRollNode;

public:
	Camera();
	~Camera();

	void resize(int width, int height);

	Ogre::Camera* getCamera();
	Ogre::Quaternion getQuaternion();

	void setTarget(Ogre::SceneNode* target);
	void setYawPitchDistance(Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Real distance);
	void stop();
	void setStyle(CameraStyle cameraStyle);

	void update(Ogre::Real dt);
};

#endif