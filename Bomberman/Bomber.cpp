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


bool Bomber::checkCollision(OIS::KeyCode dir)
{
	bool collided = false;
	Ogre::Vector3 from = node->getPosition();
	switch (dir)
	{
	case OIS::KC_DOWN: // z
		from += Ogre::Vector3(0, 0, -.05);
		collided = collided || collisionTools->check_ray_collision(from, from + Ogre::Vector3(0, 0, 1), 1, .5, 4294967295U, entity, false).collided;
		collided = collided || collisionTools->check_ray_collision(from, from + Ogre::Vector3(1, 0, 1), 1, .5, 4294967295U, entity, false).collided;
		collided = collided || collisionTools->check_ray_collision(from, from + Ogre::Vector3(-1, 0, 1), 1, .5, 4294967295U, entity, false).collided;
		break;
	case OIS::KC_LEFT: // -x
		from += Ogre::Vector3(-.7, 0, 0);
		collided = collided || collisionTools->check_ray_collision(from, from + Ogre::Vector3(-1, 0, 0), .07, .5, 4294967295U, entity, false).collided;
		collided = collided || collisionTools->check_ray_collision(from, from + Ogre::Vector3(-1, 0, 1), .7, .5, 4294967295U, entity, false).collided;
		collided = collided || collisionTools->check_ray_collision(from, from + Ogre::Vector3(-1, 0, -1), .7, .5, 4294967295U, entity, false).collided;
		break;
	case OIS::KC_UP: // -z
		from += Ogre::Vector3(0, 0, .05);
		collided = collided || collisionTools->check_ray_collision(from, from + Ogre::Vector3(0, 0, -1), 1, .5, 4294967295U, entity, false).collided;
		collided = collided || collisionTools->check_ray_collision(from, from + Ogre::Vector3(1, 0, -1), 1, .5, 4294967295U, entity, false).collided;
		collided = collided || collisionTools->check_ray_collision(from, from + Ogre::Vector3(-1, 0, -1), 1, .5, 4294967295U, entity, false).collided;
		break;
	case OIS::KC_RIGHT: // x
	default:
		from += Ogre::Vector3(.7, 0, 0);
		collided = collided || collisionTools->check_ray_collision(from, from + Ogre::Vector3(1, 0, 0), .07, .5, 4294967295U, entity, false).collided;
		collided = collided || collisionTools->check_ray_collision(from, from + Ogre::Vector3(1, 0, 1), .7, .5, 4294967295U, entity, false).collided;
		collided = collided || collisionTools->check_ray_collision(from, from + Ogre::Vector3(1, 0, -1), .7, .5, 4294967295U, entity, false).collided;
		break;
	}
	return collided;
}
