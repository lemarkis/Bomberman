#include "HumanBomber.hpp"

HumanBomber::HumanBomber(Ogre::SceneManager * pSceneMgr, Collision::CollisionTools * pCollisionTools, Ogre::String const & pName, Ogre::Vector3 const pPosition): Bomber(pCollisionTools, pName)
{
	entity = pSceneMgr->createEntity(name, "Lego_perso.mesh");
	entity->setCastShadows(true);
	node = pSceneMgr->getRootSceneNode()->createChildSceneNode(name, pPosition);
	node->setScale(.65, .65, .65);
	node->attachObject(entity);
	animation = entity->getAnimationState("my_animation");
	animation->setLoop(true);

	moveSpeed = 0.12f;
}

HumanBomber::~HumanBomber()
{
}

bool HumanBomber::keyPressed(const OIS::KeyEvent &keyEventRef)
{
	return true;
}

bool HumanBomber::keyReleased(const OIS::KeyEvent &keyEventRef)
{
	if (keyEventRef.key == OIS::KC_LEFT ||
		keyEventRef.key == OIS::KC_RIGHT ||
		keyEventRef.key == OIS::KC_UP ||
		keyEventRef.key == OIS::KC_DOWN)
	{
		animation->setEnabled(false);
	}
	return true;
}

bool HumanBomber::mouseMoved(const OIS::MouseEvent &arg)
{
	return true;
}

bool HumanBomber::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return true;
}

bool HumanBomber::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return true;
}

void HumanBomber::update(double timeSinceLastFrame)
{
	animation->addTime(timeSinceLastFrame / 400);

	translateVector = Ogre::Vector3::ZERO;
	lookAtVector = Ogre::Vector3::ZERO;

	getUnbufferedInput();
	move();
}

bool HumanBomber::checkCollision(Collision::CollisionTools * pCollisionTools)
{
	return false;
}

void HumanBomber::getUnbufferedInput()
{
	OIS::Keyboard * lKeyboard = OgreFramework::getSingletonPtr()->m_pKeyboard;
	if (lKeyboard->isKeyDown(OIS::KC_LEFT))
	{
		if (!checkCollision(collisionTools))
		{
			translateVector.x = -moveSpeed;
		}
		lookAtVector.x = -1;
		animation->setEnabled(true);
	}

	if (lKeyboard->isKeyDown(OIS::KC_RIGHT))
	{
		if (!checkCollision(collisionTools))
		{
			translateVector.x = moveSpeed;
		}
		lookAtVector.x = 1;
		animation->setEnabled(true);
	}

	if (lKeyboard->isKeyDown(OIS::KC_UP))
	{
		if (!checkCollision(collisionTools))
		{
			translateVector.z = -moveSpeed;
		}
		lookAtVector.z = -1;
		animation->setEnabled(true);
	}

	if (lKeyboard->isKeyDown(OIS::KC_DOWN))
	{
		if (!checkCollision(collisionTools))
		{
			translateVector.z = moveSpeed;
		}
		lookAtVector.z = 1;
		animation->setEnabled(true);
	}
}

void HumanBomber::move()
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
