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

	new AppFactory(m_pSceneMgr);

    m_pSceneMgr->addRenderQueueListener(OgreFramework::getSingletonPtr()->m_pOverlaySystem);

    m_pCamera = m_pSceneMgr->createCamera("GameCamera");
    m_pCamera->setPosition(Ogre::Vector3(22.38, 30, 55));
    m_pCamera->lookAt(Ogre::Vector3(22.38, 0, 28.78));
    m_pCamera->setNearClipDistance(2);

    m_pCamera->setAspectRatio(Ogre::Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) /
        Ogre::Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));

    OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

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

	delete AppFactory::getSingletonPtr();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::createScene()
{
	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	m_pSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	AppFactory * factory = AppFactory::getSingletonPtr();
	//Plaques
	factory->createGround("Plaque1", Ogre::Vector3(3.18, 0, 3.18));
	factory->createGround("Plaque2", Ogre::Vector3(3.18, 0, 15.98));
	factory->createGround("Plaque3", Ogre::Vector3(3.18, 0, 28.78));
	factory->createGround("Plaque4", Ogre::Vector3(3.18, 0, 41.58));
	factory->createGround("Plaque5", Ogre::Vector3(15.98, 0, 3.18));
	factory->createGround("Plaque6", Ogre::Vector3(15.98, 0, 15.98));
	factory->createGround("Plaque7", Ogre::Vector3(15.98, 0, 28.78));
	factory->createGround("Plaque8", Ogre::Vector3(15.98, 0, 41.58));
	factory->createGround("Plaque9", Ogre::Vector3(28.78, 0, 3.18));
	factory->createGround("Plaque10", Ogre::Vector3(28.78, 0, 15.98));
	factory->createGround("Plaque11", Ogre::Vector3(28.78, 0, 28.78));
	factory->createGround("Plaque12", Ogre::Vector3(28.78, 0, 41.58));
	factory->createGround("Plaque13", Ogre::Vector3(41.58, 0, 3.18));
	factory->createGround("Plaque14", Ogre::Vector3(41.58, 0, 15.98));
	factory->createGround("Plaque15", Ogre::Vector3(41.58, 0, 28.78));
	factory->createGround("Plaque16", Ogre::Vector3(41.58, 0, 41.58));
	//player
	factory->createBomber("Player1", Ogre::Vector3(22.38, 0, 22.38), false);
	//haut
	factory->createBlock("Static1", Ogre::Vector3(0, 0, 0), false);
	factory->createBlock("Static2", Ogre::Vector3(3.18, 0, 0), false);
	factory->createBlock("Static3", Ogre::Vector3(6.38, 0, 0), false);
	factory->createBlock("Static4", Ogre::Vector3(9.58, 0, 0), false);
	factory->createBlock("Static5", Ogre::Vector3(12.78, 0, 0), false);
	factory->createBlock("Static6", Ogre::Vector3(15.98, 0, 0), false);
	factory->createBlock("Static7", Ogre::Vector3(19.18, 0, 0), false);
	factory->createBlock("Static8", Ogre::Vector3(22.38, 0, 0), false);
	factory->createBlock("Static9", Ogre::Vector3(25.58, 0, 0), false);
	factory->createBlock("Static10", Ogre::Vector3(28.78, 0, 0), false);
	factory->createBlock("Static11", Ogre::Vector3(31.98, 0, 0), false);
	factory->createBlock("Static12", Ogre::Vector3(35.18, 0, 0), false);
	factory->createBlock("Static13", Ogre::Vector3(38.38, 0, 0), false);
	factory->createBlock("Static14", Ogre::Vector3(41.58, 0, 0), false);
	//gauche
	factory->createBlock("Static17", Ogre::Vector3(0, 0, 3.18), false);
	factory->createBlock("Static18", Ogre::Vector3(0, 0, 6.38), false);
	factory->createBlock("Static19", Ogre::Vector3(0, 0, 9.58), false);
	factory->createBlock("Static20", Ogre::Vector3(0, 0, 12.78), false);
	factory->createBlock("Static21", Ogre::Vector3(0, 0, 15.98), false);
	factory->createBlock("Static22", Ogre::Vector3(0, 0, 19.18), false);
	factory->createBlock("Static23", Ogre::Vector3(0, 0, 22.38), false);
	factory->createBlock("Static24", Ogre::Vector3(0, 0, 25.58), false);
	factory->createBlock("Static25", Ogre::Vector3(0, 0, 28.78), false);
	factory->createBlock("Static26", Ogre::Vector3(0, 0, 31.98), false);
	factory->createBlock("Static27", Ogre::Vector3(0, 0, 35.18), false);
	factory->createBlock("Static28", Ogre::Vector3(0, 0, 38.38), false);
	factory->createBlock("Static29", Ogre::Vector3(0, 0, 41.58), false);
	factory->createBlock("Static30", Ogre::Vector3(0, 0, 44.78), false);
	//droite
	factory->createBlock("Static33", Ogre::Vector3(44.78, 0, 0), false);
	factory->createBlock("Static34", Ogre::Vector3(44.78, 0, 3.18), false);
	factory->createBlock("Static35", Ogre::Vector3(44.78, 0, 6.38), false);
	factory->createBlock("Static36", Ogre::Vector3(44.78, 0, 9.58), false);
	factory->createBlock("Static37", Ogre::Vector3(44.78, 0, 12.78), false);
	factory->createBlock("Static38", Ogre::Vector3(44.78, 0, 15.98), false);
	factory->createBlock("Static39", Ogre::Vector3(44.78, 0, 19.18), false);
	factory->createBlock("Static40", Ogre::Vector3(44.78, 0, 22.38), false);
	factory->createBlock("Static41", Ogre::Vector3(44.78, 0, 25.58), false);
	factory->createBlock("Static42", Ogre::Vector3(44.78, 0, 28.78), false);
	factory->createBlock("Static43", Ogre::Vector3(44.78, 0, 31.98), false);
	factory->createBlock("Static44", Ogre::Vector3(44.78, 0, 35.18), false);
	factory->createBlock("Static45", Ogre::Vector3(44.78, 0, 38.38), false);
	factory->createBlock("Static46", Ogre::Vector3(44.78, 0, 41.58), false);
	//bas
	factory->createBlock("Static50", Ogre::Vector3(3.18, 0, 44.78), false);
	factory->createBlock("Static51", Ogre::Vector3(6.38, 0, 44.78), false);
	factory->createBlock("Static52", Ogre::Vector3(9.58, 0, 44.78), false);
	factory->createBlock("Static53", Ogre::Vector3(12.78, 0, 44.78), false);
	factory->createBlock("Static54", Ogre::Vector3(15.98, 0, 44.78), false);
	factory->createBlock("Static55", Ogre::Vector3(19.18, 0, 44.78), false);
	factory->createBlock("Static56", Ogre::Vector3(22.38, 0, 44.78), false);
	factory->createBlock("Static57", Ogre::Vector3(25.58, 0, 44.78), false);
	factory->createBlock("Static58", Ogre::Vector3(28.78, 0, 44.78), false);
	factory->createBlock("Static59", Ogre::Vector3(31.98, 0, 44.78), false);
	factory->createBlock("Static60", Ogre::Vector3(35.18, 0, 44.78), false);
	factory->createBlock("Static61", Ogre::Vector3(38.38, 0, 44.78), false);
	factory->createBlock("Static62", Ogre::Vector3(41.58, 0, 44.78), false);
	factory->createBlock("Static63", Ogre::Vector3(44.78, 0, 44.78), false);
	//Interieur
	factory->createBlock("StaticI1", Ogre::Vector3(6.38, 0, 6.38), false);
	factory->createBlock("StaticI2", Ogre::Vector3(12.78, 0, 6.38), false);
	factory->createBlock("StaticI3", Ogre::Vector3(19.18, 0, 6.38), false);
	factory->createBlock("StaticI5", Ogre::Vector3(25.58, 0, 6.38), false);
	factory->createBlock("StaticI6", Ogre::Vector3(31.98, 0, 6.38), false);
	factory->createBlock("StaticI7", Ogre::Vector3(38.38, 0, 6.38), false);
	factory->createBlock("StaticI8", Ogre::Vector3(6.38, 0, 12.78), false);
	factory->createBlock("StaticI9", Ogre::Vector3(12.78, 0, 12.78), false);
	factory->createBlock("StaticI10", Ogre::Vector3(19.18, 0, 12.78), false);
	factory->createBlock("StaticI12", Ogre::Vector3(25.58, 0, 12.78), false);
	factory->createBlock("StaticI13", Ogre::Vector3(31.98, 0, 12.78), false);
	factory->createBlock("StaticI14", Ogre::Vector3(38.38, 0, 12.78), false);
	factory->createBlock("StaticI15", Ogre::Vector3(6.38, 0, 19.18), false);
	factory->createBlock("StaticI16", Ogre::Vector3(12.78, 0, 19.18), false);
	factory->createBlock("StaticI17", Ogre::Vector3(19.18, 0, 19.18), false);
	factory->createBlock("StaticI19", Ogre::Vector3(25.58, 0, 19.18), false);
	factory->createBlock("StaticI20", Ogre::Vector3(31.98, 0, 19.18), false);
	factory->createBlock("StaticI21", Ogre::Vector3(38.38, 0, 19.18), false);
	factory->createBlock("StaticI29", Ogre::Vector3(6.38, 0, 25.58), false);
	factory->createBlock("StaticI30", Ogre::Vector3(12.78, 0, 25.58), false);
	factory->createBlock("StaticI31", Ogre::Vector3(19.18, 0, 25.58), false);
	factory->createBlock("StaticI33", Ogre::Vector3(25.58, 0, 25.58), false);
	factory->createBlock("StaticI34", Ogre::Vector3(31.98, 0, 25.58), false);
	factory->createBlock("StaticI35", Ogre::Vector3(38.38, 0, 25.58), false);
	factory->createBlock("StaticI36", Ogre::Vector3(6.38, 0, 31.98), false);
	factory->createBlock("StaticI37", Ogre::Vector3(12.78, 0, 31.98), false);
	factory->createBlock("StaticI38", Ogre::Vector3(19.18, 0, 31.98), false);
	factory->createBlock("StaticI40", Ogre::Vector3(25.58, 0, 31.98), false);
	factory->createBlock("StaticI41", Ogre::Vector3(31.98, 0, 31.98), false);
	factory->createBlock("StaticI42", Ogre::Vector3(38.38, 0, 31.98), false);
	factory->createBlock("StaticI43", Ogre::Vector3(6.38, 0, 38.38), false);
	factory->createBlock("StaticI44", Ogre::Vector3(12.78, 0, 38.38), false);
	factory->createBlock("StaticI45", Ogre::Vector3(19.18, 0, 38.38), false);
	factory->createBlock("StaticI47", Ogre::Vector3(25.58, 0, 38.38), false);
	factory->createBlock("StaticI48", Ogre::Vector3(31.98, 0, 38.38), false);
	factory->createBlock("StaticI49", Ogre::Vector3(38.38, 0, 38.38), false);
	//light
	Ogre::Light *spotlight = m_pSceneMgr->createLight("Spotlight");
	spotlight->setDiffuseColour(.7, .7, .7);
	spotlight->setSpecularColour(.3, .7, .7);
	spotlight->setDirection(0, -1, 0);
	spotlight->setPosition(22.38, 20, 22.38);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	AppFactory::getSingletonPtr()->injectKeyPressed(keyEventRef);

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
	AppFactory::getSingletonPtr()->injectKeyReleased(keyEventRef);

    OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::mouseMoved(const OIS::MouseEvent &evt)
{
	AppFactory::getSingletonPtr()->injectMouseMoved(evt);

	m_pCamera->yaw(Ogre::Degree(evt.state.X.rel * -0.1f));
	m_pCamera->pitch(Ogre::Degree(evt.state.Y.rel * -0.1f));

	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	AppFactory::getSingletonPtr()->injectMousePressed(evt, id);

    //if(OgreFramework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) return true;

    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	AppFactory::getSingletonPtr()->injectMouseReleased(evt, id);

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
	//Camera
	OIS::Keyboard *lKeyboard = OgreFramework::getSingletonPtr()->m_pKeyboard;
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

	AppFactory::getSingletonPtr()->injectUpdate(timeSinceLastFrame);

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
    //OgreFramework::getSingletonPtr()->m_pTrayMgr->createLabel(OgreBites::TL_TOP, "GameLbl", "Game mode", 250);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->hideCursor();
}

//|||||||||||||||||||||||||||||||||||||||||||||||