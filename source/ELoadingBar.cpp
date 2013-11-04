#include "ELoadingBar.h"

ELoadingBar::ELoadingBar() {}

ELoadingBar::~ELoadingBar() {}

void ELoadingBar::start(Ogre::RenderWindow* window) {
	numsGroupsInit = 1;
	numsGroupsLoad = 1;
	initProportion = 0.7f;
	
	
	/*
	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
	loadingOverlay = (Ogre::Overlay*) overlayManager.getByName("Core/LoadOverlay");

	loadingOverlay->show();

	loadingBarElement = overlayManager.getOverlayElement("Core/LoadPanel/Bar/Progress");
	loadingCommentElement = overlayManager.getOverlayElement("Core/LoadPanel/Comment");
	loadingDescriptionElement = overlayManager.getOverlayElement("Core/LoadPanel/Description");

	Ogre::OverlayElement* barContainer = overlayManager.getOverlayElement("Core/LoadPanel/Bar");
	progressBarMaxSize = barContainer->getWidth();
	loadingBarElement->setWidth(0);

	Ogre::ResourceGroupManager::getSingleton().addResourceGroupListener(this);
	*/
}

void ELoadingBar::finish(void) {
	loadingOverlay->hide();
	Ogre::ResourceGroupManager::getSingleton().removeResourceGroupListener(this);
}

void ELoadingBar::resourceGroupScriptingStarted(const Ogre::String& groupName, size_t scriptCount) {
	progressBarIncrement = progressBarMaxSize * initProportion / (Ogre::Real)scriptCount;
	progressBarIncrement /= numsGroupsInit;
	loadingDescriptionElement->setCaption("Parsing scripts...");
	Game::renderWindow->update();
}
	
void ELoadingBar::scriptParseStarted(const Ogre::String& scriptName, bool &skipThisScript) {
	loadingCommentElement->setCaption(scriptName);
	Game::renderWindow->update();
}

void ELoadingBar::scriptParseEnded(const Ogre::String& scriptName, bool skipped) {
	loadingBarElement->setWidth(
	loadingBarElement->getWidth() + progressBarIncrement);
	Game::renderWindow->update();
}
	
void ELoadingBar::resourceGroupScriptingEnded(const Ogre::String& groupName) {}

void ELoadingBar::resourceGroupLoadStarted(const Ogre::String& groupName, size_t resourceCount) {
	progressBarIncrement = progressBarMaxSize * (1-initProportion) / (Ogre::Real)resourceCount;
	progressBarIncrement /= numsGroupsLoad;
	loadingDescriptionElement->setCaption("Loading resources...");	
	Game::renderWindow->update();
}
	
void ELoadingBar::resourceLoadStarted(const Ogre::ResourcePtr& resource) {
	loadingCommentElement->setCaption(resource->getName());
	Game::renderWindow->update();
}

void ELoadingBar::resourceLoadEnded(void) {}

void ELoadingBar::worldGeometryStageStarted(const Ogre::String& description) {
	loadingCommentElement->setCaption(description);
	Game::renderWindow->update();
}
	
void ELoadingBar::worldGeometryStageEnded(void) {
	loadingBarElement->setWidth(loadingBarElement->getWidth() + progressBarIncrement);
	Game::renderWindow->update();
}
	
void ELoadingBar::resourceGroupLoadEnded(const Ogre::String& groupName) {}