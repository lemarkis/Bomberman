#include "Bomber.hpp"

Bomber::Bomber(Collision::CollisionTools * pCollisionTools, Ogre::String const & pName): name(pName), entity(nullptr), node(nullptr), animation(nullptr), collisionTools(pCollisionTools)
{
}

Bomber::~Bomber()
{
}

Ogre::String const & Bomber::getName() const
{
	return this->name;
}

Ogre::Entity * Bomber::getEntity() const
{
	return this->entity;
}

Ogre::SceneNode * Bomber::getNode() const
{
	return this->node;
}
