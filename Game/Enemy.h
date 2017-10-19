#ifndef ENEMY_H
#define ENEMY_H

#include "GameEntity.h"
#include "allegro5\allegro_primitives.h"
#include "Player.h"

enum TYPES{ MELEEZOMBIE };
class Enemy :public GameEntity{//class contains all enemies
public:
	Enemy(int Enemytype, CTwoDVector position, int speed_x, int speed_y, int direction,
		ALLEGRO_BITMAP* image, bool active, int hitpoints,
		int regenRate, int damage, int difficulty);
	~Enemy();

	void takeDamage(int damage);
	bool UpdatePosition();
	int static getCount();
	static void setPlayer(Player *player);//sets player in enemy class
	int getDamagePower();
	void Draw();

protected:
	int difficulty;
	int type;//type of enemy
	int max_hitpoints;//full life hitpoint number
	int regenRate;//hitpoints regen rate per a second
	int regenCounter;
	int damage;
	static Player *m_player;//pointer to the player, for creating AI
	static int maxEnemyCount;

	//Death Animation Variables
	bool runDeathAnimation;

};
#endif

/*CREDITS:
Sprite sheets:
http://opengameart.org/content/zombie-sprites 
*/