#ifndef ENEMY_H
#define ENEMY_H

#include "GameEntity.h"
#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_image.h"

class Enemy :public GameEntity{
private:
	int type;
	int hitpoints;//hitpoints set by difficulty
	int armortype;//to allow resistances to certain weapons
	int regenRate;//rate is set by difficulty
public:
	Enemy(int type, int pos_x, int pos_y, int hitpoints, int armortype, int regenRate);
	void chasePlayer();
};

#endif
/*GameEntity(int pos_x, int pos_y, int speed_x, int speed_y, int direction_y, int direction_x, bool active,
int hitboxRadius, int ID, ALLEGRO_BITMAP *image);*/