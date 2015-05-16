#pragma once
#include "GameEntity.h"
class Projectile :
	public GameEntity
{

public:
	Projectile(int destination_x, int destination_y, int lif, int maxX, int maxY, int xPos, int yPos, int speedX, int speedY, int Dir, bool activ, int hitboxR, int Identity, ALLEGRO_BITMAP *imag, ALLEGRO_BITMAP *explosionImag, int damagePower);
	//void Collided(GameEntity *otherObject);
	~Projectile();
private:
	float gradient; //Gradient for Path of Bullet Equation
	float y_int;	//y intercept for Path of Bullet Equation
	float angleOfPath;
	float destinationX, destinationY;
	bool UpdatePosition();
	void UpdateDirection();
	void update();
	int damagePower;
	//Explosion Control
	ALLEGRO_BITMAP *explosionSpriteSheet;
	bool explosionStarted;
	virtual int getDamagePower();
};

