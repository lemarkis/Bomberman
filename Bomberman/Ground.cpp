#include "Ground.hpp"

Ground::Ground(Ogre::SceneManager * pSceneMgr, Ogre::String const & pName, Ogre::Vector3 const pPosition): name(pName)
{
	entity = pSceneMgr->createEntity(name, "Plaque.mesh");
	node = pSceneMgr->getRootSceneNode()->createChildSceneNode(name, pPosition);
	node->attachObject(entity);
}

Ground::~Ground()
{
}


Ogre::String const & Ground::getName() const
{
	return this->name;
}

Ogre::Entity * Ground::getEntity() const
{
	return this->entity;
}

Ogre::SceneNode * Ground::getNode() const
{
	return this->node;
}