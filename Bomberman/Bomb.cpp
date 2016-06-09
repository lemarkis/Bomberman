#include "Bomb.hpp"
#include "AppFactory.hpp"

Bomb::Bomb(Ogre::SceneManager * pSceneMgr, Ogre::String const & pName, Ogre::Vector3 const pPosition): name(pName)
{
	entity = pSceneMgr->createEntity(name, "Sphere.mesh");
	entity->setCastShadows(true);
	node = pSceneMgr->getRootSceneNode()->createChildSceneNode(name, pPosition);
	node->attachObject(entity);

	remainingLifeTime = 3000;
}

Bomb::~Bomb()
{
}

Ogre::String const & Bomb::getName() const
{
	return this->name;
}

Ogre::Entity * Bomb::getEntity() const
{
	return this->entity;
}

Ogre::SceneNode * Bomb::getNode() const
{
	return this->node;
}

bool Bomb::update(double timeSinceLastFrame)
{
	remainingLifeTime -= timeSinceLastFrame;
	if (remainingLifeTime <= 0)
	{
		int x = (node->getPosition().x / 3.2) + .8;
		int z = (node->getPosition().z / 3.2) + .8;
		AppFactory * factory = AppFactory::getSingletonPtr();
		factory->mapCollision[z][x] = 0;
		factory->mapDanger[z][x] = 0;
		factory->mapDanger[z - 1][x] = 0;
		factory->mapDanger[z + 1][x] = 0;
		factory->mapDanger[z][x - 1] = 0;
		factory->mapDanger[z][x + 1] = 0;
		Collision::CollisionTools * tools = factory->getCollisionTools();
		Collision::SCheckCollisionAnswer result;
		Ogre::Vector3 from = node->getPosition() + Ogre::Vector3(0, .5, 0);
		//x
		result = tools->check_ray_collision(Ogre::Ray(from, Ogre::Vector3::UNIT_X), 0xFFFFFFFF, entity, 4.2, false);
		_breakItem(result);
		//-x
		result = tools->check_ray_collision(Ogre::Ray(from, Ogre::Vector3::NEGATIVE_UNIT_X), 0xFFFFFFFF, entity, 4.2, false);
		_breakItem(result);
		//z
		result = tools->check_ray_collision(Ogre::Ray(from, Ogre::Vector3::UNIT_Z), 0xFFFFFFFF, entity, 4.2, false);
		_breakItem(result);
		//-z
		result = tools->check_ray_collision(Ogre::Ray(from, Ogre::Vector3::NEGATIVE_UNIT_Z), 0xFFFFFFFF, entity, 4.2, false);
		_breakItem(result);
		return true;
	}
	return false;
}

void Bomb::_breakItem(Collision::SCheckCollisionAnswer result)
{
	if (result.collided)
	{
		Ogre::String name = result.entity->getName();
		if (name.find("Player") != Ogre::String::npos && name.find("Bomb") == Ogre::String::npos)
		{
			AppFactory::getSingletonPtr()->destroyBomber(result.entity->getName());
		}
		else if (name.find("Break") != Ogre::String::npos)
		{
			AppFactory::getSingletonPtr()->destroyBlock(result.entity->getName());
		}
	}
}
