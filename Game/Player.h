#pragma once
#include "GameEntity.h"
#include "Projectile.h"

//Temp for HUD
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

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
	void megaShot();//do an AOE shot around player
protected:
	int score;
	int livesLeft;
	int shooting_control;
	void UpdateDirection();
	bool UpdatePosition();
	void ShootCheck();
	virtual void draw();
	ALLEGRO_BITMAP *bulletSpriteSheet;
	ALLEGRO_BITMAP *bulletExplosionSpriteSheet;

	//Temp for HUD
	ALLEGRO_FONT *font_18;
};

