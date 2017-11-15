#pragma once
#include "GameEntity.h"
#include "CSprite.h"

class Projectile :
	public GameEntity
{

public:
	Projectile( CTwoDVector destination, int lif, CTwoDVector position, int speedX, int speedY, int Dir, bool activ, int Identity, ALLEGRO_BITMAP* imag, ALLEGRO_BITMAP* explosionImag, int damagePower );
	//void Collided(GameEntity *otherObject);
	~Projectile();
private:
	float gradient; //Gradient for Path of Bullet Equation
	float y_int;	//y intercept for Path of Bullet Equation
	float angleOfPath;
	CTwoDVector m_destination;
	float destinationX, destinationY;
	bool UpdatePosition();
	void UpdateDirection();
	void Update( double deltaTime ) override;
	void Draw() override;
	int damagePower;
	//Explosion Control
	ALLEGRO_BITMAP *explosionSpriteSheet;
	bool explosionStarted;
	virtual int getDamagePower();

	void setDamagePower(int);

	CSprite* m_explosionSprite;
	CSprite* m_bulletSprite;
	CSprite* m_currentImage;
};

