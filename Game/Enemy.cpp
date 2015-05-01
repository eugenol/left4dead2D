#include "Enemy.h"
#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_image.h"

Enemy::Enemy(int ID, int type, int pos_x, int pos_y, int speed_x, int speed_y, int direction_x, int direction_y,
	int hitboxRadius, ALLEGRO_BITMAP *image, bool active, int hitpoints, int armorType, int regenRate)
	:GameEntity(pos_x, pos_y, speed_x, speed_y, direction_x, direction_y, active, hitboxRadius, ID, image){
	
	this->type = type;
	this->hitpoints = hitpoints;
	this->armortype = armortype;
	this->regenRate = regenRate;

	count++;//increments number of enemy objects
};
Enemy::~Enemy(){
	count--;
};
void Enemy::chasePlayer(){
	//does nothing right now
}

void Enemy::draw(){
	al_draw_filled_rectangle(pos_x-rad_x,pos_y-rad_y,pos_x+rad_x,pos_y+rad_y,al_map_rgb(255,0,0));
};
void Enemy::update(){
	//random roaming, will update when player class is made
	/*if within certain range, move directly towards player
	if not in range, move randomly every few ticks, with an added offset of a small number towards
	player location to ensure entities end up near player*/

};
int Enemy::getCount(){
	return count;
}
int Enemy::count = 0;