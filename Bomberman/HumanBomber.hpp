
#ifndef _HUMANBOMBER_HPP
#define _HUMANBOMBER_HPP

#include "Bomber.hpp"

class HumanBomber : public Bomber
{
public:
	HumanBomber(Ogre::SceneManager* pSceneMgr, Collision::CollisionTools * pCollisionTools, Ogre::String const & pName, Ogre::Vector3 const pPosition);
	~HumanBomber();

	bool keyPressed(const OIS::KeyEvent & keyEventRef);
	bool keyReleased(const OIS::KeyEvent & keyEventRef);

	bool mouseMoved(const OIS::MouseEvent & arg);
	bool mousePressed(const OIS::MouseEvent & arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent & arg, OIS::MouseButtonID id);

	void update(double timeSinceLastFrame);

private:
	bool checkCollision(Collision::CollisionTools * pCollisionTools);
	void getUnbufferedInput();
	void move();

protected:
	Ogre::Real		moveSpeed;

	Ogre::Vector3	translateVector;
	Ogre::Vector3	lookAtVector;
};

#endif // !_HUMANBOMBER_HPP
