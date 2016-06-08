#include "AppFactory.hpp"

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
	/* if (pIA)
	{
		bomber = new IABomber(sceneMgr, pName, pPosition);
	}
	else
	{*/
		bomber = new HumanBomber(sceneMgr, collisionTools, pName, pPosition);
	//}
	bombers.push_back(bomber);
	collisionTools->register_entity(bomber->getEntity());
}

void AppFactory::createBlock(Ogre::String const & pName, Ogre::Vector3 const pPosition, bool pBreakable)
{
	Ogre::String str = Ogre::String("Creating block ").append(pName);
	OgreFramework::getSingletonPtr()->m_pLog->logMessage(str);
	Block * block; 
	if (pBreakable)
	{
		block = new DynamicBlock(sceneMgr, pName, pPosition);
	}
	else
	{
		block = new StaticBlock(sceneMgr, pName, pPosition);
	}
	blocks.push_back(block);
	collisionTools->register_entity(block->getEntity());
	int x = pPosition.x / 3.18;
	int z = pPosition.z / 3.18;
	mapCollision[z][x] = 1;
}

void AppFactory::destroyGround(Ogre::String const & pName)
{
	for (std::vector<Ground*>::iterator it = grounds.begin(); it != grounds.end(); it++)
	{
		if (!((*it)->getName().compare(pName)))
		{
			Ground * ground = (*it);
			grounds.erase(it);
			delete ground;
		}
	}
}

void AppFactory::destroyBomber(Ogre::String const & pName)
{
	for (std::vector<Bomber*>::iterator it = bombers.begin(); it != bombers.end(); it++)
	{
		if (!((*it)->getName().compare(pName)))
		{
			Bomber * bomber = (*it);
			bombers.erase(it);
			delete bomber;
		}
	}
}

void AppFactory::destroyBlock(Ogre::String const & pName)
{
}

void AppFactory::destroyAll()
{
	//Ground
	for (std::vector<Ground*>::iterator it = grounds.begin(); it != grounds.end(); it++)
	{
		Ground * ground = (*it);
		grounds.erase(it);
		delete ground;
	}

	//Bomber
	for (std::vector<Bomber*>::iterator it = bombers.begin(); it != bombers.end(); it++)
	{
		Bomber * bomber = (*it);
		bombers.erase(it);
		delete bomber;
	}

	//Block
	for (std::vector<Block*>::iterator it = blocks.begin(); it != blocks.end(); it++)
	{
		Block * block = (*it);
		blocks.erase(it);
		delete block;
	}


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

void * AppFactory::getElement(Ogre::Entity & pEntity) const
{
	for (std::vector<Ground*>::const_iterator it = grounds.begin(); it != grounds.end(); it++)
	{
		if (!((*it)->getEntity()->getName().compare(pEntity.getName())))
		{
			return *it;
		}
	}
	for (std::vector<Bomber*>::const_iterator it = bombers.begin(); it != bombers.end(); it++)
	{
		if (!((*it)->getEntity()->getName().compare(pEntity.getName())))
		{
			return *it;
		}
	}
	for (std::vector<Block*>::const_iterator it = blocks.begin(); it != blocks.end(); it++)
	{
		if (!((*it)->getEntity()->getName().compare(pEntity.getName())))
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
	for (std::vector<Bomber*>::const_iterator it = bombers.begin(); it != bombers.end(); it++)
	{
		(*it)->update(timeSinceLastFrame);
	}
}
