#include "BarrelFactory.h"
#include "PenguinFactory.h"
#include "WallFactory.h"
#include "Barrel.h"
#include "Penguin.h"
#include "FloorGenerator.h"
#include "Game.h"
#include "GameController.h"
#include "InputHandler.h"
#include "Entity.h"
#include "Hero.h"
#include "Robot.h"
#include "MovableEntityFactory.h"
#include "ParticleFactory.h"
#include "CollisionHandler.h"
#include "ELoadingBar.h"

Camera* Game::camera;
Map* Game::map;
Game* Game::game;

Ogre::RenderWindow* Game::renderWindow;
Ogre::Root* Game::root;
Ogre::SceneManager* Game::scene;
Ogre::Viewport* Game::viewport;
Ogre::Log* Game::log;

BarrelFactory* Game::barrelFactory;
PenguinFactory* Game::penguinFactory;
WallFactory* Game::wallFactory;
MovableEntityFactory* Game::movableEntityFactory;
GameController* Game::gameController;
InputHandler* Game::inputHandler;
Timer* Game::timer;
Parser* Game::parser;
Robot* Game::robot;
Hud* Game::hud;
Floor* Game::floor;
FloorGenerator* Game::floorGenerator;
Hero* Game::hero;
ParticleFactory* Game::particleFactory;
CollisionHandler* Game::collisionHandler;
ELoadingBar* Game::loadingBar;

const unsigned int fpsInterval = 16;

std::string Game::data = "C:/Users/dujo/Documents/Visual Studio 2010/Projects/Omecha/Omecha/data/";
std::string Game::debg = "C:/Users/dujo/Documents/ogre-sdk/OgreSDK_vc10_v1-8-1/";

Game::Game() {
	fps = 0;
	realTime = 0;
}

Game::~Game() {
	delete Game::barrelFactory;
	delete Game::penguinFactory;
	delete Game::wallFactory;
	delete Game::map;
	delete Game::movableEntityFactory;
	delete Game::gameController;
	delete Game::inputHandler;
	delete Game::timer;
	delete Game::parser;
	delete Game::hud;
	delete Game::floorGenerator;
	delete Game::floor;
	delete Game::robot;
	delete Game::hero;
	delete Game::particleFactory;
	delete Game::collisionHandler;
	delete game;
}

void Game::init() {
	Game::game = new Game();
}

Game* Game::instance() {
	return Game::game;
}

void Game::loadGame() {
	gameState = GameState::playing;

	//OGRE
	//const std::string data = "C:/Users/dujo/Documents/Visual Studio 2010/Projects/Omecha/Omecha/data/";
	const std::string config = "config/";
	const std::string graphics = "graphics";

	#ifdef _DEBUG
		const std::string resources = "resources_d.cfg";
		const std::string plugins = "plugins_d.cfg";
	#else
		const std::string resourcesCfg = "resources.cfg";
		const std::string pluginsCfg = "plugins.cfg";
	#endif

	Game::root = new Ogre::Root(plugins);

	if(root->showConfigDialog() || root->restoreConfig()) {
        //create window
		Game::renderWindow = root->initialise(true, "MechStar", "");
        //create scene manager
		Game::scene = root->createSceneManager(Ogre::ST_GENERIC);
        //setup shadow type - needs to be done first
		Game::scene->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

        //set resources
        Ogre::ResourceGroupManager& resourceManager = Ogre::ResourceGroupManager::getSingleton();
		resourceManager.addResourceLocation(Game::data + "model", "FileSystem", "modelss");
        resourceManager.addResourceLocation(Game::data + "model/target", "FileSystem", "targets");
        resourceManager.addResourceLocation(Game::data + "model/robot", "FileSystem", "robot");
		resourceManager.addResourceLocation(Game::data + "model/jaiqua", "FileSystem", "jaiqua");
		resourceManager.addResourceLocation(Game::data + "texture", "FileSystem", "texture");
		resourceManager.addResourceLocation(Game::data + "texture/hud", "FileSystem", "texturess");
		resourceManager.addResourceLocation(Game::data + "texture/particles", "FileSystem", "particles");
		resourceManager.addResourceLocation(Game::data + "hud", "FileSystem", "hud");
        resourceManager.addResourceLocation(Game::data + "terrain", "FileSystem", "terrain");
		resourceManager.addResourceLocation(Game::data + "materials", "FileSystem", "mats");

		resourceManager.addResourceLocation(Game::debg + "media/materials/programs", "FileSystem", "programs");
		resourceManager.addResourceLocation(Game::debg + "media/materials/scripts", "FileSystem", "scripts");
		resourceManager.addResourceLocation(Game::debg + "media/materials/textures", "FileSystem", "textures");
		resourceManager.addResourceLocation(Game::debg + "media/materials/textures/nvidia", "FileSystem", "nvidia");
		resourceManager.addResourceLocation(Game::debg + "media/models", "FileSystem", "models");
		resourceManager.addResourceLocation(Game::debg + "media/particle", "FileSystem", "particle");
		resourceManager.addResourceLocation(Game::debg + "media/DeferredShadingMedia", "FileSystem", "media");
		resourceManager.addResourceLocation(Game::debg + "media/PCZAppMedia", "FileSystem", "appmedia");
		resourceManager.addResourceLocation(Game::debg + "media/RTShaderLib", "FileSystem", "shader");
		resourceManager.addResourceLocation(Game::debg + "media/RTShaderLib/materials", "FileSystem", "materials");
		resourceManager.addResourceLocation(Game::debg + "media/materials/scripts/SSAO", "FileSystem", "SSAOs");
		resourceManager.addResourceLocation(Game::debg + "media/materials/textures/SSAO", "FileSystem", "SSAOt");
		resourceManager.addResourceLocation(Game::debg + "media/datafiles/imagesets", "FileSystem", "imagesets");
		resourceManager.addResourceLocation(Game::debg + "media/datafiles/fonts", "FileSystem", "fonts");
		resourceManager.addResourceLocation(Game::debg + "media/datafiles/schemes", "FileSystem", "schemes");
		resourceManager.addResourceLocation(Game::debg + "media/datafiles/looknfeel", "FileSystem", "looknfeel");
		resourceManager.addResourceLocation(Game::debg + "media/datafiles/layouts", "FileSystem", "layouts");

		resourceManager.initialiseResourceGroup("modelss");
		resourceManager.initialiseResourceGroup("robot");
		resourceManager.initialiseResourceGroup("targets");
		resourceManager.initialiseResourceGroup("texture");
		resourceManager.initialiseResourceGroup("texturess");
		resourceManager.initialiseResourceGroup("particles");
		resourceManager.initialiseResourceGroup("terrain");
		resourceManager.initialiseResourceGroup("hud");
		resourceManager.initialiseResourceGroup("mats");

		resourceManager.initialiseResourceGroup("programs");
		resourceManager.initialiseResourceGroup("scripts");
		resourceManager.initialiseResourceGroup("textures");
		resourceManager.initialiseResourceGroup("nvidia");
		resourceManager.initialiseResourceGroup("models");
		resourceManager.initialiseResourceGroup("particle");
		resourceManager.initialiseResourceGroup("media");
		resourceManager.initialiseResourceGroup("appmedia");
		resourceManager.initialiseResourceGroup("shader");
		resourceManager.initialiseResourceGroup("materials");
		resourceManager.initialiseResourceGroup("SSAOs");
		resourceManager.initialiseResourceGroup("SSAOt");
		resourceManager.initialiseResourceGroup("imagesets");
		resourceManager.initialiseResourceGroup("fonts");
		resourceManager.initialiseResourceGroup("schemes");
		resourceManager.initialiseResourceGroup("looknfeel");
		resourceManager.initialiseResourceGroup("layouts");
    }
}

void Game::runGame() {
	Game::log = Ogre::LogManager::getSingleton().createLog("Logfile.log", true, true, false);
    Game::camera = new Camera();

	viewport = renderWindow->addViewport(camera->getCamera());
    viewport->setBackgroundColour(Ogre::ColourValue::Black);

    Game::inputHandler = new InputHandler();
    Game::gameController = new GameController();
	Game::inputHandler->setController(Game::gameController);


	Game::timer = new Timer(Game::root->getTimer());
    //lastTime = timer->getTicks();
	lastTime = Game::root->getTimer()->getMilliseconds();

	Game::collisionHandler = new CollisionHandler();

	Game::hud = new Hud();
	Game::hud->loadHud();
	Game::hud->activateHud(true);

	Game::particleFactory = new ParticleFactory();
	//Game::particleFactory->createExplosion(Ogre::Vector3(0,0,0), 2.f, 20.f);
	
	Game::map = new Map();
	if(map->loadMap("arena")) {
		//gets frameRenderingQueued called every frame
        root->addFrameListener(this); 
        root->startRendering();  //go into ogre main loop 
    }

	//ELoadingBar* bar = new ELoadingBar();
	//ExampleLoadingBar* bar = new ExampleLoadingBar();
	//bar->start(Game::renderWindow);
	//bar->finish();
}

void Game::loadResources(const std::string& configFile) {
    Ogre::ConfigFile cf;
    cf.load(configFile);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while(seci.hasMoreElements()) {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for(i = settings->begin(); i != settings->end(); ++i) {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}

bool Game::frameRenderingQueued(const Ogre::FrameEvent &evt) {
	if(gameState == GameState::playing) {
        //newTime = timer->getTicks();
		newTime = Game::root->getTimer()->getMilliseconds();
        unsigned long dticks = newTime - lastTime;
        lastTime = newTime;
        //main game loop
        update(dticks);
	} else if(gameState == GameState::quit) {
        return false;
    } else {
        return false;
    }
    return true;
}

void Game::update(unsigned long dticks) {
	// ticks/seconds
	Ogre::Real dt = dticks / Ogre::Real(1000.f);
	updateInput();
	updateEntities(dt);

	Game::hud->update(dt);
	Game::camera->update(dt);
	Game::collisionHandler->update(dt);
}

void Game::updateEntities(Ogre::Real dt) {

	std::vector<Barrel*> barrels = Game::barrelFactory->getBarrels();
	std::vector<Barrel*>::iterator iter = barrels.begin();
	if(barrels.size() > 0) {
		for(iter; iter != barrels.end(); iter++) {
			(*iter)->update(dt);
			(*iter)->select();
		}
	}

	std::vector<Penguin*> penguins = Game::penguinFactory->getPenguins();
	std::vector<Penguin*>::iterator it = penguins.begin();
	if(penguins.size() > 0) {
		for(it; it != penguins.end(); it++) {
			(*it)->update(dt);
			(*it)->select();
		}
	}

	Game::robot->update(dt);
	Game::hero->update(dt);
	//Game::particleFactory->update(dt);
}

void Game::updateInput() {
	this->inputHandler->update();
}

GameState Game::getGameState() { 
	return gameState; 
}

void Game::setGameState(GameState state) { 
	gameState = state;
}

Ogre::SceneManager* Game::getScene() {
	return Game::scene;
}

Ogre::RenderWindow* Game::getRender() {
	return renderWindow;
}

void Game::quitGame() {
	this->gameState = GameState::quit;
}

Timer* Game::getTimer() {
	return Game::timer;
}