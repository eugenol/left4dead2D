#include "Enemy.h"
#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_image.h"

Enemy::Enemy(int Enemytype, int pos_x, int pos_y, int speed_x, int speed_y, int direction, ALLEGRO_BITMAP *image,
	bool active, int hitpoints, int regenRate, ALLEGRO_DISPLAY * display)
	:GameEntity(hitpoints,al_get_display_width(display),al_get_display_height(display), pos_x, pos_y, speed_x, speed_y,
	direction, active, hitboxRadius, ID, image){
	
	this->type = Enemytype;
	this->hitpoints = hitpoints;
	this->max_hitpoints = hitpoints;
	this->regenRate = regenRate;
	this->ID = ENEMY;

};
Enemy::~Enemy(){
};

void Enemy::update(){
	if (UpdatePosition()){
		UpdateAnimation();
	}
	hitpoints += regenRate;
	if (hitpoints > max_hitpoints){
		hitpoints = max_hitpoints;
	}
};
bool Enemy::UpdatePosition(){
	//random roaming, will update when player class is made
	/*if within certain range, move directly towards player
	if not in range, move randomly every few ticks, with an added offset of a small number towards
	player location to ensure entities end up near player*/
	return false;
};