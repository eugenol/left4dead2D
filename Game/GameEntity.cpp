#include "GameEntity.h"
#include "InputManager.h"
#include "allegro5\allegro_primitives.h"

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
	if ( (this->ID == ENEMY) && (otherObject->getID() == ENEMY))//two enemies (bounceback)
		;//bounceback code
	if ( (this->ID == ENEMY) && (otherObject->getID() == PROJECTILE)
		|| ((this->ID == PROJECTILE) && (otherObject->getID == ENEMY)))//enemy and projectile (damage enemy)
		;//projectile hitting enemy code
	if ((this->ID == ENEMY) && (otherObject->getID() == PLAYER)
		|| ((this->ID == PLAYER) && (otherObject->getID == ENEMY)))//enemy and player (damage player)
		;//enemy hitting player
}

int GameEntity::getID(){
	return ID;
}
