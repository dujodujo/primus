#ifndef MAP_H
#define MAP_H

#include "Util.h"

#include <string>
#include <vector>
#include <list>

#include "MovableEntity.h"

//#include <Terrain\OgreTerrain.h>
//#include <Terrain\OgreTerrainGroup.h>
#include <OgreTerrain.h>
#include <OgreTerrainGroup.h>
#include <OgreLight.h>
#include <OgreStringConverter.h>
#include <OgreManualObject.h>

class Entity;
class MovableEntity;
class EntityFactory;
class Barrel;
class FloorGenerator;

class Map {

protected:
    Ogre::Light* sunLight;
    Ogre::Light* backLight;
    Ogre::Light* groundLight;

    Ogre::Real sceneWidth;
    Ogre::Real sceneHeight;

    unsigned int numXCells;
    unsigned int numYCells;
	static Ogre::Real cellSize;
	bool terrainLoaded;

	Ogre::TerrainGlobalOptions* terrainGlobals;
	Ogre::TerrainGroup* terrainGroup;

	std::vector<std::vector<std::list<MovableEntity*> > > movableEntities;
	std::vector<std::vector<std::list<Entity*> > > entites;

public:
	Map();
	~Map();

	bool loadMap(const std::string& mapName);
	void createGrid();

	Ogre::Light* setLights();

	Ogre::Rect getSize(Ogre::Real x, Ogre::Real y);

	void configureTerrain(Ogre::Light* light);

	std::pair<int, int> getCellID(Ogre::Real x, Ogre::Real y);
	void setCellID(std::pair<int, int> cell, Entity* entity);
	bool updateCellID(std::pair<int, int>& cell, Ogre::Vector3& position, MovableEntity* movableEntity);
	void removeCellID(std::pair<int, int>& cell, MovableEntity* movableEntity);

	void initBlendMaps(Ogre::Terrain* terrain);
	void getTerrainImage(bool flipx, bool flipy, Ogre::Image& image);
	void defineTerrain(int x, int y);
	void drawFallenTrees();
	void drawTrees();
	void drawRocks();
	void drawWater();

	bool isOutOfBounds(Ogre::Vector3& position);
	Ogre::Vector3 transformPosition(Ogre::Vector3& position);

	void update(Ogre::Real dt);
};

#endif