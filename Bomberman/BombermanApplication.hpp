
#ifndef BOMBERMANAPPLICATION_HPP
#define BOMBERMANAPPLICATION_HPP

#include "AdvancedOgreFramework.hpp"
#include "AppStateManager.hpp"

class BombermanApplication
{
public:
	BombermanApplication();
	~BombermanApplication();

	void startApp();

private:
	AppStateManager*	m_pAppStateManager;
};

#endif
