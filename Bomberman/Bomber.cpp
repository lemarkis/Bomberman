#include "Bomber.hpp"
#include "AppFactory.hpp"

Bomber::Bomber(Collision::CollisionTools * pCollisionTools, Ogre::String const & pName): name(pName), entity(nullptr), node(nullptr), animation(nullptr), collisionTools(pCollisionTools)
{
	remainingBomb = 2;
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
	Ogre::Vector3 from = node->getPosition() + Ogre::Vector3(0, .5, 0);
	switch (dir)
	{
	case OIS::KC_UP:
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from, Ogre::Vector3::NEGATIVE_UNIT_Z), 0xFFFFFFFF, entity, 1).collided;
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from + Ogre::Vector3(.8, 0, 0), Ogre::Vector3::NEGATIVE_UNIT_Z), 0xFFFFFFFF, entity, 1).collided;
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from + Ogre::Vector3(-.8, 0, 0), Ogre::Vector3::NEGATIVE_UNIT_Z), 0xFFFFFFFF, entity, 1).collided;
		break;
	case OIS::KC_LEFT:
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from, Ogre::Vector3::NEGATIVE_UNIT_X), 0xFFFFFFFF, entity, 1).collided;
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from + Ogre::Vector3(0, 0, .8), Ogre::Vector3::NEGATIVE_UNIT_X), 0xFFFFFFFF, entity, 1).collided;
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from + Ogre::Vector3(0, 0, -.8), Ogre::Vector3::NEGATIVE_UNIT_X), 0xFFFFFFFF, entity, 1).collided;
		break;
	case OIS::KC_RIGHT:
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from, Ogre::Vector3::UNIT_X), 0xFFFFFFFF, entity, 1).collided;
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from + Ogre::Vector3(0, 0, .8), Ogre::Vector3::UNIT_X), 0xFFFFFFFF, entity, 1).collided;
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from + Ogre::Vector3(0, 0, -.8), Ogre::Vector3::UNIT_X), 0xFFFFFFFF, entity, 1).collided;
		break;
	case OIS::KC_DOWN:
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from, Ogre::Vector3::UNIT_Z), 0xFFFFFFFF, entity, 1).collided;
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from + Ogre::Vector3(.8, 0, 0), Ogre::Vector3::UNIT_Z), 0xFFFFFFFF, entity, 1).collided;
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from + Ogre::Vector3(-.8, 0, 0), Ogre::Vector3::UNIT_Z), 0xFFFFFFFF, entity, 1).collided;
		break;
	default:
		break;
	}
	/*
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
	}*/
	return collided;
}

void Bomber::dropBomb()
{
	if (remainingBomb > 0)
	{
		int x = (node->getPosition().x / 3.2) + .8;
		int z = (node->getPosition().z / 3.2) + .8;

		Ogre::String bombName(name);
		bombName.append("Bomb").append(std::to_string(remainingBomb));
		AppFactory * factory = AppFactory::getSingletonPtr();
		factory->createBomb(bombName, Ogre::Vector3(x * 3.2 - .02, 0, z * 3.2 - .02));
		(factory->mapCollision)[z][x] = 1;
		(factory->mapDanger)[z][x] = 1;
		(factory->mapDanger)[z - 1][x] = 1;
		(factory->mapDanger)[z + 1][x] = 1;
		(factory->mapDanger)[z][x - 1] = 1;
		(factory->mapDanger)[z][x + 1] = 1;
		remainingBomb -= 1;
	}
}