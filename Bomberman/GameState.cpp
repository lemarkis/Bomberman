//|||||||||||||||||||||||||||||||||||||||||||||||

#include "GameState.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

GameState::GameState()
{
    m_MoveSpeed			= 0.1f;
    m_RotateSpeed		= 0.3f;

    m_bQuit             = false;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::enter()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering GameState...");

    m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(Ogre::ST_GENERIC, "GameSceneMgr");
    m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

    m_pSceneMgr->addRenderQueueListener(OgreFramework::getSingletonPtr()->m_pOverlaySystem);

    m_pCamera = m_pSceneMgr->createCamera("GameCamera");
    m_pCamera->setPosition(Ogre::Vector3(5, 60, 60));
    m_pCamera->lookAt(Ogre::Vector3(5, 20, 0));
    m_pCamera->setNearClipDistance(2);

    m_pCamera->setAspectRatio(Ogre::Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) /
        Ogre::Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));

    OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

	m_Factory = new AppFactory(m_pSceneMgr);

    buildGUI();

    createScene();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::pause()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Pausing GameState...");

    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::resume()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Resuming GameState...");

    buildGUI();

    OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);
    m_bQuit = false;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::exit()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving GameState...");

    m_pSceneMgr->destroyCamera(m_pCamera);

    if(m_pSceneMgr)
        OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::createScene()
{
	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3));
	m_pSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	m_Factory->createGround("Plaque1", Ogre::Vector3(0, -.17, 0));

	m_Factory->createBomber("Player1", Ogre::Vector3::ZERO, false);

	m_Factory->createBlock("Static1", Ogre::Vector3(2, 0, 0), false);

	Ogre::Light *spotlight = m_pSceneMgr->createLight("Spotlight");
	spotlight->setDiffuseColour(.7, .7, .7);
	spotlight->setSpecularColour(.3, .7, .7);
	spotlight->setDirection(0, -1, 0);
	spotlight->setPosition(0, 100, 0);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	m_Factory->injectKeyPressed(keyEventRef);

    if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
        pushAppState(findByName("PauseState"));
        return true;
    }

    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	m_Factory->injectKeyReleased(keyEventRef);

    OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::mouseMoved(const OIS::MouseEvent &evt)
{
	m_Factory->injectMouseMoved(evt);

	m_pCamera->yaw(Ogre::Degree(evt.state.X.rel * -0.1f));
	m_pCamera->pitch(Ogre::Degree(evt.state.Y.rel * -0.1f));

	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	m_Factory->injectMousePressed(evt, id);

    //if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) return true;

    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	m_Factory->injectMouseReleased(evt, id);

    //if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseUp(evt, id)) return true;

    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::moveCamera()
{
    m_pCamera->moveRelative(m_TranslateVector * .5);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::getInput()
{
	OIS::Keyboard *lKeyboard = OgreFramework::getSingletonPtr()->m_pKeyboard;
	
	//Camera
	if (lKeyboard->isKeyDown(OIS::KC_A))
		m_TranslateVector.x = -m_MoveScale;

	if (lKeyboard->isKeyDown(OIS::KC_D))
		m_TranslateVector.x = m_MoveScale;

	if (lKeyboard->isKeyDown(OIS::KC_W))
		m_TranslateVector.z = -m_MoveScale;

	if (lKeyboard->isKeyDown(OIS::KC_S))
		m_TranslateVector.z = m_MoveScale;

	if (lKeyboard->isKeyDown(OIS::KC_Q))
		m_TranslateVector.y = -m_MoveScale;

	if (lKeyboard->isKeyDown(OIS::KC_E))
		m_TranslateVector.y = m_MoveScale;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::update(double timeSinceLastFrame)
{
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    OgreFramework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);

    if(m_bQuit == true)
    {
        popAppState();
        return;
    }

	m_Factory->injectUpdate(timeSinceLastFrame);

    m_MoveScale = m_MoveSpeed   * timeSinceLastFrame;
    m_RotScale  = m_RotateSpeed * timeSinceLastFrame;

    m_TranslateVector = Ogre::Vector3::ZERO;

    getInput();
    moveCamera();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::buildGUI()
{
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createLabel(OgreBites::TL_TOP, "GameLbl", "Game mode", 250);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->hideCursor();
}

//|||||||||||||||||||||||||||||||||||||||||||||||