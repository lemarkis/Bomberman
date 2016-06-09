
#ifndef _BOMB_HPP
#define _BOMB_HPP

#include <Ogre.h>
#include "NewMOC.h"

class Bomb
{
public:
	Bomb(Ogre::SceneManager * pSceneMgr, Ogre::String const & pName, Ogre::Vector3 const pPosition);
	~Bomb();

	Ogre::String const & getName() const;
	Ogre::Entity * getEntity() const;
	Ogre::SceneNode * getNode() const;

	bool update(double timeSinceLastFrame);
private:
	void _breakItem(Collision::SCheckCollisionAnswer result);

protected:
	Ogre::String const		name;
	Ogre::Entity *			entity;
	Ogre::SceneNode *		node;
	double					remainingLifeTime;
};

#endif // !_BOMB_HPP
