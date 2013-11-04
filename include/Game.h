#ifndef GAME_H
#define GAME_H

#ifndef PLATFORM_WIN32
	#include <OgreFrameListener.h>
#endif

#include "Util.h"
#include "Camera.h"
#include "Map.h"
#include "GameState.h"
#include "Timer.h"
#include "Wall.h"
#include "Floor.h"
#include "Log.h"
#include "Parser.h"
#include "Hud.h"

#include <string>
#include <iostream>

class BarrelFactory;
class PenguinFactory;
class WallFactory;
class Camera;
class Entity;
class MovableEntityFactory;
class GameController;
class InputHandler;
class Map;
class Timer;
class Floor;
class FloorGenerator;
class Wall;
class Parser;
class Hud;
class Hero;
class ParticleFactory;
class CollisionHandler;
class ELoadingBar;
class Robot;

class Game : public Ogre::FrameListener {

public:
	static Game* game;
	static Camera* camera;
	static Map* map;
	static BarrelFactory* barrelFactory;
	static PenguinFactory* penguinFactory;
	static WallFactory* wallFactory;
	static MovableEntityFactory* movableEntityFactory;
	static InputHandler* inputHandler;
	static GameController* gameController;
	static Timer* timer;
	static Parser* parser;
	static Hud* hud;
	static Hero* hero;
	static ParticleFactory* particleFactory;
	static CollisionHandler* collisionHandler;
	static ELoadingBar* loadingBar;
	static Wall* wall;
	static Floor* floor;
	static FloorGenerator* floorGenerator;
	static Robot* robot;
	
	static std::string data;
	static std::string debg;

	unsigned long lastTime;
	unsigned long newTime;
	unsigned long realTime;
	Ogre::Real fps;

	GameState gameState;
	bool active;

public:
	//OGRE
	static Ogre::Root* root;
	static Ogre::Viewport* viewport;
	static Ogre::RenderWindow* renderWindow;
	static Ogre::SceneManager* scene;
	static Ogre::Log* log;

public:
	Game();
	~Game();

	void loadGame();
	void runGame();
	static Game* instance();
	static void init();

	void loadResources(const std::string& configFile);

	void update(unsigned long dt);
	void updateEntities(Ogre::Real dt);
	void updateInput();
	virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt);

	GameState getGameState();
	void setGameState(GameState state);

	Timer* getTimer();
	
	static Ogre::SceneManager* getScene();
	static Ogre::RenderWindow* getRender();

	void quitGame();
};

#endif