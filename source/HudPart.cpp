#include "Game.h"
#include "HudPart.h"

unsigned int HudPart::id = 0;

HudPart::HudPart(HudParts& hudparts) {
	position = hudparts.position;
	size = hudparts.size;
	
	container = static_cast<Ogre::OverlayContainer*>
		(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", 
		hudparts.name + HudPart::getID()));

	Hud::createOverlayMaterial(hudparts.name);
	container->setMaterialName(hudparts.name);

	container->setMetricsMode(Ogre::GMM_PIXELS);
	container->setPosition(position.first, position.second);
	container->setDimensions(size.first, size.second);
	
	Game::hud->addContainer(hudparts.area, container);
}

HudPart::~HudPart() {}

/*
Ogre::OverlayElement* createPanel(const std::string& id, const std::string& materialName,
  int x, int y, int width, int height, Ogre::OverlayContainer* container) {
	Ogre::OverlayElement* element = 
		Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", id);

	Hud::createOverlayMaterial(materialName);
	element->setMaterialName(materialName);
	element->setMetricsMode(Ogre::GMM_PIXELS);
	element->setPosition(x, y);
	element->setDimensions(width, height);

	container->addChild(element);
	return element;
}

/*
Ogre::OverlayElement* createTextArea(const std::string& id, const std::string& text,
  int fontSize, Ogre::ColourValue color, int x, int y,  int width, int height,
  Ogre::OverlayContainer* container) {
	Ogre::OverlayElement* element = 
		Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", id);

	//dimensions
	element->setMetricsMode(Ogre::GMM_PIXELS);
	element->setPosition(x, y);
	element->setDimensions(width, height);

	//elements
	element->setParameter("font_name", Game::hud->getHudComponent().fontName);
	element->setParameter("char_height", toString(fontSize));
	element->setColour(color);
	element->setCaption(text);

	container->addChild(element);
	return element;
}
*/

std::string HudPart::getID() {
	std::string idString;
	std::stringstream stream;
	stream << std::setfill('0') << std::setw(3) << ++id;
	stream >> idString;
	return idString;
}