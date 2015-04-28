#include "GameEntity.h"


GameEntity::GameEntity(int pos_x, int pos_y, int speed_x, int speed_y, int direction_x, int direction_y, bool active,
	int hitboxRadius, int ID, ALLEGRO_BITMAP *image)
{
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	this->speed_x = speed_x;
	this->speed_y = speed_y;
	this->direction_x = direction_x;
	this->direction_y = direction_y;
	this->active = active;
	this->hitboxRadius = hitboxRadius;
	this->ID = ID;
	this->image = image;
}


GameEntity::~GameEntity()
{
}

void GameEntity::draw()
{
	al_draw_bitmap_region(image, animationFrame*animationFrameWidth, direction*animationFrameHeight, animationFrameWidth, animationFrameHeight, pos_x, pos_y, 0);
}

void GameEntity::UpdateAnimation()
{
	if (++frameCount >= frameDelay)
	{
		if (++animationFrame >= maxFrame)
			animationFrame = 0;
		frameCount = 0;
	}
}

void GameEntity::UpdatePosition(int &verticleMove, int &horizontalMove)
{
	pos_x += horizontalMove*speed_x;
	pos_y += verticleMove*speed_y;
}
void GameEntity::update(int horizontalMove, int verticleMove, int damage, int dir)
{
	direction = dir;
	UpdatePosition(horizontalMove, verticleMove);
	UpdateAnimation();
}