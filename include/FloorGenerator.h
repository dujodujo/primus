#ifndef FLOOR_GENERATOR_H
#define FLOOR_GENERATOR_H

#define DEPTH 6
#define WIDTH 640
#define HEIGHT 480

#include <string>
#include <vector>

#include <OGRE\OgreVector2.h>

class Floor;

class FloorGenerator {

private:
	Ogre::Vector2* points;
	Ogre::Vector2* lines;

public:
	FloorGenerator(const std::string& floorName);
	~FloorGenerator();

	void createFloor(const std::string& floorName);

	float valley(float x);
	float lineDistance(Ogre::Vector2 v, Ogre::Vector2 w, Ogre::Vector2 p);
	
	Ogre::Vector2* createLine(Ogre::Vector2 start, Ogre::Vector2 end);
	Ogre::Vector2* point(Ogre::Vector2* points, int start, int end, int depth);

	float randomDepth(int depth);
	float lengthSquared(Ogre::Vector2* v, Ogre::Vector2* w);
	
	Ogre::Vector2* getLine();
};

#endif