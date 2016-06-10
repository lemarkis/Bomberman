#pragma once
#ifndef _IABOMBER_HPP
#define _IABOMBER_HPP

#include <algorithm>
#include "Bomber.hpp"
#include "AppFactory.hpp"

class IaBomber : public Bomber
{
public:
	IaBomber(Ogre::SceneManager* pSceneMgr, Collision::CollisionTools * pCollisionTools, Ogre::String const & pName, Ogre::Vector3 const pPosition);
	~IaBomber();

	bool keyPressed(const OIS::KeyEvent & keyEventRef);
	bool keyReleased(const OIS::KeyEvent & keyEventRef);

	bool mouseMoved(const OIS::MouseEvent & arg);
	bool mousePressed(const OIS::MouseEvent & arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent & arg, OIS::MouseButtonID id);

	void update(double timeSinceLastFrame);

private:
	void getUnbufferedInput(double timeSinceLastFrame, Ogre::Vector3 goal, Ogre::Vector3 position);
	void move();
	void setNewGoal(double x, double z);
	bool isADangerousZone(double x, double z);
	void setNewDefensiveGoal(double x, double z);
	void setNewOffensiveGoal(double x, double z);

	void tabFill(int value);
	void tabCopy(int tab[15][15]);

protected:
	Ogre::Real		moveSpeed;

	Ogre::Vector3	translateVector;
	Ogre::Vector3	lookAtVector;

	double			xGoal;
	double			zGoal;

	int				path[15][15];
	int				direction[15][15];
};

#endif /* !_IABOMBER_HPP */
