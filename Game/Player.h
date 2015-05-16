#pragma once
#include "GameEntity.h"
#include "Projectile.h"

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

protected:
	int score;
	int livesLeft;
	int shooting_control;
	void UpdateDirection();
	bool UpdatePosition();
	void ShootCheck();
	ALLEGRO_BITMAP *bulletSpriteSheet;
	ALLEGRO_BITMAP *bulletExplosionSpriteSheet;

private:
	HealthBar *healthBar;
	PlayerLives *playerLives;
};

