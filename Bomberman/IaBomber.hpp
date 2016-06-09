#pragma once
#ifndef _IABOMBER_HPP
#define _IABOMBER_HPP

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
	void set_new_goal(int x_goal, int z_goal, int x_pos, int z_pos);
	bool is_a_dangerous_zone(int x_pos, int z_pos);
	void set_new_goal_offense(short &xg, short &zg, short x, short z);
	void set_new_goal_defense();
	bool not_dangerous(int x, int z, char xg, char zg);
	bool not_a_solid_block(int x, int z, char xg, char zg);
	void try_to_put_bomb();

protected:
	Ogre::Real		moveSpeed;

	Ogre::Vector3	translateVector;
	Ogre::Vector3	lookAtVector;
};

#endif /* !_IABOMBER_HPP */
