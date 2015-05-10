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
	al_draw_bitmap_region(image, currentAnimationFrame*animationFrameWidth, direction*animationFrameHeight, animationFrameWidth, animationFrameHeight, pos_x, pos_y, 0);
	al_draw_pixel(pos_x, pos_y, al_map_rgb(255, 0, 0));
}
void GameEntity::update()
{
	if (UpdatePosition())
	{
		UpdateDirection();
		UpdateAnimation();
	}
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
	int obj_1_cent_x = pos_x + animationFrameWidth / 2;
	int obj_1_cent_y = pos_y + animationFrameHeight / 2;
	int obj_2_cent_x = otherObject->pos_x + otherObject->animationFrameWidth / 2;
	int obj_2_cent_y = otherObject->pos_y + otherObject->animationFrameHeight / 2;



	if ((pos_x > otherObject->pos_x + otherObject->animationFrameWidth) ||
		(pos_y > otherObject->pos_y + otherObject->animationFrameHeight) ||
		(otherObject->pos_x > pos_x + animationFrameWidth) ||
		(otherObject->pos_y > pos_y + animationFrameHeight))
	{
		return false;
	}
	return true;
}

void GameEntity::Collided(GameEntity *otherObject)
{
	if ((ID == PROJECTILE && otherObject->ID == ENEMY) || (ID == ENEMY && otherObject->ID == PROJECTILE))
	{
		isAlive = false;
		otherObject->isAlive = false;
	}
		

}
