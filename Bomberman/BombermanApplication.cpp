/*
-----------------------------------------------------------------------------
Filename:    BombermanApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
	  |___/
Tutorial Framework (for Ogre 1.9)
http://www.ogre3d.org/wiki/
-----------------------------------------------------------------------------
*/

#include "BombermanApplication.h"

//---------------------------------------------------------------------------
BombermanApplication::BombermanApplication(void)
{
}
//---------------------------------------------------------------------------
BombermanApplication::~BombermanApplication(void)
{
}

//---------------------------------------------------------------------------
void BombermanApplication::createScene(void)
{
	// Create your scene here :)
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	Ogre::Entity* ogreEntity = mSceneMgr->createEntity("models/penguin.mesh");
	Ogre::SceneNode* ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode->attachObject(ogreEntity);
	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(20, 80, 50);
}
//---------------------------------------------------------------------------

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#ifdef __cplusplus
extern "C" {
#endif

	INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
	{
		// Create application object
		BombermanApplication app;

		try
		{
			app.go();
		}
		catch(Ogre::Exception& e)
		{
			MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}

		return 0;
	}

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
