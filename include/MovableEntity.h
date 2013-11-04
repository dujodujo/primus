#ifndef MOVABLE_ENTITY_H
#define MOVABLE_ENTITY_H

#include "Util.h"
#include "Entity.h"
#include "GameController.h"
#include "Game.h"

class Collision;

class MovableEntity : public Entity {

protected:
	Ogre::Vector3 velocity;
	Ogre::Vector3 move;
	Ogre::Real speed;
	Ogre::Real maxSpeed;
	Ogre::Radian theta;
	Ogre::Real amplitude;
	Ogre::Radian turnSpeed;
	Ogre::Real radius;
	
	CollisionMode collisionMode;
	std::vector<MovableEntity*> collisions;

public:
	MovableEntity(Ogre::Vector3 position, Ogre::Quaternion orientation,
		const std::string& name, Ogre::SceneNode* sceneNode, 
		Ogre::Real speed, Ogre::Radian turnSpeed);
	MovableEntity(Ogre::Vector3 position, Ogre::Quaternion orientation,
		Ogre::Real speed, Ogre::Radian turnSpeed);
	~MovableEntity();

	void setVelocity(Ogre::Vector3 veloctiy);
	Ogre::Vector3 getVelocity();
	
	Ogre::Real getSpeed();
	void setOrientation();

	void circleMovement(Ogre::Real dt);
	void simpleHarmonicMovementX(Ogre::Real dt);
	void simpleHarmonicMovementY(Ogre::Real dt);
	
	void simpleHarmonicMovementXZI(Ogre::Real dt);
	void simpleHarmonicMovementXZII(Ogre::Real dt);
	void simpleHarmonicMovementXZIII(Ogre::Real dt);
	void simpleHarmonicMovementXZIV(Ogre::Real dt);

	void rotationMotion(Ogre::Real dt, bool clockwise);

	Ogre::Quaternion calculateRotation(Ogre::Vector3 value);

	CollisionMode getCollisionType() { return collisionMode; }

	virtual void handleCollision(Collision* collision);
	void addCollisionEntity(MovableEntity* entity);
	bool collisionDetected(MovableEntity* entity);
	void collision(MovableEntity* entity);

	void moveEntity(Ogre::Vector3& amove);

	virtual void update(Ogre::Real dt);
	virtual void updateGameController();
};

#endif