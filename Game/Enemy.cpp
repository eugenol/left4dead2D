#include "Enemy.h"
#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_image.h"

Player * Enemy::m_player =  NULL;
int Enemy::maxEnemyCount = 0;
Enemy::Enemy(int Enemytype, int pos_x, int pos_y, int speed_x, int speed_y, int direction, ALLEGRO_BITMAP *image,
	bool active, int hitpoints, int regenRate, ALLEGRO_DISPLAY * display, ALLEGRO_BITMAP *death_animation_spriteSheet)
	:GameEntity(hitpoints,al_get_display_width(display),al_get_display_height(display), pos_x, pos_y, speed_x, speed_y,
	direction, active, hitboxRadius, ID, image){
	
	this->type = Enemytype;
	this->hitpoints = hitpoints;
	this->max_hitpoints = hitpoints;
	this->regenRate = regenRate;
	this->ID = ENEMY;
	maxEnemyCount++;

	this->deathAnimation = death_animation_spriteSheet;
};
Enemy::~Enemy(){
	maxEnemyCount--;
};

void Enemy::update(){
	if (active)
	{
		if (UpdatePosition()){
			UpdateAnimation();
		}
		hitpoints += regenRate;
		if (hitpoints > max_hitpoints){
			hitpoints = max_hitpoints;
		}
	}
	else
	{
		image = deathAnimation;
		maxFrameCount = 7;
		minFrameCount = 0;
	}

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
		active = false;
};

int Enemy::getCount(){
	return maxEnemyCount;
}