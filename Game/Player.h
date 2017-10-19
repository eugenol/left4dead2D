#pragma once
#include "GameEntity.h"
#include "Projectile.h"
#include "HeadsUpDisplay.h"
#include <fstream>
#include "CSprite.h"

//Temp for HUD
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class HealthBar;
class PlayerLives;
class GameTimer;
class Potion;

class Player :
	public GameEntity
{
	friend Projectile;
public:
	Player(int score, int lif, int xPos, int yPos, int speedX, int speedY, int Dir, bool activ,
		int hitboxR, int Identity, ALLEGRO_BITMAP *bulletSpriteSheet, ALLEGRO_BITMAP *healthBarSpriteSheet, ALLEGRO_BITMAP *skullImage, ALLEGRO_BITMAP *gameoverImage, ALLEGRO_BITMAP *potionImage);
	~Player();
	
	//Get and Set Functions
	int GetPos_X();
	int GetPos_Y();
	void Update() override;
	void Draw() override;
	void takeDamage(int damageAmount) override;
	void increaseScore(int addedScore);

	bool hasShot;
	void megaShot();//do an AOE shot around player

protected:
	int score;
	int livesLeft;
	int shooting_control;
	void UpdateDirection();
	bool UpdatePosition();
	
	void checkForRewards(); //Check to see if Player has earned an award
	
	bool damageCheck();
	void ShootCheck();

	//Animation Functions
	void attackSplatterAnimationUpdate();
	//Animations Variables
	int deathanimationcontrol;
	ALLEGRO_BITMAP *bulletSpriteSheet;
	ALLEGRO_BITMAP *bulletExplosionSpriteSheet;

	bool attackSplatterAnimationControl;
	float splatterAngle;
	int attackSplatterFrameWidth;
	int attackSplatterFrameHeight;
	int attackSplatterCurrentAnimationFrame;
	int attackSplatterMaxAnimtionFrame;
	int attackSplatterFrameDelay;
	int attackSplatterFrameCount;

	//Damage Variables
	int noOfZombieHits;
	int damageAmount;
	//Temp for HUD
	ALLEGRO_FONT *font_18;

	//Reward Variables
	bool megaShotCapability;
	int megaShotCount;
	int oldScore;

private:
	HealthBar *healthBar;
	PlayerLives *playerLives;
	GameTimer *gameTimer;
	Potion *potion;
	HeadsUpDisplay *headsUpDisplay;


	CSprite* m_playerSpriteSheet;
	CSprite* m_playerDeathSprite;
	CSprite* m_playerImage;

	CSprite* m_attackSplatter;

};

