#include "Player.h"


Player::Player(int lif, int maxX, int maxY, int xPos, int yPos, int speedX, int speedY, int Dir, bool activ,
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
