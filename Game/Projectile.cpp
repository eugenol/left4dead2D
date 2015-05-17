#include "Projectile.h"
#include <math.h>


Projectile::Projectile(int destination_x, int destination_y, int lif, int maxX, int maxY, int xPos, int yPos, int speedX, int speedY, int Dir, bool activ, int hitboxR, int Identity, ALLEGRO_BITMAP *imag, ALLEGRO_BITMAP *explosionImag, int damagePower, int animationFrameWidth, int animationFrameHeight, int maxAnimationFrame) : GameEntity(lif, maxX, maxY, xPos, yPos, speedX, speedY, Dir, activ, hitboxR, Identity, imag)
{
	
	//Animation Initialisation
	explosionSpriteSheet = explosionImag;
	this->animationFrameHeight = animationFrameHeight;
	this->animationFrameWidth = animationFrameWidth;
	currentAnimationFrame = 0;
	frameCount = 0;
	frameDelay = 3;
	this->maxFrameCount = maxAnimationFrame;
	direction = 0;
	megaShotRotationAngle = 0;
	//Bullet Path Initialisation
	old_pos_x = xPos;
	old_pos_y = yPos;
	destinationY = destination_y;
	destinationX = destination_x;
	angleOfPath = atan2f(destinationY - old_pos_y, destinationX - old_pos_x);
	hitboxHeight = 15;
	hitboxWidth = 15;

	//Other Initialisation
	explosionStarted = false;
	this->damagePower = damagePower;

}

void Projectile::draw()
{
	if (damagePower == 20)
	{
		GameEntity::draw();
	}
	else
	{
		al_draw_tinted_scaled_rotated_bitmap_region(image, currentAnimationFrame*animationFrameWidth, 0, animationFrameWidth, animationFrameHeight, al_map_rgb(rand() % 256, rand() % 256, rand() % 256), animationFrameHeight / 2, animationFrameWidth / 2, pos_x, pos_y, 1, 1, megaShotRotationAngle, 0);
	}

}
void Projectile::UpdateAnimation()
{
	if ((megaShotRotationAngle += 30) == 360)
	{
		megaShotRotationAngle = 0;
	}
	GameEntity::UpdateAnimation();
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
			if (!collided) collided = true;
		}
		if (((pos_y + int(speed_y*sinf(angleOfPath))) > 0) && ((pos_y + int(speed_y*sinf(angleOfPath))) < (maxYpos - animationFrameHeight)))
		{
			pos_y += int(speed_y*sinf(angleOfPath));
		}
		else
		{
			active = 0;
			if (!collided) collided = true;
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
	if (active)
	{
		if (UpdatePosition())
		{
			UpdateDirection();
			UpdateAnimation();
		}
	}
	else if ((!active) && isAlive) //Explosion Sequence Out
	{
		if (collided)
		{
			image = explosionSpriteSheet;
			animationFrameHeight = 32;
			animationFrameWidth = 32;
			currentAnimationFrame = 0;
			frameCount = 0;
			frameDelay = 5;
			maxFrameCount = 12;
			collided = false;
		}
		UpdateAnimation();
		if (frameCount == 0)
			isAlive = false;
	}
}

int Projectile::getDamagePower()
{
	return damagePower;
}

void Projectile::setDamagePower(int power)
{
	damagePower = power;
}

//void Projectile::Collided(GameEntity *otherObject)
//{
//	
//	if (otherObject->getID() == ENEMY)
//	{
//		active = 0;
//		if (!explosionStarted) explosionStarted = true;
//	}
//}