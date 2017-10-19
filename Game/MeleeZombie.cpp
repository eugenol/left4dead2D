#include "MeleeZombie.h"
#include "Enemy.h"
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include <cmath>
#include <allegro5\allegro_primitives.h>

#define PI 3.14159265

MeleeZombie::MeleeZombie(int pos_x, int pos_y,int difficulty, ALLEGRO_BITMAP * image, ALLEGRO_BITMAP *zombieDeathAnimationSpriteSheet) :
Enemy(MELEEZOMBIE, pos_x, pos_y, 2 + rand() % 3, 2 + rand() % 3, NORTH,
	image, true, 87, 5,4,difficulty)
{
	this->old_pos_x = pos_x;
	this->old_pos_y = pos_y;
	//sets direction to always face downwards and towards the middle (until we have a way to point to the player)
	if (m_player)
		setDirection(180.0 / PI*atan2((float)((*m_player).GetPos_Y() - pos_y), (float)((*m_player).GetPos_X() - pos_x)));


	SpriteSheetProperties properties;
	//properties for zombie sprite sheet
	properties.m_maxFrameCount = 8;
	properties.m_minFrameCount = 0;
	properties.m_currentAnimationFrame = 0;
	properties.m_animationFrameHeight = 128;
	properties.m_animationFrameWidth = 128;
	properties.m_frameCount = 0;
	//to provide a slower, more visible animation
	properties.m_frameDelay = 5;

	m_zombieSprite = new CSprite(image, properties);
	m_currentSprite = m_zombieSprite;

	//Death animation spritesheet
	properties.m_currentAnimationFrame = 0;
	properties.m_maxFrameCount = 7;
	properties.m_frameDelay = 5;
	properties.m_minFrameCount = 0;
	properties.m_frameCount = 0;

	m_zombieDeathSprite = new CSprite(zombieDeathAnimationSpriteSheet, properties);


	hitboxWidth = 36;
	hitboxHeight = 60;
	//Death Animation Variables
	//Death Animation Variables
	runDeathAnimation = false;
}

MeleeZombie::~MeleeZombie(){
	if (m_player)
		(*m_player).increaseScore(1);

	if(m_zombieSprite)
	{
		delete m_zombieSprite;
	}

	if (m_zombieDeathSprite)
	{
		delete m_zombieDeathSprite;
	}

	m_currentSprite = nullptr;

}

void MeleeZombie::setDirection(float angle)
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

void MeleeZombie::Update(){
	if (m_player)
	{
		if (active)
		{
			UpdateDirection();
			//UpdateAnimation();
			if (++regenCounter >= 60){
				life += regenRate;
				if (life > max_hitpoints){
					life = max_hitpoints;
				}
				regenCounter = 0;
			}
		}
		else if ((!active) && isAlive && runDeathAnimation)
		{
			runDeathAnimation = false;
			m_currentSprite = m_zombieDeathSprite;
		}
		m_currentSprite->DoLogic();
		if ((!active) && (m_currentSprite->GetCurrentAnimationFrame() == (m_currentSprite->GetMaxFrameCount() - 1))) isAlive = false;
	}
		
}

void MeleeZombie::UpdateDirection(){
	float playerVector_X = (*m_player).GetPos_X() - pos_x;
	float playerVector_Y = (*m_player).GetPos_Y() - pos_y;
	float vectorMagnitude = sqrtf(playerVector_X*playerVector_X + playerVector_Y*playerVector_Y);
	if (vectorMagnitude >3){
		setDirection(180.0 / PI * atan2(playerVector_Y, playerVector_X));
		pos_x += speed_x*(playerVector_X / vectorMagnitude);
		pos_y += speed_y*(playerVector_Y / vectorMagnitude);
		if (pos_x - hitboxWidth / 2 < 0)
			pos_x = hitboxWidth / 2;
		if (pos_x + hitboxWidth / 2 > 800)
			pos_x = 800-hitboxWidth/2;
		if (pos_y - hitboxHeight / 2 < 0)
			pos_y = hitboxHeight / 2;
		if (pos_y + hitboxHeight / 2 > 600)
			pos_y = 600-hitboxHeight / 2;
	};
};

void MeleeZombie::Draw(){
	//draw a healthbar
	if(active)
	{
		//draw red background
		al_draw_filled_rectangle(pos_x - 11, pos_y - hitboxHeight + 30, pos_x + 11,
			pos_y - hitboxHeight + 23, al_map_rgba(255, 0, 0, 0));
		//draw green bar
		al_draw_filled_rectangle(pos_x - 10, pos_y - hitboxHeight + 29,
			pos_x - 10 + life * 20 / max_hitpoints, pos_y - hitboxHeight + 24,
			al_map_rgba(0, 255, 0, 120));
	}
	//draws the zombie sprite
	m_currentSprite->Draw(CTwoDVector(pos_x, pos_y), direction);
	if (difficulty != EASY)
	{
		//draw overlay
		m_currentSprite->Draw(al_map_rgba(0, 255, 0, difficulty * 60), CTwoDVector(pos_x, pos_y), direction);
	}
}