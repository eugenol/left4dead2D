#pragma once
#include "GameEntity.h"
class Player :
	public GameEntity
{
public:
	Player(int lif, int maxX, int maxY, int xPos, int yPos, int speedX, int speedY, int Dir, bool activ,
		int hitboxR, int Identity, ALLEGRO_BITMAP *imag);
	~Player();
protected:
	void UpdateDirection();
};

