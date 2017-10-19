#include "GameEntity.h"
#include <cmath>
#include "Common.h"

GameEntity::GameEntity()
{

}
GameEntity::GameEntity(int life, int pos_x, int pos_y, int speed_x, int speed_y, int direction, bool active,
	int hitboxRadius, int ID)
	:
	m_position( pos_x, pos_y ),
	speed_x( speed_x ),
	speed_y( speed_y ),
	direction( direction ),
	active( active ),
	hitboxRadius( hitboxRadius ),
	ID( ID ),
	life( life )
{
	collided = false;
}


GameEntity::~GameEntity()
{
}


bool GameEntity::SameRegion(GameEntity *otherObject)
{

	if (this->active == false || otherObject->active == false)
	{
		return false;
	}

	if (((m_position.m_x - 100) > (otherObject->m_position.m_x + 100)) ||
		  ((m_position.m_y - 100) > (otherObject->m_position.m_y + 100)) ||
		  ((otherObject->m_position.m_x - 100) >(m_position.m_x + 100)) ||
		  ((otherObject->m_position.m_y - 100) > (m_position.m_y + 100)))
	{
		return false;
	}
	return true;
}

bool GameEntity::CheckCollision(GameEntity *otherObject)
{

	if (this->active == false || otherObject->active == false)
	{
		return false;
	}
	
	if (((m_position.m_x - hitboxWidth / 2) > (otherObject->m_position.m_x + otherObject->hitboxWidth / 2)) ||
		((m_position.m_y - hitboxHeight / 2)> (otherObject->m_position.m_y + otherObject->hitboxHeight / 2)) ||
		((otherObject->m_position.m_x - otherObject->hitboxWidth / 2)>(m_position.m_x + hitboxWidth / 2)) ||
		((otherObject->m_position.m_y - otherObject->hitboxHeight / 2)> (m_position.m_y + hitboxHeight / 2)))
	{
		return false;
	}
	return true;
}

void GameEntity::Collided(GameEntity *otherObject)
{	
	// Collision between zombies or player and zombie
	// If the objects intersect, move them back until they dont.
	if ((this->getID() == PLAYER || this->getID() == ENEMY) && (otherObject->getID() == PLAYER || otherObject->getID() == ENEMY))
	{
		float diffx = m_position.m_x - otherObject->m_position.m_x;
		float diffy = m_position.m_y - otherObject->m_position.m_y;
		float vertdist = otherObject->hitboxWidth / 2 + hitboxWidth / 2;
		float hordist = otherObject->hitboxHeight / 2 + hitboxHeight / 2;
		vertdist /= 2;
		hordist /= 2;

		if (m_position.m_x < otherObject->m_position.m_x)
		{
			while (abs(diffx) < vertdist)
			{
				if (m_position.m_x > hitboxWidth/2)
					m_position.m_x--;
				if (otherObject->m_position.m_x < maxXpos - otherObject->hitboxWidth / 2)
					otherObject->m_position.m_x++;
				diffx = m_position.m_x - otherObject->m_position.m_x;
			}
		}
		if (m_position.m_x > otherObject->m_position.m_x)
		{
			while (abs(diffx) < vertdist)
			{
				if (m_position.m_x < maxXpos - hitboxWidth/2)
					m_position.m_x++;
				if (otherObject->m_position.m_x > otherObject->hitboxWidth / 2)
					otherObject->m_position.m_x--;
				diffx = m_position.m_x - otherObject->m_position.m_x;
			}
		}
		if (m_position.m_y < otherObject->m_position.m_y)
		{
			while (abs(diffy) < hordist)
			{
				if (m_position.m_y > hitboxHeight / 2)
					m_position.m_y--;
				if (otherObject->m_position.m_y < maxYpos - otherObject->hitboxHeight / 2)
					otherObject->m_position.m_y++;
				diffy = m_position.m_y - otherObject->m_position.m_y;
			}
		}
		if (m_position.m_y > otherObject->m_position.m_y)
		{
			while (abs(diffy) < hordist)
			{
				if (m_position.m_y < maxYpos - hitboxHeight / 2)
					m_position.m_y++;
				if (otherObject->m_position.m_y > otherObject->hitboxHeight / 2)
					otherObject->m_position.m_y--;
				diffy = m_position.m_y - otherObject->m_position.m_y;
			}
		}
	}
	
	//select which collision we have
	if ((this->getID() == ENEMY) && (otherObject->getID() == ENEMY))//two enemies (bounceback)
	{
		//Code for zombies colliding
	}
	else if ((this->ID == ENEMY) && (otherObject->getID() == PROJECTILE)
		|| ((this->ID == PROJECTILE) && (otherObject->getID() == ENEMY)))//enemy and projectile (damage enemy) (destroy projectile)
	{	
		//Enemy & projectile collides
		//To avoid writing code twice, see which is which and use the following pointers to each
		GameEntity *zombie = nullptr;
		GameEntity *projectile = nullptr;

		if (this->ID == PROJECTILE)
		{
			// Code if this object is projectile and other object is zombie
			projectile = this;
			zombie = otherObject;
		}
		else if (otherObject->getID() == PROJECTILE)
		{
			 // otherObject is projectile, and this is zombie
			projectile = otherObject;
			zombie = this;
		}

		// Now code only has to be here once... use projectile and zombie pointers.
		//Projectile Specific Code
		projectile->active = false;
		if (!(projectile->collided)) projectile->collided = true;
		//Zombie Specific Code
		zombie->takeDamage(projectile->getDamagePower());
		
	} 
	else if ((this->ID == ENEMY) && (otherObject->getID() == PLAYER)
		|| ((this->ID == PLAYER) && (otherObject->getID() == ENEMY)))//enemy and player (damage player)
	{	
		//Enemy & player collides
		//To avoid writing code twice, see which is which and use the following pointers to each
		GameEntity *zombie = nullptr;
		GameEntity *player = nullptr;

		if (this->ID == PLAYER)
		{
			// Code if this object is projectile and other object is zombie
			player = this;
			zombie = otherObject;
		}
		else if (otherObject->getID() == PLAYER)
		{
			// otherObject is projectile, and this is zombie
			player = otherObject;
			zombie = this;
		}

		// Now code only has to be here once... use player and zombie pointers.
		//Player Specific Code
		player->takeDamage((*zombie).getDamagePower()); //should put zombie->damgeAmount in this bracket, so each zombie type can damage differently
		if (!(player->collided)) player->collided = true;
		
		//Zombie Specific Code Here

	}
}

int GameEntity::getID(){
	return ID;
}

//Virtual Functions for Collisions
void GameEntity::takeDamage(int damageAmount)
{

}
int GameEntity::getDamagePower()
{
	return 0;
}