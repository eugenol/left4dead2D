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

	bool hasShot;

protected:
	int score;
	int shooting_control;
	void UpdateDirection();
	bool UpdatePosition();
	void ShootCheck();
	ALLEGRO_BITMAP *bulletSpriteSheet;
};

