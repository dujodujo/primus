#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

#include "Util.h"
#include "CollisionMode.h"
#include "Sphere.h"

class GameController;
class Collision;
class Sphere;

class Entity {

protected:
	Ogre::Vector3 position;
	Ogre::Vector3 direction;
	Ogre::Vector3 scale;
	
	Ogre::Quaternion orientation;
	Ogre::SceneNode* sceneNode;
	
	const Ogre::AxisAlignedBox* boundingBox;
	Ogre::Real weight;
	std::string name;
	bool controllerActive;
	bool active;
	Sphere sphere;

	GameController* gameController;

public:
	Entity(Ogre::Vector3 position, Ogre::Quaternion orientation, const std::string& name, 
		Ogre::SceneNode* sceneNode);
	Entity(Ogre::Vector3 position, Ogre::Quaternion orientation);
	virtual ~Entity();

	Ogre::Vector3 getVelocity();
	
	void setBoundingBox();
	const Ogre::AxisAlignedBox* getBoundingBox();

	void setBoundingSphere();
	Sphere getBoundingSphere();

	std::string getName() const;
	void setName(const std::string& name);

	Ogre::Real getWeight();
	void setScale(const Ogre::Vector3& scalex);

	//position
	Ogre::Vector3 getPosition();
	Ogre::Real getX() { return this->position.x; }
	Ogre::Real getY() { return this->position.y; }
	Ogre::Real getZ() { return this->position.z; }

	Ogre::Quaternion getOrientation() const;
	Ogre::Vector3 getDirection() const;

	//controllers
	void setGameController(GameController* gameController);
	GameController* getGameController() { return gameController; }
	void activeGameController(bool activate);

	//collision
	virtual void handleCollision(const Collision* collision);
	virtual bool validateCollision(Entity* entity);

	Ogre::SceneNode* getSceneNode() { return this->sceneNode; }
	void setSceneNode(Ogre::SceneNode& sceneNode);

	virtual void update(Ogre::Real dt);
	virtual void updateGameController();
};

#endif