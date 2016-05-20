/*
-----------------------------------------------------------------------------
Filename:    BombermanApplication.cpp
-----------------------------------------------------------------------------

blablabla comment;

-----------------------------------------------------------------------------
*/

#include "BombermanApplication.h"


BombermanApplication::BombermanApplication(void)
	: mRoot(0),
	mResourcesCfg(Ogre::StringUtil::BLANK),
	mPluginsCfg(Ogre::StringUtil::BLANK)
{
}

BombermanApplication::~BombermanApplication(void)
{
	//Remove ourself as a Window listener
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);
	delete mRoot;
}

bool BombermanApplication::go()
{
#ifdef _DEBUG
	mResourcesCfg = "my_resources_d.cfg";
	mPluginsCfg = "plugins_d.cfg";
#else
	mResourcesCfg = "my_resources.cfg";
	mPluginsCfg = "plugins.cfg";
#endif

#pragma region Creating root object
	mRoot = new Ogre::Root(mPluginsCfg);
#pragma endregion

#pragma region Setting up resources
	Ogre::String name, locType;
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);
	Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();
	while (secIt.hasMoreElements())
	{
		Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator it;
		for (it = settings->begin(); it != settings->end(); ++it)
		{
			locType = it->first;
			name = it->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
		}
	}
#pragma endregion

#pragma region Configuring renderSystem
	if (!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
		return false;
#pragma endregion

#pragma region Creating renderWindow
	mWindow = mRoot->initialise(true, "Bomberman Lego");
#pragma endregion

#pragma region Initialising resources
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
#pragma endregion

#pragma region Creating sceneManager
	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
#pragma endregion

#pragma region Creating camera
	mCamera = mSceneMgr->createCamera("MainCam");

	mCamera->setPosition(0, 0, 80);
	mCamera->lookAt(0, 0, -300);
	mCamera->setNearClipDistance(5);
#pragma endregion

#pragma region Creating viewPort
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);

	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));
#pragma endregion

#pragma region Creating scene
	createScene();
#pragma endregion

#pragma region Initialising OIS
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem(pl);

	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, false));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, false));
	//mJoystick = static_cast<OIS::JoyStick*>(mInputManager->createInputObject(OIS::OISJoyStick, false));
#pragma endregion

	//----- Set initial mouse clipping size
	windowResized(mWindow);

	//----- Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mRoot->addFrameListener(this);

	mRoot->startRendering();

	return true;
}

void BombermanApplication::windowResized(Ogre::RenderWindow* rw)
{
	//Adjust mouse clipping area
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void BombermanApplication::windowClosed(Ogre::RenderWindow* rw)
{
	//Unattach OIS before window shutdown (very important under Linux)
	//Only close for window that created OIS (the main window in these demos)
	if (rw == mWindow)
	{
		if (mInputManager)
		{
			mInputManager->destroyInputObject(mMouse);
			mInputManager->destroyInputObject(mKeyboard);

			OIS::InputManager::destroyInputSystem(mInputManager);
			mInputManager = 0;
		}
	}
}

bool BombermanApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if (mWindow->isClosed())
		return false;

	//Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();

	if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
		return false;

	return true;
}

void BombermanApplication::createScene()
{
	Ogre::Entity* ogreEntity = mSceneMgr->createEntity("Legoblock.mesh");

	Ogre::SceneNode* ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode->attachObject(ogreEntity);

	mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

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
