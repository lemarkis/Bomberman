#include <random>
#include "IaBomber.hpp"

IaBomber::IaBomber(Ogre::SceneManager * pSceneMgr, Collision::CollisionTools * pCollisionTools, Ogre::String const & pName, Ogre::Vector3 const pPosition) : Bomber(pCollisionTools, pName)
{
	entity = pSceneMgr->createEntity(name, "Lego_perso.mesh");
	entity->setCastShadows(true);
	node = pSceneMgr->getRootSceneNode()->createChildSceneNode(name, pPosition);
	node->setScale(.65, .65, .65);
	node->attachObject(entity);
	animation = entity->getAnimationState("my_animation");
	animation->setLoop(true);

	moveSpeed = 12.f;
}

IaBomber::~IaBomber()
{
}

bool IaBomber::keyPressed(const OIS::KeyEvent &keyEventRef)
{
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

	AppFactory *Factory = AppFactory::getSingletonPtr();
	Ogre::Vector3 position;

	position = node->getPosition();
	int x_pos;
	x_pos = ((position.x) + 0.02) / 3.2;
	int z_pos;
	z_pos = ((position.z) + 0.02) / 3.2;
	// // // // //
	// getPos et debug
	Ogre::String str = Ogre::String(std::to_string(position.x)).append(", ").append(std::to_string(position.y)).append(", ").append(std::to_string(position.z));
	OgreFramework::getSingletonPtr()->m_pLog->logMessage(str);
	int x_dif = 0;
	int z_dif = 0;
	// objectif
	int x_goal = x_pos + x_dif;
	int z_goal = z_pos + z_dif;
	Ogre::Vector3 goal(((x_goal * 3.2) - 0.02), 0, ((z_goal * 3.2) - 0.02));
	// // // // //
	getUnbufferedInput(timeSinceLastFrame, goal, position);
	// // // // //
	if (x_goal == x_pos && z_goal == z_pos)
		set_new_goal(x_goal, z_goal, x_pos, z_pos);
	move();
}

void IaBomber::getUnbufferedInput(double timeSinceLastFrame, Ogre::Vector3 goal, Ogre::Vector3 position)
{	
	if (position.x < goal.x)
	{	
		translateVector.x = -(moveSpeed * timeSinceLastFrame / 1000);
		lookAtVector.x = -1;
		animation->setEnabled(true);
	}
	if (position.x > goal.x)
	{
		translateVector.x = (moveSpeed * timeSinceLastFrame / 1000);
		lookAtVector.x = 1;
		animation->setEnabled(true);
	}
	if (position.z < goal.z)
	{
		translateVector.z = -(moveSpeed * timeSinceLastFrame / 1000);
		lookAtVector.z = -1;
		animation->setEnabled(true);
	}
	if (position.z > goal.z)
	{
		translateVector.z = (moveSpeed * timeSinceLastFrame / 1000);
		lookAtVector.z = 1;
		animation->setEnabled(true);
	}

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

void IaBomber::set_new_goal(int x_goal, int z_goal, int x_pos, int z_pos)
{
	if (is_a_dangerous_zone(x_pos, z_pos))
		set_new_goal_offense((short)x_goal, (short)z_goal, x_pos, z_pos);
	else
		set_new_goal_defense();
}

bool IaBomber::is_a_dangerous_zone(int x_pos, int z_pos)
{
	return (false);
}

void IaBomber::set_new_goal_offense(short &xg, short &zg, short x, short z)
{
	std::default_random_engine a;
	std::uniform_int_distribution<int> f(0, 4);
	int dice_roll = f(a);

	char dir_x[] = {-1,0,1,0};
	char dir_y[] = {0,-1,0,1};

	if (not_dangerous(x, z, dir_x[n], dir_y[n]) && not_a_solid_block(x, z, dir_x[n], dir_y[n]))
	{
		std::uniform_int_distribution<int> f2(0, 7);
		dice_roll = f2(a);
		xg = x + dir_x[n] * 3.18;
		zg = y + dir_y[n] * 3.18;
		if (dice_roll == 0)
			try_to_put_bomb();
	}
}

void IaBomber::set_new_goal_defense()
{

}

bool IaBomber::not_dangerous(int x, int z, char xg, char zg)
{

}

bool IaBomber::not_a_solid_block(int x, int z, char xg, char zg)
{

}

void IaBomber::try_to_put_bomb()
{

}