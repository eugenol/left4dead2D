#include "GameEntity.h"
#include <cmath>
#include "Common.h"

GameEntity::GameEntity()
{

}
GameEntity::GameEntity(int life, int pos_x, int pos_y, int speed_x, int speed_y, int direction, bool active,
	int hitboxRadius, int ID)
{
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->maxXpos = DISPLAY_WIDTH;
	this->maxYpos = DISPLAY_HEIGHT;
	this->speed_x = speed_x;
	this->speed_y = speed_y;
	this->direction = direction;
	this->active = active;
	this->hitboxRadius = hitboxRadius;
	this->ID = ID;
	this->life = life;
	collided = false;
}


GameEntity::~GameEntity()
{
	//image connot be destroyed here, as it was not created in this object, it is created in main, and a reference is passed to the object,
	//we do it this way to save memory, otherwise every new enemy will have a new bitmap instead of sharing one.
	//al_destroy_bitmap(image);
}


bool GameEntity::CheckCollision(GameEntity *otherObject)
{

	if (this->active == false || otherObject->active == false)
	{
		return false;
	}
	
	if (((pos_x - hitboxWidth / 2) > (otherObject->pos_x + otherObject->hitboxWidth / 2)) ||
		((pos_y - hitboxHeight / 2)> (otherObject->pos_y + otherObject->hitboxHeight / 2)) ||
		((otherObject->pos_x - otherObject->hitboxWidth / 2)>(pos_x + hitboxWidth / 2)) ||
		((otherObject->pos_y - otherObject->hitboxHeight / 2)> (pos_y + hitboxHeight / 2)))
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
		float diffx = pos_x - otherObject->pos_x;
		float diffy = pos_y - otherObject->pos_y;
		float vertdist = otherObject->hitboxWidth / 2 + hitboxWidth / 2;
		float hordist = otherObject->hitboxHeight / 2 + hitboxHeight / 2;
		vertdist /= 2;
		hordist /= 2;

		if (pos_x < otherObject->pos_x)
		{
			while (abs(diffx) < vertdist)
			{
				if (pos_x > hitboxWidth/2)
					pos_x--;
				if (otherObject->pos_x < 800 - otherObject->hitboxWidth / 2)
					otherObject->pos_x++;
				diffx = pos_x - otherObject->pos_x;
			}
		}
		if (pos_x > otherObject->pos_x)
		{
			while (abs(diffx) < vertdist)
			{
				if (pos_x < 800 - hitboxWidth/2)
					pos_x++;
				if (otherObject->pos_x > otherObject->hitboxWidth / 2)
					otherObject->pos_x--;
				diffx = pos_x - otherObject->pos_x;
			}
		}
		if (pos_y < otherObject->pos_y)
		{
			while (abs(diffy) < hordist)
			{
				if (pos_y > hitboxHeight / 2)
					pos_y--;
				if (otherObject->pos_y < 600 - otherObject->hitboxHeight / 2)
					otherObject->pos_y++;
				diffy = pos_y - otherObject->pos_y;
			}
		}
		if (pos_y > otherObject->pos_y)
		{
			while (abs(diffy) < hordist)
			{
				if (pos_y < 600 - hitboxHeight / 2)
					pos_y++;
				if (otherObject->pos_y > otherObject->hitboxHeight / 2)
					otherObject->pos_y--;
				diffy = pos_y - otherObject->pos_y;
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