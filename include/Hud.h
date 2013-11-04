#ifndef HUD_H
#define HUD_H

#include "Game.h"
#include "HudDesign.h"
#include "HudStatusDisplay.h"
#include "Parser.h"
#include "Util.h"

class Game;
class HudPart;

class Hud {

protected:
	Ogre::Real hudWidth;
	Ogre::Real hudHeight;

	Ogre::Real scale;
	Ogre::Real scaleWidth;
	Ogre::Real scaleHeight;

	HudComponents hudComponent;
	
	Ogre::OverlayContainer* hudAreas[numHudAreas];
	Ogre::Overlay* hudOverlays[numHudAreas];
	Ogre::Overlay* hudOverlay3D;
	std::pair<int, int> areaOffsets[numHudAreas];

	std::vector<HudPart*> hudparts;
	bool active;

public:
	Hud();
	~Hud();

	void loadHud();
	void activateHud(bool toggle);

	static Ogre::MaterialPtr createOverlayMaterial(const std::string& name,
		Ogre::TextureUnitState::TextureAddressingMode textureAddress = Ogre::TextureUnitState::TAM_CLAMP,
		std::string textureName = std::string(""));

    Ogre::Real getHudAreaOriginX(HudArea hudArea);
    Ogre::Real getHudAreaOriginY(HudArea hudArea);

	void addContainer(HudArea hudArea, Ogre::OverlayContainer* container);
	void addElement(Ogre::SceneNode* sceneNode);

	HudComponents getHudComponent() const { return hudComponent; }

	void update(Ogre::Real dt);
};

#endif