#include "Robot.h"

Robot::Robot(Ogre::Vector3 position, Ogre::Quaternion orientation, const std::string& name) :
  MovableEntity(position, orientation, 0.1f, Ogre::Degree(0.f)),
  animationState(0),
  destination(position) {

	std::string id = Factory::getID() + "." + name;

	robotMesh = Game::getScene()->createEntity(id, "robot.mesh");
	sceneNode = Game::getScene()->getRootSceneNode()->createChildSceneNode();
	sceneNode->attachObject(robotMesh);
	sceneNode->scale(.25f, .25f, .25f);
	sceneNode->showBoundingBox(true);
	sceneNode->setPosition(position);

	walkingList.push_back(Ogre::Vector3(position));
	walkingList.push_back(Ogre::Vector3(300.f, 0.f, 100.f));
	walkingList.push_back(Ogre::Vector3(400.f, 0.f, 100.f));
	walkingList.push_back(Ogre::Vector3(500.f, 0.f, 100.f));
	walkingList.push_back(Ogre::Vector3(600.f, 0.f, 100.f));
	walkingList.push_back(Ogre::Vector3(700.f, 0.f, 100.f));
	walkingList.push_back(Ogre::Vector3(800.f, 0.f, 100.f));

	Ogre::Entity* knotEntity;
    Ogre::SceneNode* knotNode;

	int size = walkingList.size();
	Game::log->logMessage(toString(size));

	Ogre::Vector3 knotScale = Ogre::Vector3(.05f, .05f, .05f);
	for(int i = 0; i < walkingList.size(); i++) {
		std::string name = Factory::getID() + ".knotMesh";
		knotEntity = Game::scene->createEntity(name, "knot.mesh");
		std::string nameNode = Factory::getID() + ".knotNode";
		knotNode = Game::scene->getRootSceneNode()->createChildSceneNode(nameNode, 
			walkingList.at(i));
		knotNode->attachObject(knotEntity);
		knotNode->scale(knotScale);
	}
	animationState = robotMesh->getAnimationState("Idle");
	animationState->setLoop(true);
	animationState->setEnabled(true);
}

Robot::~Robot() {}

void Robot::moveRobot(Ogre::Real dt) {
	velocity = speed * direction;
	move = velocity * dt;
	position += move;
	sceneNode->setPosition(position);

	Ogre::Vector3 source = sceneNode->getOrientation() * Ogre::Vector3::UNIT_X;
	Ogre::Quaternion quat = source.getRotationTo(direction);
	sceneNode->rotate(quat);
	sceneNode->setOrientation(orientation);
	sceneNode->setDirection(direction);
}

bool Robot::nextLocation() {
	if(walkingList.empty())
		return false;

	destination = walkingList.front();
	walkingList.pop_front();

	direction = destination - sceneNode->getPosition();
	return true;
}

void Robot::update(Ogre::Real dt) {
	Ogre::Real dist = Ogre::Math::Abs(Ogre::Vector3(position-destination).length());
	MovableEntity::update(dt);
	moveRobot(dt);

	if(!walkingList.empty()) {
		if(dist <= 1.f) {
			if(nextLocation()) {
				Game::log->logMessage("walk");
				animationState = robotMesh->getAnimationState("Walk");
				animationState->setLoop(true);
				animationState->setEnabled(true);
			}
		}
	} else {
		if(dist <= 1.f) {
			Game::log->logMessage("stop");
			animationState = robotMesh->getAnimationState("Idle");
			animationState->setLoop(true);
			animationState->setEnabled(true);
			this->speed = 0;
		}
	}
	animationState->addTime(dt);
}