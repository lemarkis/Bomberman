
#include "BombermanApplication.hpp"

#include "MenuState.hpp"
#include "GameState.hpp"
#include "PauseState.hpp"
#include "SplashScreenState.hpp"

BombermanApplication::BombermanApplication()
{
	m_pAppStateManager = 0;
}

BombermanApplication::~BombermanApplication()
{
	delete m_pAppStateManager;
	delete OgreFramework::getSingletonPtr();
}

void BombermanApplication::startApp()
{
	new OgreFramework();
	if (!OgreFramework::getSingletonPtr()->initOgre("AdvancedOgreFramework", 0, 0))
		return;

	OgreFramework::getSingletonPtr()->m_pLog->logMessage("App initialized!");

	m_pAppStateManager = new AppStateManager();

	MenuState::create(m_pAppStateManager, "MenuState");
	GameState::create(m_pAppStateManager, "GameState");
	PauseState::create(m_pAppStateManager, "PauseState");
	SplashScreenState::create(m_pAppStateManager, "SplashScreenState");

	m_pAppStateManager->start(m_pAppStateManager->findByName("SplashScreenState"));
}
