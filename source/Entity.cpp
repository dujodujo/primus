#include "Entity.h"

Entity::Entity(Ogre::Vector3 position, Ogre::Quaternion orientation,
  const std::string& name, Ogre::SceneNode* sceneNode) :
  position(position),
  orientation(orientation),
  name(name),
  sceneNode(sceneNode),
  weight(1),
  active(true) {
	direction = orientation * Ogre::Vector3::UNIT_Z;
	boundingBox = &sceneNode->getAttachedObject(name)->getBoundingBox();
}

Entity::Entity(Ogre::Vector3 position, Ogre::Quaternion orientation) : 
  position(position),
  orientation(orientation),
  name(""),
  sceneNode(NULL),
  boundingBox(NULL),
  weight(1),
  active(true) {
	direction = orientation * Ogre::Vector3::UNIT_Z;
}


Entity::~Entity() {
}

Ogre::Vector3 Entity::getVelocity() {
	return Ogre::Vector3::ZERO;
}

Ogre::Vector3 Entity::getPosition() {
	return position;
}

Ogre::Quaternion Entity::getOrientation() const {
	return orientation;
}

Ogre::Vector3 Entity::getDirection() const {
	return direction;
}

std::string Entity::getName() const {
	return name;
}

void Entity::setName(const std::string& n) {
	name = n;
}

Ogre::Real Entity::getWeight() {
	return weight;
}

void Entity::setScale(const Ogre::Vector3& scalex) {
	if(sceneNode != NULL && boundingBox != NULL) {
		sceneNode->scale(scalex);
	}
}

void Entity::setGameController(GameController* gameController) {
	this->gameController = gameController;
}

void Entity::activeGameController(bool activate) {
	controllerActive = activate;
}

void Entity::handleCollision(const Collision* collision) {}

bool Entity::validateCollision(Entity* entity) {
	return false;
}

void Entity::setSceneNode(Ogre::SceneNode& sceneNode) {
	this->sceneNode = &sceneNode;
}

void Entity::setBoundingBox() {
	boundingBox = &sceneNode->getAttachedObject(name)->getBoundingBox();
}

const Ogre::AxisAlignedBox* Entity::getBoundingBox() {
	return boundingBox;
}

void Entity::setBoundingSphere() {
	sphere = Sphere(position, 10);
}

Sphere Entity::getBoundingSphere() {
	return sphere;
}

void Entity::update(Ogre::Real dt) {}

void Entity::updateGameController() {}
