#include "Enemy.h"
#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_image.h"

Player * Enemy::m_player =  NULL;
int Enemy::maxEnemyCount = 0;
Enemy::Enemy(int Enemytype, int pos_x, int pos_y, int speed_x, int speed_y, int direction, ALLEGRO_BITMAP *image,
	bool active, int hitpoints, int regenRate,int damage, int difficulty, ALLEGRO_DISPLAY * display)
	:GameEntity(hitpoints,al_get_display_width(display),al_get_display_height(display), pos_x, pos_y, speed_x, speed_y,
	direction, active, hitboxRadius, ID)
{
	
	this->difficulty = difficulty;
	this->type = Enemytype;
	this->max_hitpoints = hitpoints*(1.0 + difficulty / 2.0);
	this->life = max_hitpoints;
	this->regenRate = regenRate*(1.0 + difficulty / 3.3);
	this->ID = ENEMY;
	this->damage = damage*(1.0 + difficulty / 2.0);
	maxEnemyCount++;

};
Enemy::~Enemy(){
	maxEnemyCount--;
};

bool Enemy::UpdatePosition(){
	//random roaming, will update when player class is made
	/*if within certain range, move directly towards player
	if not in range, move randomly every few ticks, with an added offset of a small number towards
	player location to ensure entities end up near player*/
	return false;
};
void Enemy::setPlayer(Player *player){
	m_player = player;
};
void Enemy::takeDamage(int damage){
	life -= damage;
	if (life < 0)
	{
		active = false;
		runDeathAnimation = true;
	}
		
};

int Enemy::getCount(){
	return maxEnemyCount;
}

int Enemy::getDamagePower(){
	return damage;
}

void Enemy::draw()
{

}
