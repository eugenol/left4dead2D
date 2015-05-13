#include "Projectile.h"
#include <math.h>


Projectile::Projectile(int destination_x, int destination_y, int lif, int maxX, int maxY, int xPos, int yPos, int speedX, int speedY, int Dir, bool activ, int hitboxR, int Identity, ALLEGRO_BITMAP *imag) : GameEntity(lif, maxX, maxY, xPos, yPos, speedX, speedY, Dir, activ, hitboxR, Identity, imag)
{
	
	//Animation Initialisation
	animationFrameHeight = 15;
	animationFrameWidth = 15;
	currentAnimationFrame = 0;
	frameCount = 0;
	frameDelay = 3;
	maxFrameCount = 3;
	direction = 0;

	//Bullet Path Initialisation
	old_pos_x = xPos;
	old_pos_y = yPos;
	destinationY = destination_y;
	destinationX = destination_x;
	angleOfPath = atan2f(destinationY - old_pos_y, destinationX - old_pos_x);
	hitboxHeight = 15;
	hitboxWidth = 15;
}


Projectile::~Projectile()
{
}

bool Projectile::UpdatePosition()
{
	if (active)
	{
		if (((pos_x + int(speed_x*cosf(angleOfPath))) > 0) && ((pos_x + int(speed_x*cosf(angleOfPath))) < (maxXpos - animationFrameWidth)))
		{
			pos_x += int(speed_x*cosf(angleOfPath));
		}
		else
		{
			active = 0;
			isAlive = 0;
		}
		if (((pos_y + int(speed_y*sinf(angleOfPath))) > 0) && ((pos_y + int(speed_y*sinf(angleOfPath))) < (maxYpos - animationFrameHeight)))
		{
			pos_y += int(speed_y*sinf(angleOfPath));
		}
		else
		{
			active = 0;
			isAlive = 0;
		}
		return 1;
	}
	else return 0;
}

void Projectile::UpdateDirection()
{

}
void Projectile::update()
{
	if (UpdatePosition())
	{
		UpdateDirection();
		UpdateAnimation();
	}
}

void Projectile::Collided(GameEntity *otherObject)
{
	if (otherObject->getID() == ENEMY)
	{
		active = 0;
		isAlive = 0;
	}
}