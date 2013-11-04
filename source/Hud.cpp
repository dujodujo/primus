#include "Hud.h"

Hud::Hud() : 
  active(false),
  scale(1.f),
  scaleWidth(1.f),
  scaleHeight(1.f) {
	hudWidth = Ogre::Real(640);
	hudHeight = Ogre::Real(480);
}

Hud::~Hud() {
	Ogre::OverlayManager* om = &Ogre::OverlayManager::getSingleton();
	om->destroyAllOverlayElements();
	om->destroyAll();

	Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup("hud");
}

void Hud::loadHud() {
	Parser::init();
	Game::parser = Parser::instance();

	std::string hudName = 
		"C:/Users/dujo/Documents/Visual Studio 2010/Projects/Omecha/Omecha/data/hud/hud";
	if(Parser::getHudDesign(hudName, hudComponent) == false) {
		Game::game->quitGame();
	}
	
	Ogre::OverlayManager* overlayManager = &Ogre::OverlayManager::getSingleton();
	for(unsigned int i = 0; i < numHudAreas; i++) {
		hudOverlays[i] = overlayManager->create(hudAreaNames[i]);
		createOverlayMaterial(hudAreaNames[i]);

		//create the top container
        hudAreas[i] = (static_cast<Ogre::OverlayContainer*>
            (overlayManager->createOverlayElement("Panel", hudAreaNames[i] + "_area")));
		//apply meterial with texture from design
        hudAreas[i]->setMaterialName(hudAreaNames[i]);
		//set size and position
        hudAreas[i]->setMetricsMode(Ogre::GMM_PIXELS);

        hudAreas[i]->setDimensions(hudComponent.sizes[i].first, hudComponent.sizes[i].second);
		hudAreas[i]->setPosition(hudComponent.positions[i].first, hudComponent.positions[i].second);
		
		//add to the overlay
        hudOverlays[i]->add2D(hudAreas[i]);
        hudOverlays[i]->setZOrder(400);
	}

	for(unsigned int i = 0; i < hudComponent.parts.size(); ++i) {
		if(hudComponent.parts[i].area == HudArea::hud_status) {
			hudparts.push_back(new HudStatusDisplay(hudComponent.parts[i]));
		} else if(hudComponent.parts[i].area == HudArea::hud_heat) {
			//hudParts.push_back(new HudStatusDisplay(hudComponent.parts[i]));
		} else if(hudComponent.parts[i].area == HudArea::hud_log) {
			//hudParts.push_back(new HudStatusDisplay(hudComponent.parts[i]));
		}
    }
}

void Hud::activateHud(bool toggle) {
	this->active = toggle;
	if(active) {
		for(unsigned int i = 0; i < numHudAreas; i++) {
			hudOverlays[i]->show();
		}
	} else {
		for(unsigned int i = 0; i < numHudAreas; i++) {
			hudOverlays[i]->hide();
		}
	}
}

Ogre::MaterialPtr Hud::createOverlayMaterial(const std::string& name,
  Ogre::TextureUnitState::TextureAddressingMode textureAddress, 
  std::string textureName) {
	Ogre::MaterialPtr material;

	if(textureName.empty()) {
		textureName = name;
	}

	if(Ogre::MaterialManager::getSingleton().resourceExists(name)) {
		material = Ogre::MaterialManager::getSingleton().getByName(name);
	} else {
		//create it
		material = Ogre::MaterialManager::getSingleton().create(name, "hud");
		Ogre::Pass* pass = material->getTechnique(0)->getPass(0);
		pass->createTextureUnitState()->setTextureName(textureName + ".dds");

		//enable alpha blending
        pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
        //crucial bit for the hud - enable clamping by default
        pass->getTextureUnitState(0)->setTextureAddressingMode(textureAddress);
        //get them a bit crisper
        pass->setTextureFiltering(Ogre::TFO_TRILINEAR);
	}
	return material;
}

Ogre::Real Hud::getHudAreaOriginX(HudArea hudArea) {
	switch (hudComponent.positions[hudArea].first) {
	case Position::left:
        return areaOffsets[hudArea].first * scale;
	case Position::center:
		return hudWidth - (hudComponent.sizes[hudArea].first + areaOffsets[hudArea].first) * 0.5 * scale;
    case Position::right:
        return hudWidth - (hudComponent.sizes[hudArea].first + areaOffsets[hudArea].first) * scale;
    default:
        return 0;
    }
}

Ogre::Real Hud::getHudAreaOriginY(HudArea hudArea) {
	switch (hudComponent.positions[hudArea].second) {
	case Position::top:
		return areaOffsets[hudArea].first * scale;
	case Position::center:
        return hudHeight - (hudComponent.sizes[hudArea].second + areaOffsets[hudArea].second) * 0.5 * scale;
	case Position::bottom:
        return hudHeight - (hudComponent.sizes[hudArea].second + areaOffsets[hudArea].second) * scale;
    default:
        return 0;
    }
}

void Hud::addContainer(HudArea hudArea, Ogre::OverlayContainer* container) {
	hudOverlays[hudArea]->add2D(container);
}

void Hud::addElement(Ogre::SceneNode* sceneNode) {
	hudOverlay3D->add3D(sceneNode);
}

void Hud::update(Ogre::Real dt) {
	if(active) {
		for(unsigned int i = 0; i < hudparts.size(); ++i) {
			hudparts.at(i)->update(dt);
		}
	}
}
