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

#pragma region SplashScreen while loading
	mSplashSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "SplashScreen");
	mSplashSceneMgr->createCamera(CAMERA_NAME);
	createSplashScreen();
	mSceneMgr = mSplashSceneMgr;
	mCamera = mSceneMgr->getCamera(CAMERA_NAME);
#pragma endregion

#pragma region Creating viewPort
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);

	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));
#pragma endregion

#pragma region Creating sceneManager
	mIntroSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, "Introduction");
#pragma endregion

#pragma region Creating camera
	mIntroSceneMgr->createCamera(CAMERA_NAME);
#pragma endregion

#pragma region Creating scene
	createIntroScene();
#pragma endregion

	loadScene(mIntroSceneMgr);
	setupViewport(mSceneMgr);

#pragma region Initialising OIS
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem(pl);

	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));
	//mJoystick = static_cast<OIS::JoyStick*>(mInputManager->createInputObject(OIS::OISJoyStick, false));

	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);
#pragma endregion

	//----- Set initial mouse clipping size
	windowResized(mWindow);

	//----- Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mRoot->addFrameListener(this);

	mRoot->startRendering();

	return true;
}

void BombermanApplication::loadScene(Ogre::SceneManager * loadScene)
{
	mSceneMgr = loadScene;
}

bool BombermanApplication::keyPressed(const OIS::KeyEvent & arg)
{
	if (arg.key == OIS::KC_V)
	{
		loadScene(mSplashSceneMgr);
		setupViewport(mSceneMgr);
	}
	if (arg.key == OIS::KC_B)
	{
		loadScene(mIntroSceneMgr);
		setupViewport(mSceneMgr);
	}

	return true;
}

bool BombermanApplication::keyReleased(const OIS::KeyEvent & arg)
{
	return true;
}

bool BombermanApplication::mouseMoved(const OIS::MouseEvent & arg)
{
	return true;
}

bool BombermanApplication::mousePressed(const OIS::MouseEvent & arg, OIS::MouseButtonID id)
{
	return true;
}

bool BombermanApplication::mouseReleased(const OIS::MouseEvent & arg, OIS::MouseButtonID id)
{
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

void BombermanApplication::createIntroScene()
{
	mCamera = mIntroSceneMgr->getCamera(CAMERA_NAME);
	mCamera->setPosition(0, 0, 80);
	mCamera->lookAt(0, 0, -300);
	mCamera->setNearClipDistance(5);

	Ogre::Entity* ogreEntity = mIntroSceneMgr->createEntity("Legoblock.mesh");

	Ogre::SceneNode* ogreNode = mIntroSceneMgr->getRootSceneNode()->createChildSceneNode();
	ogreNode->attachObject(ogreEntity);

	mIntroSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

	Ogre::Light* light = mIntroSceneMgr->createLight("MainLight");
	light->setPosition(20, 80, 50);
}

void BombermanApplication::createSplashScreen()
{
	// creation image splash screen
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("SplashScreen", "General");
	material->getTechnique(0)->getPass(0)->createTextureUnitState("splash_screen.dds");
	material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
	material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
	//creation rect
	rect = new Ogre::Rectangle2D(true);
	rect->setCorners(-1.0, 1.0, 1.0, -1.0);
	rect->setMaterial("SplashScreen");
	// priorité chargement
	rect->setRenderQueueGroup(Ogre::RenderQueueGroupID::RENDER_QUEUE_BACKGROUND);
	// stay visible
	Ogre::AxisAlignedBox aabInf;
	aabInf.setInfinite();
	rect->setBoundingBox(aabInf);
	//
	Ogre::SceneNode* node = mSplashSceneMgr->getRootSceneNode()->createChildSceneNode("SplashScreen");
	node->attachObject(rect);
	mSplashSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
}

void BombermanApplication::setupViewport(Ogre::SceneManager * curr)
{
	mWindow->removeAllViewports();

	Ogre::Camera *cam = curr->getCamera(CAMERA_NAME);
	Ogre::Viewport* vp = mWindow->addViewport(cam);

	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	cam->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
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
