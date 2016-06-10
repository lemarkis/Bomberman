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
	Ogre::Vector3 from = node->getPosition();
	if (dir == OIS::KC_UP || dir == OIS::KC_DOWN)
	{
		if (collisionTools->check_ray_collision(Ogre::Ray(from, Ogre::Vector3::UNIT_Y), 0xFFFFFFFF, entity, 5).collided ||
			collisionTools->check_ray_collision(Ogre::Ray(from + Ogre::Vector3(.8, 0, 0), Ogre::Vector3::UNIT_Y), 0xFFFFFFFF, entity, 5).collided ||
			collisionTools->check_ray_collision(Ogre::Ray(from + Ogre::Vector3(-.8, 0, 0), Ogre::Vector3::UNIT_Y), 0xFFFFFFFF, entity, 5).collided)
		{
			return false;
		}
	}
	if (dir == OIS::KC_RIGHT || dir == OIS::KC_LEFT)
	{
		if (collisionTools->check_ray_collision(Ogre::Ray(from, Ogre::Vector3::UNIT_Y), 0xFFFFFFFF, entity, 5).collided ||
			collisionTools->check_ray_collision(Ogre::Ray(from + Ogre::Vector3(0, 0, .8), Ogre::Vector3::UNIT_Y), 0xFFFFFFFF, entity, 5).collided ||
			collisionTools->check_ray_collision(Ogre::Ray(from + Ogre::Vector3(0, 0, -.8), Ogre::Vector3::UNIT_Y), 0xFFFFFFFF, entity, 5).collided)
		{
			return false;
		}
	}
	from += Ogre::Vector3(0, .5, 0);
	switch (dir)
	{
	case OIS::KC_UP:
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from, Ogre::Vector3::NEGATIVE_UNIT_Z), 0xFFFFFFFF, entity, 1.2).collided;
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from + Ogre::Vector3(.8, 0, 0), Ogre::Vector3::NEGATIVE_UNIT_Z), 0xFFFFFFFF, entity, 1.2).collided;
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from + Ogre::Vector3(-.8, 0, 0), Ogre::Vector3::NEGATIVE_UNIT_Z), 0xFFFFFFFF, entity, 1.2).collided;
		break;
	case OIS::KC_LEFT:
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from, Ogre::Vector3::NEGATIVE_UNIT_X), 0xFFFFFFFF, entity, 1.2).collided;
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from + Ogre::Vector3(0, 0, .8), Ogre::Vector3::NEGATIVE_UNIT_X), 0xFFFFFFFF, entity, 1.2).collided;
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from + Ogre::Vector3(0, 0, -.8), Ogre::Vector3::NEGATIVE_UNIT_X), 0xFFFFFFFF, entity, 1.2).collided;
		break;
	case OIS::KC_RIGHT:
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from, Ogre::Vector3::UNIT_X), 0xFFFFFFFF, entity, 1.2).collided;
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from + Ogre::Vector3(0, 0, .8), Ogre::Vector3::UNIT_X), 0xFFFFFFFF, entity, 1.2).collided;
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from + Ogre::Vector3(0, 0, -.8), Ogre::Vector3::UNIT_X), 0xFFFFFFFF, entity, 1.2).collided;
		break;
	case OIS::KC_DOWN:
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from, Ogre::Vector3::UNIT_Z), 0xFFFFFFFF, entity, 1.2).collided;
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from + Ogre::Vector3(.8, 0, 0), Ogre::Vector3::UNIT_Z), 0xFFFFFFFF, entity, 1.2).collided;
		collided = collided || collisionTools->check_ray_collision(Ogre::Ray(from + Ogre::Vector3(-.8, 0, 0), Ogre::Vector3::UNIT_Z), 0xFFFFFFFF, entity, 1.2).collided;
		break;
	default:
		break;
	}
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

bool Bomber::compareDouble(double a, double b)
{
	double diff = a - b;
	return (diff < 0.00005) && (-diff < 0.00005);
}