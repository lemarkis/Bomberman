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

//---------------------------------------------------------------------------

class BombermanApplication : public Ogre::WindowEventListener, public Ogre::FrameListener
{
public:
	BombermanApplication(void);
	virtual ~BombermanApplication(void);

	bool go();
	void createScene();

protected:
	Ogre::Root* mRoot;
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;
	Ogre::RenderWindow* mWindow;
	Ogre::SceneManager* mSceneMgr;
	Ogre::SceneManager* mPrimarySceneMgr;
	Ogre::SceneManager* mSecondarySceneMgr;
	Ogre::Camera* mCamera;
	Ogre::Rectangle2D *rect;

	OIS::InputManager* mInputManager;
	OIS::Mouse* mMouse;
	OIS::Keyboard* mKeyboard;
	//OIS::JoyStick* mJoystick;

	virtual void windowResized(Ogre::RenderWindow* rw);
	virtual void windowClosed(Ogre::RenderWindow* rw);


	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

private:
	void createSplashScreen();
};

//---------------------------------------------------------------------------

#endif // #ifndef __BombermanApplication_h_

//---------------------------------------------------------------------------
