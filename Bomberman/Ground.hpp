
#ifndef _GROUND_HPP
#define _GROUND_HPP

#include "Ogre.h"

class Ground
{
public:
	Ground(Ogre::SceneManager * pSceneMgr, Ogre::String const & pName, Ogre::Vector3 const pPosition);
	~Ground();

	Ogre::String const & getName() const;
	Ogre::Entity * getEntity() const;
	Ogre::SceneNode * getNode() const;

private:

protected:
	Ogre::String const		name;
	Ogre::Entity *			entity;
	Ogre::SceneNode *		node;
};

#endif // !_GROUND_HPP
