#include "Hero.h"
#include "Collision.h"

Hero::Hero(Ogre::Vector3 position, Ogre::Quaternion orientation,
  const std::string& name, Ogre::Real speed, Ogre::Radian turnSpeed) :
	MovableEntity(position, orientation, speed, turnSpeed) {
	std::string id = Factory::getID() + "." + name;

	Ogre::Entity* driveMesh = Game::getScene()->createEntity(id, "robot_drive.mesh");
	Ogre::Entity* chasisMesh = Game::getScene()->createEntity(id + "1", "robot_chasis.mesh");
	Ogre::Entity* armRightMesh = Game::getScene()->createEntity(id + "2", "robot_arm_right.mesh");
	Ogre::Entity* armLeftMesh = Game::getScene()->createEntity(id + "3", "robot_arm_left.mesh");
	Ogre::Entity* legRightMesh = Game::getScene()->createEntity(id + "4", "robot_leg_right.mesh");
	Ogre::Entity* legLeftMesh = Game::getScene()->createEntity(id + "5", "robot_leg_left.mesh");

	driveMesh->setMaterialName("red");
	chasisMesh->setMaterialName("red");
	armRightMesh->setMaterialName("red");
	armLeftMesh->setMaterialName("red");
	legRightMesh->setMaterialName("red");
	legLeftMesh->setMaterialName("red");

	sceneNode = Game::getScene()->getRootSceneNode()->createChildSceneNode();
	Ogre::SceneNode* chasisNode = sceneNode->createChildSceneNode();
	Ogre::SceneNode* armRightNode = sceneNode->createChildSceneNode();
	Ogre::SceneNode* armLeftNode = sceneNode->createChildSceneNode();
	Ogre::SceneNode* legRightNode = sceneNode->createChildSceneNode();
	Ogre::SceneNode* legLeftNode = sceneNode->createChildSceneNode();

	sceneNode->attachObject(driveMesh);
	chasisNode->attachObject(chasisMesh);
	armRightNode->attachObject(armRightMesh);
	armLeftNode->attachObject(armLeftMesh);
	legRightNode->attachObject(legRightMesh);
	legLeftNode->attachObject(legLeftMesh);

	/*	
	Ogre::Entity* entityMesh = Game::getScene()->createEntity(id, "jaiqua.mesh");
	sceneNode = Game::getScene()->getRootSceneNode()->createChildSceneNode();
	sceneNode->attachObject(entityMesh);

	int numModels = 4;
	loadAnimation();

	for(unsigned int i = 0; i < numModels; ++i) {
		//modelNodes.push_back(sceneNode);
		animationState = entityMesh->getAnimationState("Sneak");
		animationState->setEnabled(true);
		animationState->setLoop(true);
		animationSpeeds.push_back(Ogre::Math::RangeRandom(0.5f, 1.5f));
		animationStates.push_back(animationState);
	}
	*/

	sceneNode->showBoundingBox(true);
	sceneNode->setPosition(position);
	sceneNode->setOrientation(orientation);
	//sceneNode->setScale(0.4f, 0.4f, 0.4f);

	setName(id);
	setOrientation();
	setBoundingBox();
	setBoundingSphere();

	//Ogre::SceneNode* dustNode = sceneNode->createChildSceneNode();
	//dustNode->setPosition(position);
	//dust = static_cast<ParticleEffectDust*> (Game::particleFactory->createDust(dustNode, id));
	//animation = new Animation(sceneNode);
}

Hero::~Hero() {}

void Hero::loadAnimation() {
	/*
	Ogre::SkeletonPtr skeleton = Ogre::SkeletonManager::getSingleton().load("jaiqua.skeleton", 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	animation = skeleton->getAnimation("Sneak");
	*/
}

void Hero::startAnimation() {
	animationTrack = new AnimationTrack();
}

void Hero::moveHero(Ogre::Real dt) {
	Ogre::Real friction = 0.9;

	speed = velocity.dotProduct(direction);
	Ogre::Vector3 correctionVelocity = speed * direction;
	velocity = (1-friction) * velocity + correctionVelocity * friction;

	//Ogre::Real differenceVelocity = -velocity.dotProduct(direction);
	int throttle = gameController->getThrottle();
	Ogre::Real a = 1.f;
	Ogre::Vector3 accelaration = friction * direction * a;

	velocity = velocity + accelaration * dt;

	move = (velocity * dt) * throttle;
	position += move;

	Ogre::Radian turnSpeed = gameController->getTurnSpeed() * Ogre::Radian(1.f);

	orientation = Ogre::Quaternion(turnSpeed * dt, Ogre::Vector3::UNIT_Y) * orientation;
	direction = orientation * Ogre::Vector3::UNIT_Z;

	sceneNode->setPosition(position);
	sceneNode->setOrientation(orientation);
	sceneNode->setDirection(direction);
}

void Hero::handleCollision(Collision* collision) {
	this->position -= collision->move;
}

void Hero::update(Ogre::Real dt) {
	MovableEntity::update(dt);
	moveHero(dt);
	//animation->update(dt);
	/*
	for(unsigned int i = 0; i < numModels; ++i) {
		if(animationStates[i]->getTimePosition() >= 8) {
			animationStates[i]->setTimePosition(0);
		}
		this->animationStates[i]->addTime(animationSpeeds[i] * dt);
		if(this->animationStates.size() > 0) {}
	}
	*/
}