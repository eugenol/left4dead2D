#include "MeleeZombie.h"
#include "Enemy.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <math.h>
#define PI 3.14159265

MeleeZombie::MeleeZombie(int pos_x, int pos_y, ALLEGRO_BITMAP * image) : Enemy(MELEEZOMBIE, pos_x, pos_y, defaultSpeed, defaultSpeed, NORTH,
	image, true, defaultHitpoints, defaultRegen, al_get_current_display()){
	this->old_pos_x = pos_x;
	this->old_pos_y = pos_y;
	//sets direction to always face downwards and towards the middle (until we have a way to point to the player)
	setDirection(direction, pos_x, pos_y, al_get_display_width(al_get_current_display()) / 2, al_get_display_height(al_get_current_display()));
	maxFrameCount = 12;
	minFrameCount = 4;
	currentAnimationFrame = 0;
	animationFrameHeight = 128;
	animationFrameWidth = 128;
	//to provide a slower, more visible animation
	frameDelay = 4;
};
MeleeZombie::~MeleeZombie(){};
void MeleeZombie::setDirection(int & direction, int pos_x, int pos_y, int dest_x, int dest_y)
{
	enum Compass{ W, NW, N, NE, E, SE, S, SW };//ordered such that sprite sheet rows correlate correctly to cardinal directions
	//function itself
	float angle =180.0/PI*atan2((float)(dest_y - pos_y),(float)(dest_x - pos_x));//angle in degrees of path to target
	if (angle < -135 - 22.5) direction = W;
	else if (angle < -90 - 22.5) direction = SW;
	else if (angle < -45 - 22.5) direction = S;
	else if (angle < 0 - 22.5) direction = SE;
	else if (angle < 45 - 22.5) direction = E;
	else if (angle < 90 - 22.5) direction = NE;
	else if (angle < 135 - 22.5) direction = N;
	else if (angle < 180 - 22.5) direction = NW;
	else direction = W;
}
void MeleeZombie::update(){
	UpdateDirection();
	UpdateAnimation();
};

void MeleeZombie::UpdateDirection(){

};
//Enemy(int type, int pos_x, int pos_y, int speed_x, int speed_y, int direction,
//	ALLEGRO_BITMAP *image, bool active, int hitpoints, int armorType,
//	int regenRate, ALLEGRO_DISPLAY * display);