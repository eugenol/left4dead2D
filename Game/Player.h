#pragma once
#include "GameEntity.h"
#include "Projectile.h"

//Temp for HUD
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


class HealthBar;
class PlayerLives;

class Player :
	public GameEntity
{
	friend Projectile;
public:
	Player(int score, int lif, int maxX, int maxY, int xPos, int yPos, int speedX, int speedY, int Dir, bool activ,
		int hitboxR, int Identity, ALLEGRO_BITMAP *imag, ALLEGRO_BITMAP *bulletSpriteSheet, ALLEGRO_BITMAP *healthBarSpriteSheet, ALLEGRO_BITMAP *skullImage);
	~Player();
	
	//Get and Set Functions
	int GetPos_X();
	int GetPos_Y();
	void update();
	bool hasShot;
	void megaShot();//do an AOE shot around player
	virtual void takeDamage(int damageAmount);

protected:
	int score;
	int livesLeft;
	int shooting_control;
	void UpdateDirection();
	bool UpdatePosition();
	
	bool damageCheck();
	void ShootCheck();
	virtual void draw();
	//Animations Variables
	int deathanimationcontrol;
	ALLEGRO_BITMAP *bulletSpriteSheet;
	ALLEGRO_BITMAP *bulletExplosionSpriteSheet;
	ALLEGRO_BITMAP *playerDeathAnimation;

	//Damage Variables
	int noOfZombieHits;
	int damageAmount;
	//Temp for HUD
	ALLEGRO_FONT *font_18;

private:
	HealthBar *healthBar;
	PlayerLives *playerLives;
};

