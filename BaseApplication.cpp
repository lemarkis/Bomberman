/*
-----------------------------------------------------------------------------
Filename:    BaseApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
	  |___/
Tutorial Framework (for Ogre 2.0)
http://www.ogre3d.org/wiki/
-----------------------------------------------------------------------------
*/

#include "BaseApplication.h"
#include <Compositor/OgreCompositorManager2.h>

//---------------------------------------------------------------------------
BaseApplication::BaseApplication(void)
	: mRoot(0),
	mCamera(0),
	mSceneMgr(0),
	mWindow(0),
    mResourcesCfg(Ogre::BLANKSTRING),
	mPluginsCfg(Ogre::BLANKSTRING),
    mCameraMan(0),
	mShutDown(false),
	mInputManager(0),
	mMouse(0),
	mKeyboard(0)
{
	m_ResourcePath = "";
}

//---------------------------------------------------------------------------
BaseApplication::~BaseApplication(void)
{
    if (mCameraMan) delete mCameraMan;

	// Remove ourself as a Window listener
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);
	delete mRoot;
}

//---------------------------------------------------------------------------
bool BaseApplication::configure(void)
{
	// Show the configuration dialog and initialise the system.
	// You can skip this and use root.restoreConfig() to load configuration
	// settings if you were sure there are valid ones saved in ogre.cfg.
	if(mRoot->showConfigDialog())
	{
		// If returned true, user clicked OK so initialise.
		// Here we choose to let the system create a default rendering window by passing 'true'.
		mWindow = mRoot->initialise(true, "Bomberman Render Window");

		return true;
	}
	else
	{
		return false;
	}
}
//---------------------------------------------------------------------------
void BaseApplication::chooseSceneManager(void)
{
	// Get the SceneManager, in this case a generic one
	const size_t numThreads = std::max<int>(1, Ogre::PlatformInformation::getNumLogicalCores());
	Ogre::InstancingThreadedCullingMethod threadedCullingMethod = Ogre::INSTANCING_CULLING_SINGLETHREAD;
	if (numThreads > 1) threadedCullingMethod = Ogre::INSTANCING_CULLING_THREADED;
	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC, numThreads, threadedCullingMethod);
}
//---------------------------------------------------------------------------
void BaseApplication::createCamera(void)
{
	// Create the camera
	mCamera = mSceneMgr->createCamera("PlayerCam");

	// Position it at 500 in Z direction
	mCamera->setPosition(Ogre::Vector3(0,0,80));
	// Look back along -Z
	mCamera->lookAt(Ogre::Vector3(0,0,-300));
	mCamera->setNearClipDistance(5);

	mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // Create a default camera controller
}
//---------------------------------------------------------------------------
void BaseApplication::createFrameListener(void)
{
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

	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);

	// Set initial mouse clipping size
	windowResized(mWindow);

	// Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mRoot->addFrameListener(this);
}
//---------------------------------------------------------------------------
void BaseApplication::destroyScene(void)
{
}
//---------------------------------------------------------------------------
void BaseApplication::createCompositor(void)
{
	// Get compositor manager
	Ogre::CompositorManager2* compMan = mRoot->getCompositorManager2();

	// Create default workspace
	const Ogre::String workspaceName = "default scene workspace";
	const Ogre::IdString workspaceNameHash = workspaceName;
	compMan->createBasicWorkspaceDef(workspaceName, Ogre::ColourValue::Black);
	compMan->addWorkspace(mSceneMgr, mWindow, mCamera, workspaceNameHash, true);
}
//---------------------------------------------------------------------------
void BaseApplication::setupResources(void)
{
	// Load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}
}
//---------------------------------------------------------------------------
void BaseApplication::createResourceListener(void)
{
}
//---------------------------------------------------------------------------
void BaseApplication::loadResources(void)
{
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
//---------------------------------------------------------------------------
void BaseApplication::go(void)
{
#ifdef _DEBUG
	mResourcesCfg = m_ResourcePath + "resources_d.cfg";
	mPluginsCfg = m_ResourcePath + "plugins_d.cfg";
#else
	mResourcesCfg = m_ResourcePath + "resources.cfg";
	mPluginsCfg = m_ResourcePath + "plugins.cfg";
#endif

	if (!setup())
		return;

	mRoot->startRendering();

	// Clean up
	destroyScene();
}
//---------------------------------------------------------------------------
bool BaseApplication::setup(void)
{
	mRoot = new Ogre::Root(mPluginsCfg);

	setupResources();

	bool carryOn = configure();
	if (!carryOn) return false;

	chooseSceneManager();
	createCamera();

    createCompositor();

	// Set default mipmap level (NB some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	// Create any resource listeners (for loading screens)
	createResourceListener();
	// Load resources
	loadResources();

	// Create the scene
	createScene();

	createFrameListener();

	return true;
};
//---------------------------------------------------------------------------
bool BaseApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if(mWindow->isClosed())
		return false;

	if(mShutDown)
		return false;

	// Need to capture/update each device
	mKeyboard->capture();
	mMouse->capture();

    return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::keyPressed( const OIS::KeyEvent &arg )
{
    if (arg.key == OIS::KC_R)   // cycle polygon rendering mode
	{
		Ogre::PolygonMode pm;

		switch (mCamera->getPolygonModeOverrideable())
		{
		case Ogre::PM_SOLID:
			pm = Ogre::PM_WIREFRAME;
			break;
		case Ogre::PM_WIREFRAME:
			pm = Ogre::PM_POINTS;
			break;
		default:
			pm = Ogre::PM_SOLID;
		}

		mCamera->setPolygonModeOverrideable(pm);
	}
	else if (arg.key == OIS::KC_F5)   // refresh all textures
	{
		Ogre::TextureManager::getSingleton().reloadAll();
	}
	else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
	{
		mWindow->writeContentsToTimestampedFile("screenshot", ".png");
	}
	else if (arg.key == OIS::KC_ESCAPE)
	{
		mShutDown = true;
	}

	mCameraMan->injectKeyDown(arg);
	return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::keyReleased(const OIS::KeyEvent &arg)
{
	mCameraMan->injectKeyUp(arg);
	return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::mouseMoved(const OIS::MouseEvent &arg)
{
    mCameraMan->injectPointerMove(arg);
	return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    mCameraMan->injectPointerDown(arg, id);
	return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
    mCameraMan->injectPointerUp(arg, id);
	return true;
}
//---------------------------------------------------------------------------
// Adjust mouse clipping area
void BaseApplication::windowResized(Ogre::RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}
//---------------------------------------------------------------------------
// Unattach OIS before window shutdown (very important under Linux)
void BaseApplication::windowClosed(Ogre::RenderWindow* rw)
{
	// Only close for window that created OIS (the main window in these demos)
	if(rw == mWindow)
	{
		if(mInputManager)
		{
			mInputManager->destroyInputObject(mMouse);
			mInputManager->destroyInputObject(mKeyboard);

			OIS::InputManager::destroyInputSystem(mInputManager);
			mInputManager = 0;
		}
	}
}
//---------------------------------------------------------------------------
