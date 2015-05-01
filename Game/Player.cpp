#include "Player.h"
#include "InputManager.h"


Player::Player(int score, int lif, int maxX, int maxY, int xPos, int yPos, int speedX, int speedY, int Dir, bool activ,
	int hitboxR, int Identity, ALLEGRO_BITMAP *imag):GameEntity(lif, maxX, maxY, xPos,yPos,speedX,speedY,Dir,activ,hitboxR,Identity,imag)
{
	score = 0;
	animationFrameHeight = 32;
	animationFrameWidth = 32;
	currentAnimationFrame = 0;
	frameCount = 0;
	frameDelay = 5;
	maxFrameCount = 8;

}


Player::~Player()
{
}

void Player::UpdateDirection()
{
	enum dir{ D, L, R, U };
	if (InputManager::getInstance().isKeyPressed(UP))
	{
		direction = U;
	}
	else if (InputManager::getInstance().isKeyPressed(DOWN))
	{
		direction = D;
	}
	else if (InputManager::getInstance().isKeyPressed(RIGHT))
	{
		direction = R;
	}
	else if (InputManager::getInstance().isKeyPressed(LEFT))
	{
		direction = L;
	}
}
	bool Player::UpdatePosition()
	{
		int horizontal = 0;
		int vertical = 0;
		old_pos_x = pos_x;
		old_pos_y = pos_y;
		if (InputManager::getInstance().isKeyPressed(UP))
		{
			vertical = -1;
		}
		if (InputManager::getInstance().isKeyPressed(DOWN))
		{
			vertical = 1;
		}
		if (InputManager::getInstance().isKeyPressed(RIGHT))
		{
			horizontal = 1;
		}
		if (InputManager::getInstance().isKeyPressed(LEFT))
		{
			horizontal = -1;
		}

		pos_y += speed_y*vertical;
		pos_x += speed_x*horizontal;


		if ((old_pos_x == pos_x) && (old_pos_y == pos_y))
			return 0;
		else return 1;
	}
