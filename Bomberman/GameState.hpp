//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AppState.hpp"
#include "NewMOC.h"
#include "AppFactory.hpp"

#include "DotSceneLoader.hpp"

#include <OgreSubEntity.h>
#include <OgreMaterialManager.h>

#include <stack>

//|||||||||||||||||||||||||||||||||||||||||||||||

enum QueryFlags
{
	OGRE_HEAD_MASK	= 1<<0,
    CUBE_MASK		= 1<<1
};

//|||||||||||||||||||||||||||||||||||||||||||||||

class GameState : public AppState
{
public:
	GameState();

	DECLARE_APPSTATE_CLASS(GameState)

	void enter();
	void createScene();
	void exit();
	bool pause();
	void resume();

	void moveCamera();
	void getInput();
    void buildGUI();

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

	bool mouseMoved(const OIS::MouseEvent &arg);
	bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	void update(double timeSinceLastFrame);

private:
	bool						m_bQuit;

	Ogre::Vector3				m_TranslateVector;
	Ogre::Real					m_MoveSpeed;
	Ogre::Degree				m_RotateSpeed;
	float						m_MoveScale;
	Ogre::Degree				m_RotScale;

	AppFactory*					m_Factory;

	void	setProtect(bool b);
	void	generateBBlock();
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||