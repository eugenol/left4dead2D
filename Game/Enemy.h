#ifndef ENEMY_H
#define ENEMY_H

#include "GameEntity.h"
#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_image.h"
enum ARMOR{ NONE };
enum TYPES{ MELEEZOMBIE };
class Enemy :public GameEntity{//class contains all enemies
private:
	static int count;//number of enemy objects alive
protected:
	int difficulty = 1;
	int hitboxRadius_x;
	int hitboxRadius_y;
	int type;//type of enemy
	int max_hitpoints;//full life hitpoint number
	int hitpoints;
	int armortype;//to allow resistances to certain weapons
	int regenRate;
public:
	Enemy(int type, int pos_x, int pos_y,int speed_x,int speed_y,int direction,
		ALLEGRO_BITMAP *image, bool active, int hitpoints, int armorType,
		int regenRate,ALLEGRO_DISPLAY * display);
	~Enemy();
	void chasePlayer();
	void update();
	bool UpdatePosition();
	int getCount();
};
#endif
/*GameEntity(int pos_x, int pos_y, int speed_x, int speed_y, int direction_x,
int direction_y, bool active,int hitboxRadius, int ID, ALLEGRO_BITMAP *image);*/


/*CREDITS:
Sprite sheets:
http://opengameart.org/content/zombie-sprites 
*/