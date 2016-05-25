/*
-----------------------------------------------------------------------------
Filename:    BombermanApplication.h
-----------------------------------------------------------------------------

blablabl comment;

-----------------------------------------------------------------------------
*/

#ifndef __BombermanApplication_h_
#define __BombermanApplication_h_

//#include "BaseApplication.h"

#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
//#include <OISJoyStick.h>

#define CAMERA_NAME "SceneCamera"

//---------------------------------------------------------------------------

class BombermanApplication : public Ogre::WindowEventListener, public Ogre::FrameListener, public OIS::KeyListener, public OIS::MouseListener
{
public:
	BombermanApplication(void);
	virtual ~BombermanApplication(void);

	bool go();

protected:
	Ogre::Root* mRoot;
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;
	Ogre::SceneManager* mSplashSceneMgr;
	Ogre::SceneManager* mIntroSceneMgr;
	Ogre::Camera* mCamera;
	Ogre::Rectangle2D *rect;

	OIS::InputManager* mInputManager;
	OIS::Mouse* mMouse;
	OIS::Keyboard* mKeyboard;
	//OIS::JoyStick* mJoystick;

	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	virtual void windowResized(Ogre::RenderWindow* rw);
	virtual void windowClosed(Ogre::RenderWindow* rw);

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

private:
	void createIntroScene();
	void createSplashScreen();
	void setupViewport(Ogre::SceneManager *curr);
	void loadScene(Ogre::SceneManager* loadScene);
};

//---------------------------------------------------------------------------

#endif // #ifndef __BombermanApplication_h_

//---------------------------------------------------------------------------
