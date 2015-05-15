#include "Player.h"
#include "InputManager.h"
#include "EntityManager.h"
#include <allegro5/allegro_font.h>  //Temp for hud
#include <allegro5/allegro_ttf.h>	//Temp for hud
#define PI 3.14159265

Player::Player(int score, int lif, int maxX, int maxY, int xPos, int yPos, int speedX, int speedY, int Dir, bool activ,
	int hitboxR, int Identity, ALLEGRO_BITMAP *imag, ALLEGRO_BITMAP *bulletSpriteSheet) :GameEntity(lif, maxX, maxY, xPos, yPos, speedX, speedY, Dir, activ, hitboxR, Identity, imag)
{
	this->score = score;
	shooting_control = 0;
	animationFrameHeight = 32;
	animationFrameWidth = 32;
	currentAnimationFrame = 0;
	frameCount = 0;
	frameDelay = 5;
	maxFrameCount = 8;
	minFrameCount = 0;
	this->bulletSpriteSheet = bulletSpriteSheet;
	bulletExplosionSpriteSheet = al_load_bitmap("explosion.png");
	hitboxHeight = 32;
	hitboxWidth = 32;
	livesLeft = 3;
	noOfZombieHits = 0;

	//Temporary Code for HUD
	//Init fonts
	al_init_font_addon();
	al_init_ttf_addon();
	font_18 = al_load_ttf_font("pirulen.ttf", 18, 0);
}


Player::~Player()
{
}

void Player::update()
{
	if (damageCheck())
	{
		active = 0;
		isAlive = 0;
	}
	ShootCheck();
	if (UpdatePosition())
	{
		UpdateDirection();
		UpdateAnimation();
	}
}

bool Player::damageCheck()
{
	bool playerHasDied = false;
	if (noOfZombieHits >= 100) //If Player has been hit enough times for Damage to take Place then...
	{
		if ((life -= damageAmount) <= 0) //If applying damage to player will take players health equal to or below zero then...
		{
			if ((livesLeft - 1) > 0) //If taking away a life will not cause his number of lives to go to or below zero then...
			{
				livesLeft--;			//Take away a life from player
				life = 100;				//Give Him full life again
				noOfZombieHits = 0;		//Reset Zombie hit counter
			}
			else					//Otherwise taking away a life will cause players number of lives to go to or below zero so...
			{
				playerHasDied = true;
			}
		}
		else //otherwise taking away life will not take players health to or below zero so...
		{
			life -= damageAmount;	//take away some life
			noOfZombieHits = 0;		//reset zombie hit counter
		}
	}
	if (playerHasDied) return 1;
	else return 0;
		
}
void Player::damaged(int damageAmount)
{
	this->damageAmount = damageAmount;
	noOfZombieHits++;
}
void Player::UpdateDirection()
{
	enum dir{ D, L, R, U };
	if (InputManager::getInstance().isKeyPressed(UP))
	{
		direction = U;
	}
	else if (InputManager::getInstance().isKeyPressed(DOWN))
	{
		direction = D;
	}
	else if (InputManager::getInstance().isKeyPressed(RIGHT))
	{
		direction = R;
	}
	else if (InputManager::getInstance().isKeyPressed(LEFT))
	{
		direction = L;
	}
}
bool Player::UpdatePosition()
{
	int horizontal = 0;
	int vertical = 0;
	old_pos_x = pos_x;
	old_pos_y = pos_y;

	//get inputs
	if (InputManager::getInstance().isKeyPressed(UP))
	{
		vertical = -1;
	}
	if (InputManager::getInstance().isKeyPressed(DOWN))
	{
		vertical = 1;
	}
	if (InputManager::getInstance().isKeyPressed(RIGHT))
	{
		horizontal = 1;
	}
	if (InputManager::getInstance().isKeyPressed(LEFT))
	{
		horizontal = -1;
	}

	
	//move position
	if (((pos_x + speed_x*horizontal) > animationFrameWidth/2) && ((pos_x + speed_x*horizontal) < (maxXpos - animationFrameWidth/2)))
	{
			pos_x += speed_x*horizontal;
	}
	if (((pos_y + speed_y*vertical) > animationFrameHeight/2) && ((pos_y + speed_y*vertical) < (maxYpos - animationFrameHeight/2)))
	{
		pos_y += speed_y*vertical;
	}

		if ((old_pos_x == pos_x) && (old_pos_y == pos_y))
			return 0;
		else return 1;
}

void Player::ShootCheck()
{
	hasShot = false;
	if (InputManager::getInstance().isMouseButtonPressed(LEFTM))
		hasShot = true;
	if (hasShot)
	{
		if ((shooting_control == 0) || (shooting_control > 3))
		{
			int destination_x = InputManager::getInstance().getMouseX();
			float destination_y = InputManager::getInstance().getMouseY();
			Projectile *bulletPtr = new Projectile(destination_x, destination_y, 0, 800, 600, pos_x, pos_y, 10, 10, 0, 1, 2, PROJECTILE, bulletSpriteSheet, bulletExplosionSpriteSheet);
			EntityManager::getInstance().AddEntity(bulletPtr);
			shooting_control = 0;
		}
		shooting_control++;
		
	}
	
}
void Player::megaShot(){//shoots 24 projectiles radially around the player
	int destination_x, destination_y;
	for (int angle = 0; angle < 360; angle += 15)
	{
		destination_x = pos_x + 100*cosf(angle*PI/180);
		destination_y = pos_y + 100*sinf(angle*PI/180);
		Projectile *bulletPtr = new Projectile(destination_x, destination_y, 0, 800, 600, pos_x, pos_y, 10, 10, 0, 1, 2, PROJECTILE, bulletSpriteSheet, bulletExplosionSpriteSheet);
		EntityManager::getInstance().AddEntity(bulletPtr);
	}
}
int Player::GetPos_X()
{
	return pos_x;
}

int Player::GetPos_Y()
{
	return pos_y;
}

void Player::draw()
{
	GameEntity::draw();
	al_draw_textf(font_18, al_map_rgb(255, 255, 255), 0, 0, ALLEGRO_ALIGN_LEFT, "Player Life: %i Player Lives: %i", life, livesLeft);
}