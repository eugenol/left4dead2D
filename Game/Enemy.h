#ifndef ENEMY_H
#define ENEMY_H

#include "GameEntity.h"
#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_image.h"


class Enemy :public GameEntity{
private:
	static int count;
	int rad_x = 15;
	int rad_y = 15;
	int type;
	int hitpoints;//hitpoints set by difficulty
	int armortype;//to allow resistances to certain weapons
	int regenRate;//rate is set by difficulty
public:
	Enemy(int ID,int type, int pos_x, int pos_y,int speed_x,int speed_y,int direction_x,int direction_y,
		int hitboxRadius, ALLEGRO_BITMAP *image, bool active, int hitpoints, int armorType, int regenRate);
	~Enemy();
	void chasePlayer();
	void draw();
	void update();
	int getCount();
};

#endif
/*GameEntity(int pos_x, int pos_y, int speed_x, int speed_y, int direction_x,
int direction_y, bool active,int hitboxRadius, int ID, ALLEGRO_BITMAP *image);*/