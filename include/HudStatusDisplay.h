#ifndef HUD_STATUS_DISPLAY_H
#define HUD_STATUS_DISPLAY_H

#include "HudPart.h"

class HudStatusDisplay : public HudPart {

public:
	HudStatusDisplay(HudParts& hudPart);
	~HudStatusDisplay();

	void update(Ogre::Real dt);
};

#endif