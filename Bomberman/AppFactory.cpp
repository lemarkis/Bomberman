#include "AppFactory.hpp"

template<> AppFactory * Ogre::Singleton<AppFactory>::msSingleton = 0;

template<typename T>
static void removeEntityCollision(T pElement)
{
	AppFactory::getSingletonPtr()->getCollisionTools()->remove_entity(pElement->getEntity());
}

template<typename T>
void destroyNode(T pElement)
{
	Ogre::SceneManager * sceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->getSceneManager("GameSceneMgr");
	sceneMgr->destroyEntity(pElement->getEntity());
	sceneMgr->destroySceneNode(pElement->getNode());
}

AppFactory::AppFactory(Ogre::SceneManager * pSceneMgr): sceneMgr(pSceneMgr)
{
	collisionTools = new Collision::CollisionTools();
	
	int	i, j;
	i = 0;
	while (i < 15)
	{
		j = 0;
		while (j < 15)
		{
			mapCollision[i][j] = 0;
			mapDanger[i][j] = 0;
			j++;
		}
		i++;
	}
}

AppFactory::~AppFactory()
{
	destroyAll();
	delete collisionTools;
}

void AppFactory::createGround(Ogre::String const & pName, Ogre::Vector3 const pPosition)
{
	Ogre::String str = Ogre::String("Creating ground ").append(pName);
	OgreFramework::getSingletonPtr()->m_pLog->logMessage(str);
	Ground * ground = new Ground(sceneMgr, pName, pPosition);
	grounds.push_back(ground);
}

void AppFactory::createBomber(Ogre::String const & pName, Ogre::Vector3 const pPosition, bool pIA)
{
	Ogre::String str = Ogre::String("Creating bomber ").append(pName);
	OgreFramework::getSingletonPtr()->m_pLog->logMessage(str);
	Bomber * bomber;
	if (pIA)
	{
		bomber = new IaBomber(sceneMgr, collisionTools, pName, pPosition);
	}
	else
	{
		bomber = new HumanBomber(sceneMgr, collisionTools, pName, pPosition);
	}
	bombers.push_back(bomber);
	collisionTools->register_entity(bomber->getEntity(), Collision::COLLISION_BOX);
}

void AppFactory::createBlock(Ogre::String const & pName, Ogre::Vector3 const pPosition, bool pBreakable)
{
	Ogre::String str = Ogre::String("Creating block ").append(pName);
	OgreFramework::getSingletonPtr()->m_pLog->logMessage(str);
	Block * block;
	int x = (pPosition.x / 3.2) + .02;
	int z = (pPosition.z / 3.2) + .02;
	if (pBreakable)
	{
		block = new DynamicBlock(sceneMgr, pName, pPosition);
		mapCollision[z][x] = 2;
	}
	else
	{
		block = new StaticBlock(sceneMgr, pName, pPosition);
		mapCollision[z][x] = 1;
	}
	blocks.push_back(block);
	collisionTools->register_static_entity(block->getEntity(), block->getNode()->getPosition(), block->getNode()->getOrientation(), block->getNode()->getScale(), Collision::COLLISION_BOX);
}

void AppFactory::createBomb(Ogre::String const & pName, Ogre::Vector3 const pPosition)
{
	Ogre::String str = Ogre::String("Creating bomb ").append(pName);
	OgreFramework::getSingletonPtr()->m_pLog->logMessage(str);
	Bomb * bomb = new Bomb(sceneMgr, pName, pPosition);
	bombs.push_back(bomb);
	collisionTools->register_static_entity(bomb->getEntity(), bomb->getNode()->getPosition(), bomb->getNode()->getOrientation(), bomb->getNode()->getScale());
}

void AppFactory::destroyGround(Ogre::String const & pName)
{
	for (std::vector<Ground*>::iterator it = grounds.begin(); it != grounds.end(); it++)
	{
		if (!((*it)->getName().compare(pName)))
		{
			destroyNode(*it);
			grounds.erase(it);
			return;
		}
	}
}

void AppFactory::destroyBomber(Ogre::String const & pName)
{
	for (std::vector<Bomber*>::iterator it = bombers.begin(); it != bombers.end(); it++)
	{
		if (!((*it)->getName().compare(pName)))
		{
			removeEntityCollision(*it);
			destroyNode(*it);
			bombers.erase(it);
			return;
		}
	}
}

void AppFactory::destroyBlock(Ogre::String const & pName)
{
	for (std::vector<Block*>::iterator it = blocks.begin(); it != blocks.end(); it++)
	{
		if (!((*it)->getName().compare(pName)))
		{
			removeEntityCollision(*it);
			int x = ((*it)->getNode()->getPosition().x / 3.2) + .02;
			int z = ((*it)->getNode()->getPosition().z / 3.2) + .02;
			mapCollision[z][x] = mapCollision[z][x] == 2 ? 0 : mapCollision[z][x];
			destroyNode(*it);
			blocks.erase(it);
			return;
		}
	}
}

void AppFactory::destroyBomb(Ogre::String const & pName)
{
	for (std::vector<Bomb*>::iterator it = bombs.begin(); it != bombs.end(); it++)
	{
		if (!((*it)->getName().compare(pName)))
		{
			removeEntityCollision(*it);
			destroyNode(*it);
			bombs.erase(it);
			return;
		}
	}
}

void AppFactory::destroyAll()
{
	//Ground
	//std::for_each(grounds.begin(), grounds.end(), destroyNode<Ground*>);
	grounds.clear();

	//Bomber
	std::for_each(bombers.begin(), bombers.end(), removeEntityCollision<Bomber*>);
	//std::for_each(bombers.begin(), bombers.end(), destroyNode<Bomber*>);
	bombers.clear();

	//Block
	std::for_each(blocks.begin(), blocks.end(), removeEntityCollision<Block*>);
	//std::for_each(blocks.begin(), blocks.end(), destroyNode<Block*>);
	blocks.clear();
	
	//Bomb
	std::for_each(bombs.begin(), bombs.end(), removeEntityCollision<Bomb*>);
	//std::for_each(bombs.begin(), bombs.end(), destroyNode<Bomb*>);
	bombs.clear();
}

Ground * AppFactory::getGround(Ogre::String const & pName) const
{
	for (std::vector<Ground*>::const_iterator it = grounds.begin(); it != grounds.end(); it++)
	{
		if (!((*it)->getName().compare(pName)))
		{
			return *it;
		}
	}
	return nullptr;
}

Bomber * AppFactory::getBomber(Ogre::String const & pName) const
{
	for (std::vector<Bomber*>::const_iterator it = bombers.begin(); it != bombers.end(); it++)
	{
		if (!((*it)->getName().compare(pName)))
		{
			return *it;
		}
	}
	return nullptr;
}

Block * AppFactory::getBlock(Ogre::String const & pName) const
{
	for (std::vector<Block*>::const_iterator it = blocks.begin(); it != blocks.end(); it++)
	{
		if (!((*it)->getName().compare(pName)))
		{
			return *it;
		}
	}
	return nullptr;
}

Bomb * AppFactory::getBomb(Ogre::String const & pName) const
{
	for (std::vector<Bomb*>::const_iterator it = bombs.begin(); it != bombs.end(); it++)
	{
		if (!((*it)->getName().compare(pName)))
		{
			return (*it);
		}
	}
	return nullptr;
}

void * AppFactory::getElement(Ogre::Entity * pEntity) const
{
	for (std::vector<Ground*>::const_iterator it = grounds.begin(); it != grounds.end(); it++)
	{
		if (!((*it)->getEntity()->getName().compare(pEntity->getName())))
		{
			return *it;
		}
	}
	for (std::vector<Bomber*>::const_iterator it = bombers.begin(); it != bombers.end(); it++)
	{
		if (!((*it)->getEntity()->getName().compare(pEntity->getName())))
		{
			return *it;
		}
	}
	for (std::vector<Block*>::const_iterator it = blocks.begin(); it != blocks.end(); it++)
	{
		if (!((*it)->getEntity()->getName().compare(pEntity->getName())))
		{
			return *it;
		}
	}
	for (std::vector<Bomb*>::const_iterator it = bombs.begin(); it != bombs.end(); it++)
	{
		if (!((*it)->getEntity()->getName().compare(pEntity->getName())))
		{
			return *it;
		}
	}
	return nullptr;
}

void AppFactory::injectKeyPressed(const OIS::KeyEvent & keyEventRef)
{
	for (std::vector<Bomber*>::const_iterator it = bombers.begin(); it != bombers.end(); it++)
	{
		(*it)->keyPressed(keyEventRef);
	}
}

void AppFactory::injectKeyReleased(const OIS::KeyEvent & keyEventRef)
{
	for (std::vector<Bomber*>::const_iterator it = bombers.begin(); it != bombers.end(); it++)
	{
		(*it)->keyReleased(keyEventRef);
	}
}

void AppFactory::injectMouseMoved(const OIS::MouseEvent & evt)
{
	for (std::vector<Bomber*>::const_iterator it = bombers.begin(); it != bombers.end(); it++)
	{
		(*it)->mouseMoved(evt);
	}
}

void AppFactory::injectMousePressed(const OIS::MouseEvent & evt, OIS::MouseButtonID id)
{
	for (std::vector<Bomber*>::const_iterator it = bombers.begin(); it != bombers.end(); it++)
	{
		(*it)->mousePressed(evt, id);
	}
}

void AppFactory::injectMouseReleased(const OIS::MouseEvent & evt, OIS::MouseButtonID id)
{
	for (std::vector<Bomber*>::const_iterator it = bombers.begin(); it != bombers.end(); it++)
	{
		(*it)->mouseReleased(evt, id);
	}
}

void AppFactory::injectUpdate(double timeSinceLastFrame)
{
	std::vector<Bomb*> toErase;

	for (std::vector<Bomber*>::const_iterator it = bombers.begin(); it != bombers.end(); ++it)
	{
		(*it)->update(timeSinceLastFrame);
	}
	for (std::vector<Bomb*>::const_iterator it = bombs.begin(); it != bombs.end(); ++it)
	{
		if ((*it)->update(timeSinceLastFrame))
		{
			toErase.push_back(*it);
		}
	}

	while (!toErase.empty())
	{
		AppFactory::getSingletonPtr()->destroyBomb(toErase.back()->getName());
		toErase.erase(toErase.end() - 1);
	}
}

std::vector<Bomber*> AppFactory::getBombers() const
{
	 return bombers;
}