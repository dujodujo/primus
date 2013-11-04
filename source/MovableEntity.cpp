#include "MovableEntity.h"
#include "CollisionHandler.h"
#include "Collision.h"

MovableEntity::MovableEntity(Ogre::Vector3 position, Ogre::Quaternion orientation,
  const std::string& name, Ogre::SceneNode* sceneNode,
  Ogre::Real speed, Ogre::Radian turnSpeed) :
  Entity(position, orientation, name, sceneNode),
  velocity(Ogre::Vector3::ZERO),
  move(Ogre::Vector3::ZERO),
  speed(speed),
  maxSpeed(speed),
  turnSpeed(turnSpeed),
  theta(12.f), 
  amplitude(0.1f),
  collisionMode(CollisionMode::BLOCK) {
	orientation = sceneNode->getOrientation();
	this->radius = 0.005f;

	if(active) {
		Game::collisionHandler->addEntities(this);
	} else {
		Game::collisionHandler->removeEntities(this);
	}
}

MovableEntity::MovableEntity(Ogre::Vector3 position, Ogre::Quaternion orientation,
  Ogre::Real speed, Ogre::Radian turnSpeed) :
  Entity(position, orientation),
  velocity(Ogre::Vector3::ZERO),
  move(Ogre::Vector3::ZERO),
  speed(speed),
  maxSpeed(speed),
  turnSpeed(turnSpeed),
  theta(12.f), 
  amplitude(0.1f),
  collisionMode(CollisionMode::BLOCK) {
	this->radius = 0.005f;

	if(active) {
		Game::collisionHandler->addEntities(this);
	} else {
		Game::collisionHandler->removeEntities(this);
	}
}

MovableEntity::~MovableEntity() {}

void MovableEntity::setVelocity(Ogre::Vector3 veloctiy) {
	this->velocity = velocity;
}

Ogre::Vector3 MovableEntity::getVelocity() {
	return this->velocity;
}

Ogre::Real MovableEntity::getSpeed() {
	return speed;
}

void MovableEntity::setOrientation() {
	orientation = sceneNode->getOrientation();
}

void MovableEntity::rotationMotion(Ogre::Real dt, bool clockwise) {
	if(clockwise) {
		orientation = Ogre::Quaternion((turnSpeed * dt * 100), Ogre::Vector3::UNIT_Y) * orientation;
		direction = orientation * Ogre::Vector3::UNIT_Z;
	} else {
		orientation = Ogre::Quaternion((-1 * turnSpeed * dt * 100), Ogre::Vector3::UNIT_Y) * orientation;
		direction = orientation * Ogre::Vector3::UNIT_Z;
	}
}

void MovableEntity::circleMovement(Ogre::Real dt) {
	position += radius * Ogre::Vector3(Ogre::Math::Cos(theta), 0, Ogre::Math::Sin(theta));
	velocity += radius * Ogre::Vector3(-Ogre::Math::Sin(theta), 0, Ogre::Math::Cos(theta));
	direction = velocity.normalise();
}

void MovableEntity::simpleHarmonicMovementX(Ogre::Real dt) {
	theta += this->turnSpeed;
	position.x += amplitude * Ogre::Math::Cos(theta);
	velocity.x = amplitude * Ogre::Math::Sin(theta) * direction.x;
	direction = velocity.normalise();
}

void MovableEntity::simpleHarmonicMovementY(Ogre::Real dt) {
	theta += this->turnSpeed;
	position.z += amplitude * Ogre::Math::Cos(theta);
	velocity.z = amplitude * Ogre::Math::Sin(theta) * direction.z;
	direction = velocity.normalise();
}

void MovableEntity::simpleHarmonicMovementXZI(Ogre::Real dt) {
	theta += this->turnSpeed;
	position += amplitude * (Ogre::Vector3(Ogre::Math::Cos(theta), 0, -Ogre::Math::Cos(theta)));
	velocity = amplitude * (Ogre::Vector3(-Ogre::Math::Sin(theta), 0, Ogre::Math::Sin(theta))) * direction;
	direction = velocity.normalise();
}

void MovableEntity::simpleHarmonicMovementXZII(Ogre::Real dt) {
	theta += this->turnSpeed;
	position += amplitude * (Ogre::Vector3(-Ogre::Math::Cos(theta), 0, -Ogre::Math::Cos(theta)));
	velocity = amplitude * (Ogre::Vector3(Ogre::Math::Sin(theta), 0, Ogre::Math::Sin(theta))) * direction;
	direction = velocity.normalise();
}

void MovableEntity::simpleHarmonicMovementXZIII(Ogre::Real dt) {
	theta += this->turnSpeed;
	position += amplitude * (Ogre::Vector3(-Ogre::Math::Cos(theta), 0, Ogre::Math::Cos(theta)));
	velocity = amplitude * (Ogre::Vector3(Ogre::Math::Sin(theta), 0, -Ogre::Math::Sin(theta))) * direction;
	direction = velocity.normalise();
}

void MovableEntity::simpleHarmonicMovementXZIV(Ogre::Real dt) {
	theta += this->turnSpeed;
	position += amplitude * (Ogre::Vector3(Ogre::Math::Cos(theta), 0, Ogre::Math::Cos(theta)));
	velocity = amplitude * (-Ogre::Vector3(Ogre::Math::Sin(theta), 0, -Ogre::Math::Sin(theta))) * direction;
	direction = velocity.normalise();
}

void MovableEntity::handleCollision(Collision* collision) {}

void MovableEntity::addCollisionEntity(MovableEntity* entity) {
	collisions.push_back(entity);
}

bool MovableEntity::collisionDetected(MovableEntity* entity) {
	std::vector<MovableEntity*>::iterator it = collisions.begin(); 
	if(std::find(collisions.begin(), collisions.end(), entity) != collisions.end()) {
		return true;
	}
	return false;
}

void MovableEntity::moveEntity(Ogre::Vector3& amove) {
	this->position -= amove;
}

void MovableEntity::update(Ogre::Real dt) {
	collisions.clear();
	
	Entity::update(dt);
	sphere.update(position);
	
	sceneNode->setPosition(position);
	sceneNode->setOrientation(orientation);
}

void MovableEntity::updateGameController() {}