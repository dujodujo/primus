#ifndef PARSER_H
#define PARSER_H

#include "HudDesign.h"
#include "HudPart.h"
#include "Game.h"
#include "Sphere.h"

#include <map>
#include <sstream>
#include <fstream>

class Game;

struct HudParts;
struct HudComponents;

class Parser {

public:
	static Parser* instance();
	static void init();

	~Parser();

	static void stripWhitespaces(std::string& s);
	static void getStringValues(std::vector<std::string>& values, std::string buffer);
	static void getIntPairValues(std::vector<std::pair<int, int>>& values, std::string buffer);
	static void getRealValues(std::vector<Ogre::Real>& values, std::string buffer);

	template <typename T>
	static void getIntValues(std::vector<T>& values, std::string buffer);
	static bool getPairValues(const std::string& fileName, std::map<std::string, std::string>& pairs);
	static void getColorValues(std::vector<Ogre::ColourValue>& values, std::string buffer);

	template <typename M, typename N>
	static void getEnumPairValues(std::vector<std::pair<M, N>>& values, std::string buffer);

	template <typename T>
	static void getEnumValues(std::vector<T>& values, std::string buffer);
	static int toEnum(std::string string);

	static bool getHudDesign(const std::string& name, HudComponents& hudComponents);
	static bool getCollisionSpheres(const std::string& name, Sphere& boundingSphere);

private:
	Parser();
	static Parser* parser;
};

#endif