#pragma once
#include "GameEntity.h"
#include "Projectile.h"
class Player :
	public GameEntity
{
	friend Projectile;
public:
	Player(int score, int lif, int maxX, int maxY, int xPos, int yPos, int speedX, int speedY, int Dir, bool activ,
		int hitboxR, int Identity, ALLEGRO_BITMAP *imag, ALLEGRO_BITMAP *bulletSpriteSheet);
	~Player();
	
	//Get and Set Functions
	int GetPos_X();
	int GetPos_Y();
	void update();
	void takeDamage(int damage);
	int livesLeft=3;//number of respawns the player has left
	bool hasShot;
	int invulnerabilityCounter=0;//counter for player to be invulnerable, used for respawning and after taking dmg
	void megaShot();//do an AOE shot around player
	void makeInvulnerable(int time);
protected:
	int score;
	int shooting_control;
	void UpdateDirection();
	bool UpdatePosition();
	void ShootCheck();
	ALLEGRO_BITMAP *bulletSpriteSheet;
};

