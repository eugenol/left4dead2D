#include "Enemy.h"
#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_image.h"

Player * Enemy::m_player =  NULL;

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
void Enemy::setPlayer(Player *player){
	m_player = player;
};
void Enemy::takeDamage(int damage){
	life -= damage;
	if (life < 0)
		isAlive = false;
};
void Enemy::Collided(GameEntity* OtherEntity){//handles all collisions involving zombies

	//select which collision we have
	switch (OtherEntity->getID)
	{
	case PLAYER://collides with player
		//select damage amount to be done to player
			int damage;
			switch (this->type)
			{
			case MELEEZOMBIE:
				damage = 3;
				break;
			default:
				damage = 0;
				break;
			}
		//deal damage to player
		(*Enemy::m_player).takeDamage(damage);
		break;
	case ENEMY://zombies hit each other
		//bounceback code	
		break;
	};
};