#include "Game.h"
#include "InputHandler.h"
#include "GameController.h"
#include "Hero.h"

InputHandler::InputHandler() : 
  cameraDistance(1400) {
	OIS::ParamList paramList;
	unsigned int window;
	Game::renderWindow->getCustomAttribute("WINDOW", &window);
	paramList.insert(OIS::ParamList::value_type("WINDOW",
		Ogre::StringConverter::toString(window)));

	//start OIS
	inputManager = OIS::InputManager::createInputSystem(paramList);
	keyboard = static_cast<OIS::Keyboard*>(
		inputManager->createInputObject(OIS::OISKeyboard, true));
	keyboard->setEventCallback(this);

	mouse = static_cast<OIS::Mouse*>(
		inputManager->createInputObject(OIS::OISMouse, true));
	mouse->setEventCallback(this);

	Ogre::WindowEventUtilities::addWindowEventListener(Game::renderWindow, this);

	//center pointer position
	pointerX = 0.5f;
	pointerY = 0.5f;

	Ogre::Camera* cam = Game::camera->getCamera();
	ray = new Ogre::Ray();
    raySceneQuery = new Ogre::DefaultRaySceneQuery(Game::scene);
    raySceneQuery->setSortByDistance(true);
	raySceneQuery->setQueryMask(1<<0);

	screenWidth = Game::renderWindow->getWidth();
	screenHeight = Game::renderWindow->getHeight(); 

	resize();

    Ogre::Entity* pointerMeshCenter = Game::scene->createEntity("pointer_center", "target_center.mesh");

	pointerMeshCenter->setMaterialName("target");
    pointerMeshCenter->setQueryFlags(1 << 3);
    pointerMeshCenter->setCastShadows(false);
    
	centerNode = Game::scene->getRootSceneNode()->createChildSceneNode();
	centerNode->setScale(Ogre::Vector3(.5f, .5f, .5f));
    centerNode->attachObject(pointerMeshCenter);
}

InputHandler::~InputHandler() {
	inputManager->destroyInputObject(mouse);
	inputManager->destroyInputObject(keyboard);
	OIS::InputManager::destroyInputSystem(inputManager);
}

void InputHandler::updateMousePointer() {
	Ogre::Camera* cam = Game::camera->getCamera();
	cam->getCameraToViewportRay(pointerX, pointerY, ray);
	
	raySceneQuery->setRay(*ray);
	Ogre::RaySceneQueryResult& result = raySceneQuery->execute();

	Ogre::RaySceneQueryResult::iterator iter;
	Ogre::Real closestDistance = 10000;
	for(iter = result.begin(); iter != result.end(); ++iter) {
		if(closestDistance > (*iter).distance) {
			closestDistance = (*iter).distance;
		}
	}
	raySceneQuery->clearResults();
	
	Ogre::Vector3 position;

	if(closestDistance < 10000) {
		position = ray->getPoint(closestDistance);
	} else {
		const Ogre::Real step = 128;
		Ogre::Real topDistance = cameraDistance + step;
		Ogre::Real bottomDistance = cameraDistance - step;
		position = ray->getPoint(cameraDistance);
		
		Ogre::Real middleDistance;
		Ogre::Real sliceSize = step;
		while(sliceSize > 0.01f) {
			sliceSize = sliceSize/2;
			middleDistance = topDistance + sliceSize;
			position = ray->getPoint(middleDistance);
		}
	}
	gameController->setPointerPosition(position);
	centerNode->setPosition(position);

	position = gameController->getPointerPosition();
}

void InputHandler::update() {
	mouse->capture();
	keyboard->capture();
	updateMousePointer();
}

void InputHandler::windowResized(Ogre::RenderWindow* renderWindow) {
	this->screenWidth = renderWindow->getWidth();
	this->screenHeight = renderWindow->getHeight();

	if(screenWidth < 320) {
		screenWidth = 320;
		renderWindow->resize(screenWidth, screenHeight);
	}
	if(screenHeight < 320) {
		screenHeight = 320;
		renderWindow->resize(screenWidth, screenHeight);
	}

	if(screenWidth < screenHeight) {
		screenHeight = screenWidth;
		renderWindow->resize(screenWidth, screenHeight);
	} else if(screenWidth > 3 * screenHeight) {
		screenWidth = screenHeight * 3;
		renderWindow->resize(screenWidth, screenHeight);
	}

	resize();
	Game::camera->resize(screenWidth, screenHeight);
}

void InputHandler::resize() {
	const OIS::MouseState& mouseState = mouse->getMouseState();
	mouseState.width = screenWidth;
	mouseState.height = screenHeight;
}

bool InputHandler::mouseMoved(const OIS::MouseEvent& evt) {
	const OIS::MouseState& mouseState = mouse->getMouseState();
	//mouse position in pixels
	this->pointerX = mouseState.X.abs;
	this->pointerY = mouseState.Y.abs;

	//translate to <0,1>
	this->pointerX /= mouseState.width;
	this->pointerY /= mouseState.height;

	if(Game::camera->style == Game::camera->Orbit) {
		Ogre::Real distance = (Game::camera->position - Game::camera->target->_getDerivedPosition()).length();
		if(Game::camera->orbit) {
			Game::camera->camera->setPosition(Game::camera->target->_getDerivedPosition());
			Game::camera->camera->yaw(Ogre::Degree(-mouseState.X.rel));
			Game::camera->camera->pitch(Ogre::Degree(-mouseState.Y.rel));
			Game::camera->camera->moveRelative(Ogre::Vector3(0, 0, distance));
		} else if(Game::camera->zoom) {
			Game::camera->camera->moveRelative(Ogre::Vector3(0, 0, mouseState.Y.rel*distance));
		} else if(mouseState.Z.rel != 0) {
			Game::camera->camera->moveRelative(Ogre::Vector3(0, 0, -mouseState.Z.rel*distance));
		}
	} else if(Game::camera->style = Game::camera->FreeLook) {
		Game::camera->camera->yaw(Ogre::Degree(-mouseState.X.rel));
		Game::camera->camera->pitch(Ogre::Degree(-mouseState.Y.rel));
	}
	return true;
}

bool InputHandler::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID) {
	const OIS::MouseState& mouseState = mouse->getMouseState();
	if(Game::camera->style == Game::camera->Orbit) {
		if(mouseState.buttonDown(OIS::MB_Right)) {
			Game::camera->orbit = true;
		} else {
			Game::camera->zoom = true;
		}
	}
	return true;
}

bool InputHandler::mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID) {
	const OIS::MouseState& mouseState = mouse->getMouseState();
	if(Game::camera->style == Game::camera->Orbit) {
		if(mouseState.buttonDown(OIS::MB_Right)) {
			Game::camera->orbit = false;
		} else {
			Game::camera->zoom = false;
		}
	}
	return true;
}

bool InputHandler::keyPressed(const OIS::KeyEvent& evt) {
	/*
	if(evt.key == OIS::KC_UP) {
		gameController->setThrottle(1.f);
	} else if(evt.key == OIS::KC_DOWN) {
		gameController->setThrottle(-1.f);
	} else if(evt.key == OIS::KC_RIGHT) {
		gameController->setTurnRate(-1.f);
	} else if(evt.key == OIS::KC_LEFT) {
		gameController->setTurnRate(1.f);
	} else if(evt.key == OIS::KC_3) {
		Game::hero->startAnimation();
	} else if(evt.key == OIS::KC_ESCAPE) {
		Game::game->quitGame();
	}
	*/

	if(evt.key == OIS::KC_UP) 
		Game::camera->forward = true;
	else if(evt.key == OIS::KC_DOWN) 
		Game::camera->back = true;
	else if(evt.key == OIS::KC_LEFT) 
		Game::camera->left = true;
	else if(evt.key == OIS::KC_RIGHT) 
		Game::camera->right = true;
	else if(evt.key == OIS::KC_W) 
		Game::camera->up = true;
	else if(evt.key == OIS::KC_S) 
		Game::camera->down = true;
	else if(evt.key == OIS::KC_ESCAPE)
		Game::game->quitGame();

	return true;
}

bool InputHandler::keyReleased(const OIS::KeyEvent& evt) {
	/*
	if(evt.key == OIS::KC_UP) {
		gameController->setThrottle(0.f);
	}else if(evt.key == OIS::KC_DOWN) {
		gameController->setThrottle(0.f);
	}else if(evt.key == OIS::KC_RIGHT) {
        if (keyboard->isKeyDown(OIS::KC_RIGHT))
            gameController->setTurnRate(1.f);
        else
            gameController->setTurnRate(0.f);
    }  else if(evt.key == OIS::KC_LEFT) {
        if (keyboard->isKeyDown(OIS::KC_LEFT))
            gameController->setTurnRate(-1.f);
        else
            gameController->setTurnRate(0.f);
    }
	*/

	if(evt.key == OIS::KC_UP) 
		Game::camera->forward = false;
	else if(evt.key == OIS::KC_DOWN) 
		Game::camera->back = false;
	else if(evt.key == OIS::KC_LEFT) 
		Game::camera->left = false;
	else if(evt.key == OIS::KC_RIGHT) 
		Game::camera->right = false;
	else if(evt.key == OIS::KC_W) 
		Game::camera->up = false;
	else if(evt.key == OIS::KC_S) 
		Game::camera->down = false;

	return true;
}

void InputHandler::setController(GameController* controller) {
	gameController = controller;
}