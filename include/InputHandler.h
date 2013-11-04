#ifndef OIS_INPUT_H
#define OIS_INPUT_H


#ifdef PLATFORM_WIN32
    #include <OISEvents.h>
    #include <OISInputManager.h>
    #include <OISMouse.h>
    #include <OISKeyboard.h>
#else
    #include <OIS/OISEvents.h>
    #include <OIS/OISInputManager.h>
    #include <OIS/OISMouse.h>
    #include <OIS/OISKeyboard.h>
#endif


#include "Util.h"
#include "Game.h"

class GameController;

class InputHandler : public OIS::KeyListener,
                     public OIS::MouseListener,
                     public Ogre::WindowEventListener {

private:
    OIS::InputManager* inputManager;
    OIS::Mouse* mouse;
    OIS::Keyboard* keyboard;

    GameController* gameController;

    Camera* camera;
    Ogre::RaySceneQuery* raySceneQuery;
    Ogre::Ray* ray;
    Ogre::Real pointerX;
	Ogre::Real pointerY;
	Ogre::Real cameraDistance;

    Ogre::SceneNode* centerNode;

    unsigned int screenWidth;
    unsigned int screenHeight;

public:
    InputHandler();
    ~InputHandler();

    //main loop
    void update();

    //called by Ogre whe the window is resized
    void windowResized(Ogre::RenderWindow* renderWindow);
	void resize();

    //called by OIS on input
    bool mouseMoved(const OIS::MouseEvent& evt);
    bool mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID);
    bool mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID);
    bool keyPressed(const OIS::KeyEvent& evt);
    bool keyReleased(const OIS::KeyEvent& evt);

    //bind the controller which recevies local input
    void setController(GameController* controller);

    //translate mouse position to 3D coords in the world
    void updateMousePointer();
};

#endif // OIS_INPUT_H
