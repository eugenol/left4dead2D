#include "Player.h"
#include "InputManager.h"
#include "EntityManager.h"
#include <allegro5/allegro_font.h>  //Temp for hud
#include <allegro5/allegro_ttf.h>	//Temp for hud
#include "HealthBar.h"
#include "PlayerLives.h"
#include "GameTimer.h"
#include "Potion.h"
#include "HeadsUpDisplay.h"
#define PI 3.14159265

Player::Player(int score, int lif, CTwoDVector position, int speedX, int speedY, int Dir, bool activ, int hitboxR, int Identity, ALLEGRO_BITMAP *bulletSpriteSheet, ALLEGRO_BITMAP *healthBarSpriteSheet, ALLEGRO_BITMAP *skullImage, ALLEGRO_BITMAP* gameoverImage, ALLEGRO_BITMAP *potionImage) :
GameEntity(lif, position, speedX, speedY, Dir, activ, hitboxR, Identity),
healthBar(),
playerLives(),
gameTimer()
{
	//set spritesheet properties PlayerSprite
	struct SpriteSheetProperties properties;
	properties.m_animationFrameHeight = 32;
	properties.m_animationFrameWidth = 32;
	properties.m_frameDelay = 5.0 / FPS;
	properties.m_maxFrameCount = 8;
	properties.m_minFrameCount = 0;

	m_playerSpriteSheet = new CSprite("player_sprite.png", properties);
	m_playerImage = m_playerSpriteSheet;

	//set spritesheet properties PleayerDeathSprite
	properties.m_animationFrameHeight = 66;
	properties.m_animationFrameWidth = 68;
	properties.m_frameDelay = 6.0 / FPS;
	properties.m_maxFrameCount = 7;
	properties.m_minFrameCount = 0;
	
	m_playerDeathSprite = new CSprite("player_bloody_death_spritesheet.png", properties);


	//set spritesheet properties AttackSplatter
	properties.m_animationFrameHeight = 42;
	properties.m_animationFrameWidth = 32;
	properties.m_frameDelay = 2.0 / FPS;
	properties.m_maxFrameCount = 10;
	properties.m_minFrameCount = 0;
	attackSplatterAnimationControl = false;

	m_attackSplatter = new CSprite("attack_splatter_42_32.png", properties);

	headsUpDisplay = new HeadsUpDisplay();
	this->score = score;
	shooting_control = 0;

	this->bulletSpriteSheet = bulletSpriteSheet;
	bulletExplosionSpriteSheet = al_load_bitmap("explosion.png");

	hitboxHeight = 32;
	hitboxWidth = 32;
	livesLeft = 3;
	noOfZombieHits = 0;
	deathanimationcontrol = 0;

	//Temporary Code for HUD
	//Init fonts
	al_init_font_addon();
	al_init_ttf_addon();
	font_18 = al_load_ttf_font("pirulen.ttf", 18, 0);

	healthBar = new HealthBar(healthBarSpriteSheet);
	//EntityManager::getInstance().AddEntity(healthBar);

	playerLives = new PlayerLives(skullImage, gameoverImage);
	//EntityManager::getInstance().AddEntity(playerLives);

	gameTimer = new GameTimer();
	//EntityManager::getInstance().AddEntity(gameTimer);

	potion = new Potion(potionImage);
	//EntityManager::getInstance().AddEntity(potion);

	//Reward Initialisation
	megaShotCapability = false;
	megaShotCount = 0;
	oldScore = 0;
}


Player::~Player()
{
	delete headsUpDisplay;
	delete healthBar;
	delete playerLives;
	delete gameTimer;
	delete potion;
	//When Player dies save the current score and gametime to a file
	std::fstream file("highscores.txt", std::ios::app);
	file << score <<" "<< gameTime << std::endl;
	file.close();
}

void Player::Update( double deltaTime )
{
	headsUpDisplay->Update(life, livesLeft, score, megaShotCount);
	if (active)
	{
		if (damageCheck())
		{
			active = false;
		}
		ShootCheck();
		if (UpdatePosition())
		{
			UpdateDirection();
			m_playerImage->DoLogic( deltaTime );
		}
	}
	else if (!active && isAlive)
	{
		if (deathanimationcontrol == 0)
		{	
			deathanimationcontrol++;
			m_playerImage = m_playerDeathSprite;
		}

		m_playerImage->DoLogic( deltaTime );
		if (m_playerImage->AnimationComplete()) 
		{
			isAlive = false;
		}
	}
	if (attackSplatterAnimationControl)
	{
		attackSplatterAnimationUpdate( deltaTime );
	}
	
	healthBar->DoLogic(life);
	playerLives->SetLivesLeft(livesLeft);
	gameTimer->SetPlayerAliveStatus(isAlive);
	potion->Update( deltaTime );
	potion->DoLogic(GetPos_X(), GetPos_Y(), isAlive);
	
	checkForRewards();

	if (potion->CollectedPotion())
	{
		if (livesLeft == 3)
		{
			life = 100;
		}
		else
		{
			livesLeft++;
		}
	}
}

void Player::attackSplatterAnimationUpdate( double deltaTime )
{
	//Generates /Advances Animation
	m_attackSplatter->DoLogic( deltaTime );

	if( m_attackSplatter->AnimationComplete() )
	{
			attackSplatterAnimationControl = false;
			m_attackSplatter->ResetAnimation();
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
				m_position.m_x = rand() % 760 + 20;	//Give a Random "Respawn" Position
				m_position.m_y = rand() % 560 + 20;	//Give a Random "Respawn" Position
				noOfZombieHits = 0;		//Reset Zombie hit counter
			}
			else					//Otherwise taking away a life will cause players number of lives to go to or below zero so...
			{
				playerHasDied = true;

				if (livesLeft > 0)
				{
					livesLeft--;
				}
			}
		}
		else //otherwise taking away life will not take players health to or below zero so...
		{
			attackSplatterAnimationControl = true;
			splatterAngle = rand() % 360;
			life -= damageAmount;	//take away some life
			noOfZombieHits = 0;		//reset zombie hit counter
		}
	}
	if (playerHasDied) return 1;
	else return 0;
		
}
void Player::takeDamage(int damageAmount)
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
	m_oldPosition = m_position;

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
	if (((m_position.m_x + speed_x*horizontal) > m_playerImage->GetFrameWidth()/2) && ((m_position.m_x + speed_x*horizontal) < (maxXpos - m_playerImage->GetFrameWidth()/2)))
	{
		m_position.m_x += speed_x*horizontal;
	}
	if (((m_position.m_y + speed_y*vertical) > m_playerImage->GetFrameHeight() /2) && ((m_position.m_y + speed_y*vertical) < (maxYpos - m_playerImage->GetFrameHeight()/2)))
	{
		m_position.m_y += speed_y*vertical;
	}

		if (m_oldPosition == m_position)
		{
			return false;
		}

		
	return true;
}

void Player::ShootCheck()
{
	if (InputManager::getInstance().isMouseButtonPressed(LEFTM))
	{
		if ((shooting_control == 0) || (shooting_control > 3))
		{
			CTwoDVector destination = InputManager::getInstance().GetMousePosition();
			GameEntity* bulletPtr = EntityManager::getInstance().MakeEntity<Projectile>(destination, 0, m_position, 10, 10, 0, 1, 2, PROJECTILE, bulletSpriteSheet, bulletExplosionSpriteSheet, 20);
			EntityManager::getInstance().AddEntity(bulletPtr);
			shooting_control = 0;
		}
		shooting_control++;
		
	}
	if ((InputManager::getInstance().isMouseButtonPressed(RIGHTM)) && (megaShotCount > 0))
	{
		InputManager::getInstance().clearInput();
		megaShot();
		megaShotCount--;
	}
	
}
void Player::megaShot()
{//shoots 24 projectiles radially around the player
	for (int angle = 0; angle < 360; angle += 15)
	{
		CTwoDVector destination(m_position.m_x + 100 * cosf(angle*PI / 180), m_position.m_y + 100 * sinf(angle*PI / 180));
		GameEntity* bulletPtr = EntityManager::getInstance().MakeEntity<Projectile>(destination, 0, m_position, 10, 10, 0, 1, 2, PROJECTILE, bulletSpriteSheet, bulletExplosionSpriteSheet, 80);
		EntityManager::getInstance().AddEntity(bulletPtr);
	}
}
int Player::GetPos_X()
{
	return m_position.m_x;
}

int Player::GetPos_Y()
{
	return m_position.m_y;
}

CTwoDVector Player::GetPosition()
{
	return m_position;
}

void Player::Draw()
{
	m_playerImage->Draw( m_position, direction );

	//Blood Spatter Animation
	if (attackSplatterAnimationControl)
	{
		m_attackSplatter->Draw(m_position, 0);
	}

	headsUpDisplay->Draw();
	healthBar->Draw();
	playerLives->Draw();
	gameTimer->Draw();
	potion->Draw();
}
void Player::increaseScore(int addedScore){
	score += addedScore;
}

void Player::checkForRewards()
{
	if ((score - oldScore) >= 10)
	{
		megaShotCapability = true;
		megaShotCount++;
		oldScore = score;
	}

}