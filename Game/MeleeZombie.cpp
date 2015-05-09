#include "MeleeZombie.h"
#include "Enemy.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <cmath>
#define PI 3.14159265

MeleeZombie::MeleeZombie(int pos_x, int pos_y, ALLEGRO_BITMAP * image) : Enemy(MELEEZOMBIE, pos_x, pos_y,4,4, NORTH,
	image, true, 87, 2, al_get_current_display()){
	this->old_pos_x = pos_x;
	this->old_pos_y = pos_y;
	//sets direction to always face downwards and towards the middle (until we have a way to point to the player)
	setDirection(direction, 180.0 / PI*atan2((float)((*m_player).GetPos_Y() - pos_y), (float)((*m_player).GetPos_X() - pos_x)));
	maxFrameCount = 12;
	minFrameCount = 4;
	currentAnimationFrame = 0;
	animationFrameHeight = 128;
	animationFrameWidth = 128;
	//to provide a slower, more visible animation
	frameDelay = 4;
};

MeleeZombie::~MeleeZombie(){};

void MeleeZombie::setDirection(int & direction,float angle)
{
	enum Compass{ W, NW, N, NE, E, SE, S, SW };//ordered such that sprite sheet rows correlate correctly to cardinal directions
	//function itself
	if (angle < -135 - 22.5) direction = W;
	else if (angle < -90 - 22.5) direction = NW;
	else if (angle < -45 - 22.5) direction = N;
	else if (angle < 0 - 22.5) direction = NE;
	else if (angle < 45 - 22.5) direction = E;
	else if (angle < 90 - 22.5) direction = SE;
	else if (angle < 135 - 22.5) direction = S;
	else if (angle < 180 - 22.5) direction = SW;
	else direction = W;
}

void MeleeZombie::update(){
	UpdateDirection();
	UpdateAnimation();
};

void MeleeZombie::UpdateDirection(){
	float angle = 180.0 / PI*atan2((float)((*m_player).GetPos_Y()-pos_y), (float)((*m_player).GetPos_X() - pos_x));//angle in degrees of path to target
	pos_x += speed_x*cosf(angle);
	pos_y += speed_y*sinf(angle);
	setDirection(direction,angle);
};

void MeleeZombie::Collided(GameEntity* OtherEntity){//handles all collisions involving zombies
	switch (OtherEntity->getID)
	{
		case PLAYER: //zombie hits player
		(*MeleeZombie::m_player).takeDamage(3);
		break;
		
		case ENEMY://zombies hit each other
		//bounceback code	
		break;
	};
};