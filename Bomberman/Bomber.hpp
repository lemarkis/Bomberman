
#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <Ogre.h>
#include <OIS.h>
#include "NewMOC.h"
#include "AdvancedOgreFramework.hpp"

class Bomber
{
public:
	Bomber(Collision::CollisionTools * pCollisionTools, Ogre::String const & pName);
	virtual ~Bomber();

	Ogre::String const & getName() const;
	Ogre::Entity *getEntity() const;
	Ogre::SceneNode *getNode() const;

	virtual bool keyPressed(const OIS::KeyEvent &keyEventRef) = 0;
	virtual bool keyReleased(const OIS::KeyEvent &keyEventRef) = 0;

	virtual bool mouseMoved(const OIS::MouseEvent &arg) = 0;
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;

	virtual void update(double timeSinceLastFrame) = 0;

	bool checkCollision(OIS::KeyCode dir);
	void dropBomb();
private:

protected:
	Ogre::String const &		name;
	Ogre::Entity*				entity;
	Ogre::SceneNode*			node;
	Ogre::AnimationState*		animation;
	int							remainingBomb;

	Collision::CollisionTools * collisionTools;
};

#endif // !_PLAYER_HPP