#ifndef HUD_PART_H
#define HUD_PART_H

#include "Util.h"
#include "HudDesign.h"


#include <utility>

class HudPart {

protected:
	static unsigned int id;

	std::pair<int, int> position;
	std::pair<int, int> size;

	Ogre::OverlayContainer* container;

public:
	HudPart(HudParts& hudparts);
	virtual ~HudPart();

	//Ogre::OverlayElement* createPanel(const std::string& id, const std::string& materialName,
	//	int x, int y,  int width, int height, Ogre::OverlayContainer* container);
    
	//Ogre::OverlayElement* createTextArea(const std::string& id, const std::string& text,
    //    int fontSize, Ogre::ColourValue color, int x, int y,  int width, int height,
    //    Ogre::OverlayContainer* container);

	virtual void update(Ogre::Real dt) = 0;
	static std::string getID();
};

#endif