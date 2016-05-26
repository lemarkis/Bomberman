
#include "SplashScreenState.hpp"

using namespace Ogre;

SplashScreenState::SplashScreenState()
{
	m_bQuit = false;
	m_FrameEvent = Ogre::FrameEvent();
}

void SplashScreenState::enter()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering SplashScreenState...");

	m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "SplashScreenSceneMgr");
	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

	m_pSceneMgr->addRenderQueueListener(OgreFramework::getSingletonPtr()->m_pOverlaySystem);

	m_pCamera = m_pSceneMgr->createCamera("SplashScreenCam");
	m_pCamera->setPosition(Vector3(0, 25, -50));
	m_pCamera->lookAt(Vector3(0, 0, 0));
	m_pCamera->setNearClipDistance(1);

	m_pCamera->setAspectRatio(Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) /
		Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));

	OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

	OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
	OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_BOTTOM, "EnterBtn", "Press Enter...", 250);

	createScene();
}

void SplashScreenState::createScene()
{
	// creation image splash screen
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("SplashScreen", "General");
	material->getTechnique(0)->getPass(0)->createTextureUnitState("splash_screen.dds");
	material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
	material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
	//creation rect
	Ogre::Rectangle2D *rect = new Ogre::Rectangle2D(true);
	rect->setCorners(-1.0, 1.0, 1.0, -1.0);
	rect->setMaterial("SplashScreen");
	// priorité chargement
	rect->setRenderQueueGroup(Ogre::RenderQueueGroupID::RENDER_QUEUE_BACKGROUND);
	// stay visible
	Ogre::AxisAlignedBox aabInf;
	aabInf.setInfinite();
	rect->setBoundingBox(aabInf);
	//
	Ogre::SceneNode* node = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("SplashScreen");
	node->attachObject(rect);
	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
}

void SplashScreenState::exit()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving SplashScreenState...");

	m_pSceneMgr->destroyCamera(m_pCamera);
	if (m_pSceneMgr)
		OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);

	OgreFramework::getSingletonPtr()->m_pTrayMgr->clearAllTrays();
	OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
	OgreFramework::getSingletonPtr()->m_pTrayMgr->setListener(0);
}

bool SplashScreenState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		m_bQuit = true;
		return true;
	}

	if (OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_RETURN))
	{
		changeAppState(findByName("MenuState"));
		return true;
	}

	OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);
	return true;
}

bool SplashScreenState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	OgreFramework::getSingletonPtr()->keyReleased(keyEventRef);
	return true;
}

bool SplashScreenState::mouseMoved(const OIS::MouseEvent &evt)
{
	if (OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseMove(evt)) return true;
	return true;
}

bool SplashScreenState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	if (OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) return true;
	return true;
}

bool SplashScreenState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	if (OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseUp(evt, id)) return true;
	return true;
}

void SplashScreenState::update(double timeSinceLastFrame)
{
	m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
	OgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);

	if (m_bQuit == true)
	{
		shutdown();
		return;
	}
}

void SplashScreenState::buttonHit(OgreBites::Button *button)
{
	if (button->getName() == "ExitBtn")
		m_bQuit = true;
	else if (button->getName() == "EnterBtn")
		changeAppState(findByName("GameState"));
}
