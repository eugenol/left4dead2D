#include "GameEntity.h"
#include "InputManager.h"
#include "allegro5\allegro_primitives.h"
#include "Player.h"

GameEntity::GameEntity()
{

}
GameEntity::GameEntity(int life, int maxXpos, int maxYpos, int pos_x, int pos_y, int speed_x, int speed_y, int direction, bool active,
	int hitboxRadius, int ID, ALLEGRO_BITMAP *image)
{
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->maxXpos = maxXpos;
	this->maxYpos = maxYpos;
	this->speed_x = speed_x;
	this->speed_y = speed_y;
	this->direction = direction;
	this->active = active;
	this->hitboxRadius = hitboxRadius;
	this->ID = ID;
	this->image = image;
	this->life = life;
}


GameEntity::~GameEntity()
{
	//image connot be destroyed here, as it was not created in this object, it is created in main, and a reference is passed to the object,
	//we do it this way to save memory, otherwise every new enemy will have a new bitmap instead of sharing one.
	//al_destroy_bitmap(image);
}

void GameEntity::draw()
{
	al_draw_bitmap_region(image, currentAnimationFrame*animationFrameWidth, direction*animationFrameHeight, animationFrameWidth, animationFrameHeight, pos_x-animationFrameWidth/2, pos_y-animationFrameHeight/2, 0);
	//al_draw_pixel(pos_x, pos_y, al_map_rgb(255, 0, 0));
}

void GameEntity::UpdateAnimation()
{
	//Generates /Advances Animation
	if (++frameCount>= frameDelay)
	{
		if (++currentAnimationFrame >= maxFrameCount)
			currentAnimationFrame = minFrameCount;
		frameCount = 0;
	}
}


bool GameEntity::CheckCollision(GameEntity *otherObject)
{

	if (this->active == false || otherObject->active == false)
	{
		return false;
	} 
	else if (((pos_x - hitboxWidth / 2) > (otherObject->pos_x + otherObject->hitboxWidth / 2)) ||
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
	
	//select which collision we have
	if ((this->ID == ENEMY) && (otherObject->getID() == ENEMY))//two enemies (bounceback)
	{
		//bounceback code
	}
	else if ((this->ID == ENEMY) && (otherObject->getID() == PROJECTILE)
		|| ((this->ID == PROJECTILE) && (otherObject->getID() == ENEMY)))//enemy and projectile (damage enemy) (destroy projectile)
	{	
		//Enemy & projectile collides
		//To avoid writing code twice, see which is which and use the following pointers to each
		GameEntity *zombie = NULL;
		GameEntity *projectile = NULL;

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
		GameEntity *zombie = NULL;
		GameEntity *player = NULL;

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
		player->takeDamage(5);   //should put zombie->damgeAmount in this bracket, so each zombie type can damage differently
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