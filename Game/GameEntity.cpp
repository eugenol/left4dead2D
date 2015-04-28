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
	al_destroy_bitmap(image);
}
