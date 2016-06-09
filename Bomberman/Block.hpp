#ifndef _BLOCK_HPP
#define _BLOCK_HPP

#include "Ogre.h"

class Block
{
public:
	Block(Ogre::String const & pName);
	~Block();

	virtual Ogre::String const & getName() const = 0;
	virtual Ogre::Entity * getEntity() const = 0;
	virtual Ogre::SceneNode * getNode() const = 0;

private:

protected:
	Ogre::String const		name;
	Ogre::Entity *			entity;
	Ogre::SceneNode *		node;

};

class StaticBlock : public Block
{
public:
	StaticBlock(Ogre::SceneManager * pSceneMgr, Ogre::String const & pName, Ogre::Vector3 const pPosition);
	~StaticBlock();

	Ogre::String const & getName() const;
	Ogre::Entity * getEntity() const;
	Ogre::SceneNode * getNode() const;

private:

};

class DynamicBlock : public Block
{
public:
	DynamicBlock(Ogre::SceneManager * pSceneMgr, Ogre::String const & pName, Ogre::Vector3 const pPosition);
	~DynamicBlock();

	Ogre::String const & getName() const;
	Ogre::Entity * getEntity() const;
	Ogre::SceneNode * getNode() const;

private:

};

#endif // !_BLOCK_HPP
