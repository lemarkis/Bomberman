#include <random>
#include "IaBomber.hpp"

IaBomber::IaBomber(Ogre::SceneManager * pSceneMgr, Collision::CollisionTools * pCollisionTools, Ogre::String const & pName, Ogre::Vector3 const pPosition) : Bomber(pCollisionTools, pName)
{
	entity = pSceneMgr->createEntity(name, "Lego_perso_ia.mesh");
	entity->setCastShadows(true);
	node = pSceneMgr->getRootSceneNode()->createChildSceneNode(name, pPosition);
	node->setScale(.65, .65, .65);
	node->attachObject(entity);
	animation = entity->getAnimationState("my_animation");
	animation->setLoop(true);

	moveSpeed = 12.f;
	xGoal = pPosition.x;
	zGoal = pPosition.z;
}

IaBomber::~IaBomber()
{
}

bool IaBomber::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	if (keyEventRef.key == OIS::KC_I)
	{
		zGoal -= 3.18;
	}
	if (keyEventRef.key == OIS::KC_J)
	{
		xGoal -= 3.18;
	}
	if (keyEventRef.key == OIS::KC_K)
	{
		zGoal += 3.18;
	}
	if (keyEventRef.key == OIS::KC_L)
	{
		xGoal += 3.18;
	}
	return true;
}

bool IaBomber::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	return true;
}

bool IaBomber::mouseMoved(const OIS::MouseEvent &arg)
{
	return true;
}

bool IaBomber::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return true;
}

bool IaBomber::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return true;
}

void IaBomber::update(double timeSinceLastFrame)
{
	animation->addTime(timeSinceLastFrame / 400);
	
	translateVector = Ogre::Vector3::ZERO;
	lookAtVector = Ogre::Vector3::ZERO;

	double x = node->getPosition().x;
	double z = node->getPosition().z;
	if (x < xGoal) //x
	{
		if (x > (xGoal - 1))
		{
			node->setPosition(xGoal, 0, z);
		}
		else
		{
			translateVector.x = std::min((moveSpeed * timeSinceLastFrame / 1000), 3.18);
		}
		lookAtVector.x = 1;
		animation->setEnabled(true);
	}
	else if (x > xGoal) //-x
	{
		if (x < (xGoal + 1))
		{
			node->setPosition(xGoal, 0, z);
		}
		else
		{
			translateVector.x = -std::min((moveSpeed * timeSinceLastFrame / 1000), 3.18);
		}
		lookAtVector.x = -1;
		animation->setEnabled(true);
	}
	else if (z < zGoal) //z
	{
		if (z >(zGoal - 1))
		{
			node->setPosition(x, 0, zGoal);
		}
		else
		{
			translateVector.z = std::min((moveSpeed * timeSinceLastFrame / 1000), 3.18);
		}
		lookAtVector.z = 1;
		animation->setEnabled(true);
	}
	else if (z > zGoal) //-z
	{
		if (x < (zGoal + 1))
		{
			node->setPosition(x, 0, zGoal);
		}
		else
		{
			translateVector.z = -std::min((moveSpeed * timeSinceLastFrame / 1000), 3.18);
		}
		lookAtVector.z = -1;
		animation->setEnabled(true);
	}
	if (compareDouble(x, xGoal) && compareDouble(z, zGoal))
	{
		setNewGoal(x, z);
		animation->setEnabled(false);
	}
	move();
}

void IaBomber::getUnbufferedInput(double timeSinceLastFrame, Ogre::Vector3 goal, Ogre::Vector3 position)
{
}

void IaBomber::move()
{
	node->setPosition(node->getPosition() + translateVector);

	Ogre::Vector3 src = node->getOrientation() * Ogre::Vector3::UNIT_X;
	if ((1.0 + src.dotProduct(lookAtVector)) < 0.0001)
	{
		node->yaw(Ogre::Degree(180));
	}
	else
	{
		Ogre::Quaternion quat = src.getRotationTo(lookAtVector);
		node->rotate(quat);
	}
}

void IaBomber::setNewGoal(double x, double z)
{
	if (isADangerousZone(x, z))
	{
		setNewDefensiveGoal(x, z);
	}
	else
	{
		setNewOffensiveGoal(x, z);
	}
}

bool IaBomber::isADangerousZone(double x, double z)
{
	int a = x * 3.2 - .02;
	int b = z * 3.2 - .02;
	return (AppFactory::getSingletonPtr()->mapDanger[b][a] != 0);
}

void IaBomber::setNewDefensiveGoal(double x, double z)
{
}

void IaBomber::setNewOffensiveGoal(double x, double z)
{
}

void IaBomber::tabFill(int value)
{
}

void IaBomber::tabCopy(int ** tab)
{
}
