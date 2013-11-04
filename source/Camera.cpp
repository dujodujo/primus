#include "Camera.h"
#include "Game.h"

Camera::Camera() :
  position(0.f, 0.f, 0.f),
  cameraFov(0.15f),
  target(0),
  orbit(false), 
  zoom(false), 
  speed(100),
  velocity(Ogre::Vector3::ZERO), 
  style(CameraStyle::FreeLook) {

	setStyle(style);

	forward = false;
	back = false;
	left = false;
	right = false;
	up = false;
	down = false;

	camera = Game::getScene()->createCamera("camera");
    camera->setFOVy(cameraFov);

	//cameraNode = Game::getScene()->getRootSceneNode()->createChildSceneNode();
	//cameraNode->setPosition(position);
	//cameraYawNode = cameraNode->createChildSceneNode();
	//cameraPitchNode = cameraYawNode->createChildSceneNode();
	//cameraRollNode = cameraPitchNode->createChildSceneNode();
	//cameraRollNode->attachObject(camera);

	resize(Game::getRender()->getWidth(), Game::getRender()->getHeight());
}

Camera::~Camera() {
	delete camera;
}

void Camera::resize(int width, int height) {
	/*
    Ogre::Real aspectRatio = Ogre::Real(width) / Ogre::Real(height);
	Ogre::Real inverseAspectRatio = 1 / aspectRatio;

    camera->setAspectRatio(aspectRatio);

    //angle between camera ray and ground normal
    Ogre::Real cameraAngle;

    if (aspectRatio > 1) { 
        cameraAngle = Ogre::Real(acos(inverseAspectRatio));

        if (cameraAngle < 0.5) {
            cameraAngle = 0.5;
        } else if (cameraAngle > 1.2) {
            cameraAngle = 1.2;
        }

    } else {
        cameraAngle = 0.5;
    }

    cameraOffset = Ogre::Vector3(0, std::cos(cameraAngle) * cameraDistance * inverseAspectRatio,
		std::sin(cameraAngle) * cameraDistance * inverseAspectRatio);

    lookAtOffset = Ogre::Vector3(0, -5 * (cameraAngle / (0.5 * Ogre::Math::PI)), 0);
    position = lookAt + cameraOffset;
	*/
}

Ogre::Camera* Camera::getCamera() {
	return camera;
}

Ogre::Quaternion Camera::getQuaternion() {
	return camera->getOrientation();
}

void Camera::setTarget(Ogre::SceneNode* t) {
	if(target != t) {
		target = t;
		if(target) {
			setYawPitchDistance(Ogre::Degree(0), Ogre::Degree(15), 150);
			camera->setAutoTracking(true, target);
		} else {
			camera->setAutoTracking(false);
		}
	}
}

void Camera::setStyle(CameraStyle cameraStyle) {
	if(style != CameraStyle::Orbit && cameraStyle == CameraStyle::Orbit) {
		setTarget(Game::getScene()->getRootSceneNode());
		camera->setFixedYawAxis(true);
		stop();
		setYawPitchDistance(Ogre::Degree(0), Ogre::Degree(15), 150);
	} else if(style != CameraStyle::FreeLook && cameraStyle == CameraStyle::FreeLook) {
		camera->setAutoTracking(false);
		camera->setFixedYawAxis(true);
	} else if(style != CameraStyle::Manual && cameraStyle == CameraStyle::Manual) {
		camera->setAutoTracking(false);
		stop();
	}
	style = cameraStyle;
}

void Camera::setYawPitchDistance(Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Real distance) {
	camera->setPosition(target->_getDerivedPosition());
	camera->setOrientation(target->_getDerivedOrientation());
	camera->yaw(yaw);
	camera->pitch(-pitch);
	camera->moveRelative(Ogre::Vector3(0, 0, distance));
}

void Camera::stop() {
	if(style == CameraStyle::FreeLook) {
		forward = false;
		back = false;
		left = false;
		right = false;
		up = false;
		down = false;
		velocity = Ogre::Vector3::ZERO;
	}
}

void Camera::update(Ogre::Real dt) {

	if(style == CameraStyle::FreeLook) {
		Ogre::Vector3 accel = Ogre::Vector3::ZERO;
		if(forward) 
			accel += camera->getDirection();
		if(back) 
			accel -= camera->getDirection();
		if(right) 
			accel += camera->getRight();
		if(left) 
			accel -= camera->getRight();
		if(up) 
			accel += camera->getUp();
		if(down) 
			accel -= camera->getUp();

		if(accel.squaredLength() != 0) {
			accel.normalise();
			velocity += accel * speed * dt;
		} else {
			velocity -= velocity * dt;
		}

		if(velocity.squaredLength() > speed * speed) {
			velocity.normalise();
			velocity *= speed;
		} else if(velocity.squaredLength() < 0.0001f) {
			velocity = Ogre::Vector3::ZERO;
		}

		if(velocity != Ogre::Vector3::ZERO) {
			camera->move(velocity * dt);
		}
	}
}