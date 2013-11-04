#ifndef ELOADING_BAR_H
#define ELOADING_BAR_H

#include "Game.h"

class ELoadingBar : public Ogre::ResourceGroupListener {

private:
	Ogre::Overlay* loadingOverlay;
	Ogre::Real initProportion;
	unsigned short numsGroupsInit;
	unsigned short numsGroupsLoad;
	Ogre::Real progressBarMaxSize;
	Ogre::Real progressBarScriptSize;
	Ogre::Real progressBarIncrement;
	
	Ogre::OverlayElement* loadingBarElement;
	Ogre::OverlayElement* loadingDescriptionElement;
	Ogre::OverlayElement* loadingCommentElement;

public:
	ELoadingBar();
	virtual ~ELoadingBar();

	virtual void start(Ogre::RenderWindow* window);
	
	virtual void finish(void);

	void resourceGroupScriptingStarted(const Ogre::String& groupName, size_t scriptCount);
	
	void scriptParseStarted(const Ogre::String& scriptName, bool &skipThisScript);
	void scriptParseEnded(const Ogre::String& scriptName, bool skipped);
	
	void resourceGroupScriptingEnded(const Ogre::String& groupName);
	void resourceGroupLoadStarted(const Ogre::String& groupName, size_t resourceCount);
	
	void resourceLoadStarted(const Ogre::ResourcePtr& resource);
	void resourceLoadEnded(void);

	void worldGeometryStageStarted(const Ogre::String& description);
	void worldGeometryStageEnded(void);
	void resourceGroupLoadEnded(const Ogre::String& groupName);
};

#endif