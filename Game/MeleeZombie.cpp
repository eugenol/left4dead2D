#include "MeleeZombie.h"
#include "Enemy.h"
#include <allegro5\allegro.h>
#include <cmath>
#include <allegro5\allegro_primitives.h>
#include "EntityManager.h"

#define PI 3.14159265

MeleeZombie::MeleeZombie( CTwoDVector position,int difficulty, ALLEGRO_BITMAP * image, ALLEGRO_BITMAP *zombieDeathAnimationSpriteSheet) :
Enemy(MELEEZOMBIE, position, 2 + rand() % 3, 2 + rand() % 3, NORTH,
	image, true, 87, 5,4,difficulty)
{
	m_oldPosition = position;

	m_player = EntityManager::getInstance().GetPlayer();

	//sets direction to always face downwards and towards the middle (until we have a way to point to the player)
	if (m_player)
		setDirection(180.0 / PI*atan2((m_player->GetPos_Y() - position.m_y), (m_player->GetPos_X() - position.m_x)));


	SpriteSheetProperties properties;
	//properties for zombie sprite sheet
	properties.m_maxFrameCount = 8;
	properties.m_minFrameCount = 0;
	properties.m_animationFrameHeight = 128;
	properties.m_animationFrameWidth = 128;
	//to provide a slower, more visible animation
	properties.m_frameDelay = 5.0 / FPS;

	m_zombieSprite = new CSprite(image, properties);
	m_currentSprite = m_zombieSprite;

	//Death animation spritesheet
	properties.m_maxFrameCount = 7;
	properties.m_frameDelay = 5.0 / FPS;
	properties.m_minFrameCount = 0;

	m_zombieDeathSprite = new CSprite(zombieDeathAnimationSpriteSheet, properties);


	hitboxWidth = 36;
	hitboxHeight = 60;
	//Death Animation Variables
	//Death Animation Variables
	runDeathAnimation = false;
}

MeleeZombie::~MeleeZombie()
{
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

void MeleeZombie::Update( double deltaTime )
{
	m_player = EntityManager::getInstance().GetPlayer();

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
		m_currentSprite->DoLogic( deltaTime );

		if (!active && m_currentSprite->AnimationComplete())
		{
			isAlive = false;
		}
	}
		
}

void MeleeZombie::UpdateDirection()
{

	CTwoDVector playerVector = m_player->GetPosition() - m_position;

	double vectorMagnitude = playerVector.Magnitude();

	if (vectorMagnitude >3){
		setDirection(180.0 / PI * atan2(playerVector.m_y, playerVector.m_x));
		m_position.m_x += speed_x*(playerVector.m_x / vectorMagnitude);
		m_position.m_y += speed_y*(playerVector.m_y / vectorMagnitude);
		if (m_position.m_x - hitboxWidth / 2 < 0)
			m_position.m_x = hitboxWidth / 2;
		if (m_position.m_x + hitboxWidth / 2 > 800)
			m_position.m_x = DISPLAY_WIDTH-hitboxWidth/2;
		if (m_position.m_y - hitboxHeight / 2 < 0)
			m_position.m_y = hitboxHeight / 2;
		if (m_position.m_y + hitboxHeight / 2 > 600)
			m_position.m_y = DISPLAY_HEIGHT-hitboxHeight / 2;
	};
};

void MeleeZombie::Draw()
{
	//draw a healthbar
	if(active)
	{
		//draw red background
		al_draw_filled_rectangle(m_position.m_x - 11, m_position.m_y - hitboxHeight + 30, m_position.m_x + 11,
			m_position.m_y - hitboxHeight + 23, al_map_rgba(255, 0, 0, 0));
		//draw green bar
		al_draw_filled_rectangle(m_position.m_x - 10, m_position.m_y - hitboxHeight + 29,
			m_position.m_x - 10 + life * 20 / max_hitpoints, m_position.m_y - hitboxHeight + 24,
			al_map_rgba(0, 255, 0, 120));
	}
	//draws the zombie sprite
	m_currentSprite->Draw( m_position, direction);
	if (difficulty != EASY)
	{
		//draw overlay
		m_currentSprite->Draw(al_map_rgba(0, 255, 0, difficulty * 60), m_position, direction);
	}
}