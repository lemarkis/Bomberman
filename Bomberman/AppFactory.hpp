#ifndef _FACTORY_HPP
#define _FACTORY_HPP

#include <vector>
#include <stack>

#include "Ground.hpp"
#include "Bomber.hpp"
#include "HumanBomber.hpp"
#include "Block.hpp"
#include "AdvancedOgreFramework.hpp"

class AppFactory
{
public:
	AppFactory(Ogre::SceneManager* pSceneMgr);
	~AppFactory();

	void createGround(Ogre::String const & pName, Ogre::Vector3 const pPosition);
	void createBomber(Ogre::String const & pName, Ogre::Vector3 const pPosition, bool pIA = true);
	void createBlock(Ogre::String const & pName, Ogre::Vector3 const pPosition, bool pBreakable = true);
	//void createBomb(Ogre::String& const pName, Ogre::Vector3& pPosition);
	
	void destroyGround(Ogre::String const & pName);
	void destroyBomber(Ogre::String const & pName);
	void destroyBlock(Ogre::String const & pName);
	//void destroyBomb(Ogre::String& const pName);

	void destroyAll();

	Ground* getGround(Ogre::String const & pName) const;
	Bomber* getBomber(Ogre::String const & pName) const;
	Block* getBlock(Ogre::String const & pName) const;
	//Bomb* getBomb(Ogre::String const & pName) const;

	void* getElement(Ogre::Entity& pEntity) const;

	void injectKeyPressed(const OIS::KeyEvent &keyEventRef);
	void injectKeyReleased(const OIS::KeyEvent &keyEventRef);

	void injectMouseMoved(const OIS::MouseEvent &evt);
	void injectMousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	void injectMouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

	void injectUpdate(double timeSinceLastFrame);

private:

protected:
	Collision::CollisionTools	*collisionTools;
	Ogre::SceneManager			*sceneMgr;

	std::vector<Ground*>		grounds;
	std::vector<Bomber*>		bombers;
	std::vector<Block*>			blocks;
	//std::vector<Bomb*>			bombs;

	int							mapCollision[15][15];
	int							mapDanger[15][15];
};

#endif // !_FACTORY_HPP
