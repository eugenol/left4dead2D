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
	int old_pos_x; //Used to check if the entity has had it's position updated
	int old_pos_y; //If not then there is no need to update direction or animation (this may differ for enemies?)

	void UpdateDirection();
	bool UpdatePosition();
};

