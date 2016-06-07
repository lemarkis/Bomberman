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
	//Plaques
	m_Factory->createGround("Plaque1", Ogre::Vector3(6.36, -0.32, 6.36));
	m_Factory->createGround("Plaque2", Ogre::Vector3(6.36, -0.32, 19.14));
	m_Factory->createGround("Plaque3", Ogre::Vector3(6.36, -0.32, 31.92));
	m_Factory->createGround("Plaque4", Ogre::Vector3(6.36, -0.32, 44.7));
	m_Factory->createGround("Plaque5", Ogre::Vector3(19.14, -0.32, 6.36));
	m_Factory->createGround("Plaque6", Ogre::Vector3(19.14, -0.32, 19.14));
	m_Factory->createGround("Plaque7", Ogre::Vector3(19.14, -0.32, 31.92));
	m_Factory->createGround("Plaque8", Ogre::Vector3(19.14, -0.32, 44.7));
	m_Factory->createGround("Plaque9", Ogre::Vector3(31.92, -0.32, 6.36));
	m_Factory->createGround("Plaque10", Ogre::Vector3(31.92, -0.32, 19.14));
	m_Factory->createGround("Plaque11", Ogre::Vector3(31.92, -0.32, 31.92));
	m_Factory->createGround("Plaque12", Ogre::Vector3(31.92, -0.32, 44.7));
	m_Factory->createGround("Plaque13", Ogre::Vector3(44.7, -0.32, 6.36));
	m_Factory->createGround("Plaque14", Ogre::Vector3(44.7, -0.32, 19.14));
	m_Factory->createGround("Plaque15", Ogre::Vector3(44.7, -0.32, 31.92));
	m_Factory->createGround("Plaque16", Ogre::Vector3(44.7, -0.32, 44.7));
	//player
	m_Factory->createBomber("Player1", Ogre::Vector3(3.18, 0, 3.18), false);
	// gauche
	m_Factory->createBlock("Static1", Ogre::Vector3(0, 0, 0), false);
	m_Factory->createBlock("Static2", Ogre::Vector3(3.18, 0, 0), false);
	m_Factory->createBlock("Static3", Ogre::Vector3(6.36, 0, 0), false);
	m_Factory->createBlock("Static4", Ogre::Vector3(9.54, 0, 0), false);
	m_Factory->createBlock("Static5", Ogre::Vector3(12.72, 0, 0), false);
	m_Factory->createBlock("Static6", Ogre::Vector3(15.9, 0, 0), false);
	m_Factory->createBlock("Static7", Ogre::Vector3(19.08, 0, 0), false);
	m_Factory->createBlock("Static8", Ogre::Vector3(22.26, 0, 0), false);
	m_Factory->createBlock("Static9", Ogre::Vector3(25.44, 0, 0), false);
	m_Factory->createBlock("Static10", Ogre::Vector3(28.62, 0, 0), false);
	m_Factory->createBlock("Static11", Ogre::Vector3(31.8, 0, 0), false);
	m_Factory->createBlock("Static12", Ogre::Vector3(34.98, 0, 0), false);
	m_Factory->createBlock("Static13", Ogre::Vector3(38.16, 0, 0), false);
	m_Factory->createBlock("Static14", Ogre::Vector3(41.34, 0, 0), false);
	m_Factory->createBlock("Static15", Ogre::Vector3(44.52, 0, 0), false);
	m_Factory->createBlock("Static16", Ogre::Vector3(47.7, 0, 0), false);
	//haut
	m_Factory->createBlock("Static17", Ogre::Vector3(0, 0, 3.18), false);
	m_Factory->createBlock("Static18", Ogre::Vector3(0, 0, 6.36), false);
	m_Factory->createBlock("Static19", Ogre::Vector3(0, 0, 9.54), false);
	m_Factory->createBlock("Static20", Ogre::Vector3(0, 0, 12.72), false);
	m_Factory->createBlock("Static21", Ogre::Vector3(0, 0, 15.9), false);
	m_Factory->createBlock("Static22", Ogre::Vector3(0, 0, 19.08), false);
	m_Factory->createBlock("Static23", Ogre::Vector3(0, 0, 22.26), false);
	m_Factory->createBlock("Static24", Ogre::Vector3(0, 0, 25.44), false);
	m_Factory->createBlock("Static25", Ogre::Vector3(0, 0, 28.62), false);
	m_Factory->createBlock("Static26", Ogre::Vector3(0, 0, 31.8), false);
	m_Factory->createBlock("Static27", Ogre::Vector3(0, 0, 34.98), false);
	m_Factory->createBlock("Static28", Ogre::Vector3(0, 0, 38.16), false);
	m_Factory->createBlock("Static29", Ogre::Vector3(0, 0, 41.34), false);
	m_Factory->createBlock("Static30", Ogre::Vector3(0, 0, 44.52), false);
	m_Factory->createBlock("Static31", Ogre::Vector3(0, 0, 47.7), false);
	m_Factory->createBlock("Static32", Ogre::Vector3(0, 0, 50.88), false);
	//droite
	m_Factory->createBlock("Static33", Ogre::Vector3(50.88, 0, 0), false);
	m_Factory->createBlock("Static34", Ogre::Vector3(50.88, 0, 3.18), false);
	m_Factory->createBlock("Static35", Ogre::Vector3(50.88, 0, 6.36), false);
	m_Factory->createBlock("Static36", Ogre::Vector3(50.88, 0, 9.54), false);
	m_Factory->createBlock("Static37", Ogre::Vector3(50.88, 0, 12.72), false);
	m_Factory->createBlock("Static38", Ogre::Vector3(50.88, 0, 15.9), false);
	m_Factory->createBlock("Static39", Ogre::Vector3(50.88, 0, 19.08), false);
	m_Factory->createBlock("Static40", Ogre::Vector3(50.88, 0, 22.26), false);
	m_Factory->createBlock("Static41", Ogre::Vector3(50.88, 0, 25.44), false);
	m_Factory->createBlock("Static42", Ogre::Vector3(50.88, 0, 28.62), false);
	m_Factory->createBlock("Static43", Ogre::Vector3(50.88, 0, 31.8), false);
	m_Factory->createBlock("Static44", Ogre::Vector3(50.88, 0, 34.98), false);
	m_Factory->createBlock("Static45", Ogre::Vector3(50.88, 0, 38.16), false);
	m_Factory->createBlock("Static46", Ogre::Vector3(50.88, 0, 41.34), false);
	m_Factory->createBlock("Static47", Ogre::Vector3(50.88, 0, 44.52), false);
	m_Factory->createBlock("Static48", Ogre::Vector3(50.88, 0, 47.7), false);
	m_Factory->createBlock("Static49", Ogre::Vector3(50.88, 0, 50.88), false);
	//bas
	m_Factory->createBlock("Static50", Ogre::Vector3(3.18, 0, 50.88), false);
	m_Factory->createBlock("Static51", Ogre::Vector3(6.36, 0, 50.88), false);
	m_Factory->createBlock("Static52", Ogre::Vector3(9.54, 0, 50.88), false);
	m_Factory->createBlock("Static53", Ogre::Vector3(12.72, 0, 50.88), false);
	m_Factory->createBlock("Static54", Ogre::Vector3(15.9, 0, 50.88), false);
	m_Factory->createBlock("Static55", Ogre::Vector3(19.08, 0, 50.88), false);
	m_Factory->createBlock("Static56", Ogre::Vector3(22.26, 0, 50.88), false);
	m_Factory->createBlock("Static57", Ogre::Vector3(25.44, 0, 50.88), false);
	m_Factory->createBlock("Static58", Ogre::Vector3(28.62, 0, 50.88), false);
	m_Factory->createBlock("Static59", Ogre::Vector3(31.8, 0, 50.88), false);
	m_Factory->createBlock("Static60", Ogre::Vector3(34.98, 0, 50.88), false);
	m_Factory->createBlock("Static61", Ogre::Vector3(38.16, 0, 50.88), false);
	m_Factory->createBlock("Static62", Ogre::Vector3(41.34, 0, 50.88), false);
	m_Factory->createBlock("Static63", Ogre::Vector3(44.52, 0, 50.88), false);
	m_Factory->createBlock("Static64", Ogre::Vector3(47.7, 0, 50.88), false);
	//Interieur
	m_Factory->createBlock("StaticI1", Ogre::Vector3(6.36, 0, 6.36), false);
	m_Factory->createBlock("StaticI2", Ogre::Vector3(12.72, 0, 6.36), false);
	m_Factory->createBlock("StaticI3", Ogre::Vector3(19.08, 0, 6.36), false);
	m_Factory->createBlock("StaticI5", Ogre::Vector3(31.8, 0, 6.36), false);
	m_Factory->createBlock("StaticI6", Ogre::Vector3(38.16, 0, 6.36), false);
	m_Factory->createBlock("StaticI7", Ogre::Vector3(44.52, 0, 6.36), false);
	m_Factory->createBlock("StaticI8", Ogre::Vector3(6.36, 0, 12.72), false);
	m_Factory->createBlock("StaticI9", Ogre::Vector3(12.72, 0, 12.72), false);
	m_Factory->createBlock("StaticI10", Ogre::Vector3(19.08, 0, 12.72), false);
	m_Factory->createBlock("StaticI12", Ogre::Vector3(31.8, 0, 12.72), false);
	m_Factory->createBlock("StaticI13", Ogre::Vector3(38.16, 0, 12.72), false);
	m_Factory->createBlock("StaticI14", Ogre::Vector3(44.52, 0, 12.72), false);
	m_Factory->createBlock("StaticI15", Ogre::Vector3(6.36, 0, 19.08), false);
	m_Factory->createBlock("StaticI16", Ogre::Vector3(12.72, 0, 19.08), false);
	m_Factory->createBlock("StaticI17", Ogre::Vector3(19.08, 0, 19.08), false);
	m_Factory->createBlock("StaticI19", Ogre::Vector3(31.8, 0, 19.08), false);
	m_Factory->createBlock("StaticI20", Ogre::Vector3(38.16, 0, 19.08), false);
	m_Factory->createBlock("StaticI21", Ogre::Vector3(44.52, 0, 19.08), false);
	m_Factory->createBlock("StaticI29", Ogre::Vector3(6.36, 0, 31.8), false);
	m_Factory->createBlock("StaticI30", Ogre::Vector3(12.72, 0, 31.8), false);
	m_Factory->createBlock("StaticI31", Ogre::Vector3(19.08, 0, 31.8), false);
	m_Factory->createBlock("StaticI33", Ogre::Vector3(31.8, 0, 31.8), false);
	m_Factory->createBlock("StaticI34", Ogre::Vector3(38.16, 0, 31.8), false);
	m_Factory->createBlock("StaticI35", Ogre::Vector3(44.52, 0, 31.8), false);
	m_Factory->createBlock("StaticI36", Ogre::Vector3(6.36, 0, 38.16), false);
	m_Factory->createBlock("StaticI37", Ogre::Vector3(12.72, 0, 38.16), false);
	m_Factory->createBlock("StaticI38", Ogre::Vector3(19.08, 0, 38.16), false);
	m_Factory->createBlock("StaticI40", Ogre::Vector3(31.8, 0, 38.16), false);
	m_Factory->createBlock("StaticI41", Ogre::Vector3(38.16, 0, 38.16), false);
	m_Factory->createBlock("StaticI42", Ogre::Vector3(44.52, 0, 38.16), false);
	m_Factory->createBlock("StaticI43", Ogre::Vector3(6.36, 0, 44.52), false);
	m_Factory->createBlock("StaticI44", Ogre::Vector3(12.72, 0, 44.52), false);
	m_Factory->createBlock("StaticI45", Ogre::Vector3(19.08, 0, 44.52), false);
	m_Factory->createBlock("StaticI47", Ogre::Vector3(31.8, 0, 44.52), false);
	m_Factory->createBlock("StaticI48", Ogre::Vector3(38.16, 0, 44.52), false);
	m_Factory->createBlock("StaticI49", Ogre::Vector3(44.52, 0, 44.52), false);
	//light
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