#include "BarrelFactory.h"
#include "PenguinFactory.h"
#include "WallFactory.h"
#include "Camera.h"
#include "Entity.h"
#include "Game.h"
#include "Map.h"
#include "FloorGenerator.h"
#include "MovableEntityFactory.h"
#include "Barrel.h"
#include "Penguin.h"
#include "Hero.h"
#include "Robot.h"

Ogre::Real Map::cellSize = 10;

Map::Map() :
  sceneWidth(12000),
  sceneHeight(12000),
  terrainLoaded(false) {
	
	Game::barrelFactory = new BarrelFactory();
	Game::penguinFactory = new PenguinFactory();
	Game::wallFactory = new WallFactory();
	Game::floorGenerator = new FloorGenerator("heightmapGenerator.bmp");

	terrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();
	terrainGroup = OGRE_NEW Ogre::TerrainGroup(Game::scene, Ogre::Terrain::ALIGN_X_Z, 513, sceneWidth);
	terrainGroup->setFilenameConvention(Ogre::String("Terrain"), Ogre::String("dat"));
	terrainGroup->setOrigin(Ogre::Vector3::ZERO);

	Ogre::Light* light = setLights();
	configureTerrain(light);

	defineTerrain(0, 0);

	terrainGroup->loadAllTerrains(true);

	if(terrainLoaded) {
		Ogre::TerrainGroup::TerrainIterator terrainIterator = terrainGroup->getTerrainIterator();
		while(terrainIterator.hasMoreElements()) {
			Ogre::Terrain* terrain = terrainIterator.getNext()->instance;
			initBlendMaps(terrain);
		}
	}

	Game::scene->setSkyDome(true, "Examples/CloudySky", 4, 10);
	
	terrainGroup->freeTemporaryResources();
	drawFallenTrees();
	drawRocks();
	drawTrees();
	drawWater();
}

Map::~Map() {
	Game::getScene()->destroyAllLights();
	OGRE_DELETE terrainGlobals;
	OGRE_DELETE terrainGroup;
}

void Map::configureTerrain(Ogre::Light* light) {
	terrainGlobals->setMaxPixelError(8);
	terrainGlobals->setCompositeMapDistance(30000);
	terrainGlobals->setLightMapDirection(light->getDerivedDirection());
	terrainGlobals->setCompositeMapAmbient(Game::getScene()->getAmbientLight());
	terrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());

	Ogre::Terrain::ImportData& import = terrainGroup->getDefaultImportSettings();
    import.terrainSize = 513;
    import.worldSize = sceneWidth;
    import.inputScale = 600*6;
    import.minBatchSize = 33;
    import.maxBatchSize = 65;

	import.layerList.resize(3);
    import.layerList[0].worldSize = 30;
    import.layerList[0].textureNames.push_back(Game::debg + "media/materials/textures/mossy_stone_S.dds");
    import.layerList[0].textureNames.push_back(Game::debg + "media/materials/textures/mossy_stone_N.dds");
	
	import.layerList[1].worldSize = 800;
    import.layerList[1].textureNames.push_back(Game::debg + "media/materials/textures/WallRubble_D.dds");
    import.layerList[1].textureNames.push_back(Game::debg + "media/materials/textures/WallRubble_N.dds");
    
	import.layerList[2].worldSize = 200;
	import.layerList[2].textureNames.push_back(Game::debg + "media/materials/textures/grass_green.dds");
	import.layerList[2].textureNames.push_back(Game::debg + "media/materials/textures/grass_green.dds");
}

Ogre::Light* Map::setLights() {
    sunLight = Game::getScene()->createLight("sunlight");
    backLight = Game::getScene()->createLight("backlight");
    groundLight = Game::getScene()->createLight("ground_light");

	Game::getScene()->setAmbientLight(Ogre::ColourValue(0.2f, 0.2f, 0.2f));
	Ogre::Light* light = Game::getScene()->createLight("MainLight");
	light->setPosition(20, 80, 50);

    Game::getScene()->setShadowColour(Ogre::ColourValue(0.1, 0.1, 0.1));

    sunLight->setType(Ogre::Light::LT_DIRECTIONAL);
	sunLight->setCastShadows(true);
    sunLight->setPosition(Ogre::Vector3(50, 50, 50));
    sunLight->setCastShadows(false);
    
	backLight->setType(Ogre::Light::LT_DIRECTIONAL);
    backLight->setCastShadows(true);
	groundLight->setType(Ogre::Light::LT_DIRECTIONAL);
    groundLight->setCastShadows(true);

	return light;
}

bool Map::loadMap(const std::string& mapName) {
	Wall* wall2 = Game::wallFactory->createWall(200, 100, 
		Ogre::Vector3(sceneWidth, sceneHeight, 0), WallFactory::Direction::XX);

	Game::robot = new Robot(Ogre::Vector3(200, 0, 100), Ogre::Quaternion(1, 0, 0, 0), "robot");

	//Ogre::Vector3 penguinPosition = transformPosition(Ogre::Vector3(0, 10, 0));
	Ogre::Vector3 penguinPosition = Ogre::Vector3(10, 0, 10);
	Penguin* penguin = Game::penguinFactory->createPenguin(penguinPosition,
		"penguin", Ogre::Quaternion(1, 0, 0, 0), 0.f, Ogre::Radian::Radian(1.f));

	//Ogre::Vector3 barrelPosition = transformPosition(Ogre::Vector3(20, 10, 20));
	Ogre::Vector3 barrelPosition = Ogre::Vector3(85, 0, 85);
	Barrel* barrel1 = Game::barrelFactory->createBarrel(barrelPosition, 
		"jaiqua", Ogre::Quaternion(1, 0, 0, 0), 0.f, Ogre::Radian::Radian(1.f));

	//Ogre::Vector3 heroPosition = transformPosition(Ogre::Vector3(64, 10, 64));
	Ogre::Vector3 heroPosition = Ogre::Vector3(45, 0, 45);
	Game::hero = new Hero(heroPosition, Ogre::Quaternion(1, 0, 0, 0), 
		"hero", 10.f, Ogre::Radian::Radian(1.f));
	
	Game::hero->setBoundingBox();
	Game::hero->setGameController(Game::gameController);

	return true;
}

void Map::createGrid() {
	numXCells = sceneWidth / cellSize;
    numYCells = sceneHeight / cellSize;
	//set 2d cell size indices holding entities on the map
	movableEntities = std::vector<std::vector<std::list<MovableEntity*> > >(numXCells, numYCells);
	entites = std::vector<std::vector<std::list<Entity*> > >(numXCells, numYCells);
}

void Map::initBlendMaps(Ogre::Terrain* terrain) {
	Ogre::TerrainLayerBlendMap* xBlendMap = terrain->getLayerBlendMap(1);
	Ogre::TerrainLayerBlendMap* yBlendMap = terrain->getLayerBlendMap(2);
	Ogre::Real xMinHeight = 0;
	Ogre::Real yMinHeight = 0;
	Ogre::Real xFadeDist = 40;
	Ogre::Real yFadeDist = 40;
	
	float* pxBlend = xBlendMap->getBlendPointer();
	float* pyBlend = yBlendMap->getBlendPointer();

	for(Ogre::uint16 xx = 0; xx < terrain->getLayerBlendMapSize(); xx++) {
		for(Ogre::uint16 yy = 0; yy < terrain->getLayerBlendMapSize(); yy++) {
			Ogre::Real tx, ty;
			xBlendMap->convertImageToTerrainSpace(yy, xx, &ty, &tx);
			Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
			Ogre::Real value = (height-xMinHeight)/xFadeDist;
			value = Ogre::Math::Clamp(value, (Ogre::Real)0, (Ogre::Real)1);
			*pxBlend++ = value;

			value = (height-yMinHeight)/yFadeDist;
			value = Ogre::Math::Clamp(value, (Ogre::Real)0, (Ogre::Real)1);
			*pyBlend++ = value;
		}
	}
	xBlendMap->dirty();
	yBlendMap->dirty();
	xBlendMap->update();
	yBlendMap->update();
}

void Map::getTerrainImage(bool flipx, bool flipy, Ogre::Image& image) {
	image.load(Game::debg + "media/materials/textures/heightmap.bmp", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	if(flipx)
		image.flipAroundY();
	if(flipy)
		image.flipAroundX();
}

void Map::defineTerrain(int x, int y) {
	Ogre::String fileName = terrainGroup->generateFilename(x, y);
	if(Ogre::ResourceGroupManager::getSingleton().resourceExists(terrainGroup->getResourceGroup(), fileName)) {
		terrainGroup->defineTerrain(x, y);
	} else {
		Ogre::Image image;
		int xx = x % 2 != 0;
		int yy = y % 2 != 0;
		getTerrainImage(xx, yy, image);
		terrainGroup->defineTerrain(xx, yy, &image);
		terrainLoaded = true;
	}
}

void Map::drawFallenTrees() {
	Ogre::Vector2* line = Game::floorGenerator->getLine();
	Ogre::Entity* fallenTree = Game::getScene()->createEntity(Factory::getID()+".treeFallen", "tree_log.mesh");
	Ogre::SceneNode* treeNode = Game::getScene()->getRootSceneNode()->createChildSceneNode();

	Ogre::Quaternion orientation;
	orientation.FromAngleAxis(Ogre::Degree(Ogre::Math::RangeRandom(0, 359)), Ogre::Vector3::UNIT_SCALE);
	treeNode->rotate(orientation);

	float scale = 1;
	treeNode->setScale(scale, scale, scale);

	int segment = Ogre::Math::RangeRandom(0, 36);
	float x = -sceneWidth/2+line[segment].x/512*sceneWidth;
    float z =  sceneWidth/2+line[segment].y/512*sceneWidth;
    x += 25 * Ogre::Math::RangeRandom(-25, 0);
    z += 25 * Ogre::Math::RangeRandom(-25, 0);
    float y = terrainGroup->getHeightAtWorldPosition(x, 0, z);
    
	treeNode->translate(x, y, z);
    treeNode->attachObject(fallenTree);
}

void Map::drawTrees() {
	for(int i = 0; i < 12; i++) {
		float x = Ogre::Math::RangeRandom(-sceneWidth/2, sceneWidth/2);
		float z = Ogre::Math::RangeRandom(-sceneWidth/2, sceneWidth/2);
		float y = terrainGroup->getHeightAtWorldPosition(x, 0, z);
		float scale = Ogre::Math::RangeRandom(1, 3);

		Ogre::Entity* entityTree = Game::getScene()->createEntity(Factory::getID()+".tree", "oakA.mesh");
		Ogre::SceneNode* treeNode = Game::getScene()->getRootSceneNode()->createChildSceneNode();
		treeNode->setScale(scale, scale, scale);
		treeNode->translate(x, y, z);
		treeNode->attachObject(entityTree);
	}
}

void Map::drawRocks() {
	Ogre::Vector2* line = Game::floorGenerator->getLine();
	for(int i = 0; i < 12; i++) {
		Ogre::Entity* entityRock = Game::getScene()->createEntity(Factory::getID()+".rock", "boulder_02.mesh");
		Ogre::SceneNode* rockNode = Game::getScene()->getRootSceneNode()->createChildSceneNode();

		float scale = Ogre::Math::RangeRandom(1, 2);
		rockNode->setScale(scale, scale, scale);

		Ogre::Quaternion orientation;
		orientation.FromAngleAxis(Ogre::Degree(Ogre::Math::RangeRandom(0, 360)), Ogre::Vector3::UNIT_SCALE);
		rockNode->rotate(orientation);

		float x = -sceneWidth/2 + (line[i].x/512 * sceneWidth);
		float z =  sceneWidth/2 - (line[i].y/512 * sceneWidth);
		x += 25 * Ogre::Math::SymmetricRandom(); 
		z += 25 * Ogre::Math::SymmetricRandom();
		float y = terrainGroup->getHeightAtWorldPosition(x, 0, z);
		rockNode->translate(x, y, z);
		rockNode->attachObject(entityRock);
	}

	for(int i = 0; i < 12; i+=1) {
		Ogre::Entity* entityRock = Game::getScene()->createEntity(Factory::getID()+"."+"rock", "boulder_03.mesh");
		Ogre::SceneNode* rockNode = Game::getScene()->getRootSceneNode()->createChildSceneNode();

		float scale = Ogre::Math::RangeRandom(1, 2);
		rockNode->setScale(scale, scale, scale);

		Ogre::Quaternion orientation;
		orientation.FromAngleAxis(Ogre::Degree(Ogre::Math::RangeRandom(0, 360)), Ogre::Vector3::UNIT_SCALE);
		rockNode->rotate(orientation);

		float x = -sceneWidth/2 + line[i].x/512 * sceneWidth;
        float z = sceneWidth/2 - line[i].y/512 * sceneWidth;
        float side = Ogre::Math::UnitRandom() < 0.5 ? -1 : 1;
        x += 25 * Ogre::Math::RangeRandom(10, 15) * side;
        z += 25 * Ogre::Math::RangeRandom(10, 15) * side;
        float y = terrainGroup->getHeightAtWorldPosition(x, 0, z);
        rockNode->translate(x, y, z);
        rockNode->attachObject(entityRock);
	}
}

void Map::drawWater() {
	Game::floor = new Floor(sceneWidth, sceneHeight, "water", "WaterEntity", "planeMat", "water.jpg");
}

bool Map::isOutOfBounds(Ogre::Vector3& position) {
	bool out = false;

	if(position.x < 0) {
		position.x = 0;
		out = true;
	}else if(position.x >= sceneWidth) {
		position.x = sceneWidth - cellSize;
		out = true;
	}

	if(position.z < 0) {
		position.z = 0;
		out = true;
	} else if(position.z >= sceneHeight) {
		position.z = sceneHeight - cellSize;
		out = true;
	}
	return out;
}

std::pair<int, int> Map::getCellID(Ogre::Real x, Ogre::Real y) {
	int i = x / cellSize;
	int j = y / cellSize;
	return std::make_pair(i, j);
}

void Map::setCellID(std::pair<int, int> cell, Entity* entity) {
	this->entites[cell.first][cell.second].push_back(entity);
}

bool Map::updateCellID(std::pair<int, int>& cellID, Ogre::Vector3& position, MovableEntity* movableEntity) {
	bool out = isOutOfBounds(position);
	std::pair<int, int> currentCellID = getCellID(position.x, position.y);
	if(cellID != currentCellID) {
		movableEntities[cellID.first][cellID.second].remove(movableEntity);
		cellID = currentCellID;
		movableEntities[cellID.first][cellID.second].push_back(movableEntity);
	}
	return out;
}

void Map::removeCellID(std::pair<int, int>& cell, MovableEntity* movableEntity) {
	if(movableEntities[cell.first][cell.second].size() > 0) {
		std::list<MovableEntity*>::iterator begin = movableEntities[cell.first][cell.second].begin();
		std::list<MovableEntity*>::iterator end = movableEntities[cell.first][cell.second].end();
		if(std::count(begin, end, movableEntity) > 0) {
			movableEntities[cell.first][cell.second].remove(movableEntity);
		}
	}
}

Ogre::Rect Map::getSize(Ogre::Real x, Ogre::Real y) {
	return Ogre::Rect(0,0,0,0);
}

Ogre::Vector3 Map::transformPosition(Ogre::Vector3& position) {
	float y = terrainGroup->getHeightAtWorldPosition(position.x, 0, position.z) + position.y;
	return Ogre::Vector3(position.x, y, position.z);
}

void Map::update(Ogre::Real dt) {}
