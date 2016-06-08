#include "Block.hpp"

Block::Block(Ogre::String const & pName) : name(pName), entity(nullptr), node(nullptr)
{
}

Block::~Block()
{
}

StaticBlock::StaticBlock(Ogre::SceneManager * pSceneMgr, Ogre::String const & pName, Ogre::Vector3 const pPosition) : Block(pName)
{
	entity = pSceneMgr->createEntity(name, "M_fixe-block.mesh");
	entity->setCastShadows(false);
	node = pSceneMgr->getRootSceneNode()->createChildSceneNode(name, pPosition);
	node->rotate(Ogre::Vector3(0, 1, 0), Ogre::Degree(90), Ogre::Node::TS_LOCAL);
	node->attachObject(entity);
	
}

StaticBlock::~StaticBlock()
{
}

Ogre::String const & StaticBlock::getName() const
{
	return this->name;
}

Ogre::Entity * StaticBlock::getEntity() const
{
	return this->entity;
}

Ogre::SceneNode * StaticBlock::getNode() const
{
	return this->node;
}

DynamicBlock::DynamicBlock(Ogre::SceneManager * pSceneMgr, Ogre::String const & pName, Ogre::Vector3 const pPosition) : Block(pName)
{
	entity = pSceneMgr->createEntity(name, "M_mobile-block.mesh");
	entity->setCastShadows(false);
	node = pSceneMgr->getRootSceneNode()->createChildSceneNode(name, pPosition);
	node->attachObject(entity);
}

DynamicBlock::~DynamicBlock()
{
}

Ogre::String const & DynamicBlock::getName() const
{
	return this->name;
}

Ogre::Entity * DynamicBlock::getEntity() const
{
	return this->entity;
}

Ogre::SceneNode * DynamicBlock::getNode() const
{
	return this->node;
}
