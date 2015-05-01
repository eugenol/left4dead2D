#include "GameEntity.h"

GameEntity::GameEntity()
{

}
GameEntity::GameEntity(int life, int maxXpos, int maxYpos, int pos_x, int pos_y, int speed_x, int speed_y, int direction, bool active,
	int hitboxRadius, int ID, ALLEGRO_BITMAP *image)
{
	this->pos_x = pos_x;
	this->pos_y = pos_y;
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

void GameEntity::UpdateAnimation()
{
	//Generates /Advances Animation
	if (++frameCount>= frameDelay)
	{
		if (++currentAnimationFrame >= maxFrameCount)
			currentAnimationFrame = 0;
		frameCount = 0;
	}
}

void GameEntity::UpdatePosition()
{

}