#ifndef HUD_DESIGN_H
#define HUD_DESIGN_H

#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayElement.h>

#include <string>
#include <vector>

const unsigned int numHudAreas = 3;

enum HudArea { hud_status, hud_heat, hud_log };

const std::string hudAreaNames[numHudAreas] = { "hud_status", "hud_heat", "hud_log" };

enum Position { left, center, right, top, bottom };

struct HudParts {
	HudArea area;
	std::string name;
	std::pair<int, int> position;
	std::pair<int, int> size;
	std::vector<Ogre::Real> parameters;
};

struct HudComponents {
	std::string name;
	std::string fontName;
	std::vector<std::string> areaTextures;
	std::vector<std::pair<int, int>> positions;
	std::vector<std::pair<int, int>> sizes;
	std::vector<HudParts> parts;
};

#endif