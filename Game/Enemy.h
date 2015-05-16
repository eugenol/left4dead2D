#ifndef ENEMY_H
#define ENEMY_H

#include "GameEntity.h"
#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_image.h"
#include "Player.h"
enum TYPES{ MELEEZOMBIE };
class Enemy :public GameEntity{//class contains all enemies
private:
protected:
	int difficulty = 1;
	int type;//type of enemy
	int max_hitpoints;//full life hitpoint number
	int regenRate;//hitpoints regen rate per a second
	int regenCounter;
	static Player *m_player;//pointer to the player, for creating AI
	static int maxEnemyCount;

	//Death Animation Variables
	bool runDeathAnimation;
public:
	Enemy(int type, int pos_x, int pos_y,int speed_x,int speed_y,int direction,
		ALLEGRO_BITMAP *image, bool active, int hitpoints,
		int regenRate,ALLEGRO_DISPLAY * display);
	~Enemy();
	void takeDamage(int damage);
	bool UpdatePosition();
	int static getCount();
	static void setPlayer(Player *player);//sets player in enemy class
};
#endif
/*GameEntity(int pos_x, int pos_y, int speed_x, int speed_y, int direction_x,
int direction_y, bool active,int hitboxRadius, int ID, ALLEGRO_BITMAP *image);*/


/*CREDITS:
Sprite sheets:
http://opengameart.org/content/zombie-sprites 
*/