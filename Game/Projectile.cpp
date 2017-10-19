#include "Projectile.h"
#include <math.h>


Projectile::Projectile(CTwoDVector destination, int lif, CTwoDVector position, int speedX, int speedY, int Dir, bool activ, int hitboxR, int Identity, ALLEGRO_BITMAP *imag, ALLEGRO_BITMAP *explosionImag, int damagePower)
	: 
	GameEntity(lif, position, speedX, speedY, Dir, activ, hitboxR, Identity)
{
	
	//Animation Initialisation
	SpriteSheetProperties properties;
	properties.m_animationFrameHeight = 15;
	properties.m_animationFrameWidth = 15;
	properties.m_currentAnimationFrame = 0;
	properties.m_frameCount = 0;
	properties.m_frameDelay = 3;
	properties.m_maxFrameCount = 3;
	properties.m_minFrameCount = 0;
	direction = 0;
	m_bulletSprite = new CSprite(imag, properties);

	m_currentImage = m_bulletSprite;

	properties.m_animationFrameHeight = 32;
	properties.m_animationFrameWidth = 32;
	properties.m_currentAnimationFrame = 0;
	properties.m_frameCount = 0;
	properties.m_frameDelay = 1;
	properties.m_maxFrameCount = 12;
	properties.m_minFrameCount = 0;

	m_explosionSprite = new CSprite(explosionImag, properties);

	//Bullet Path Initialisation
	m_oldPosition = position;
	m_destination = destination;
	angleOfPath = atan2f(m_destination.m_y - m_oldPosition.m_y, m_destination.m_x - m_oldPosition.m_x);
	hitboxHeight = 15;
	hitboxWidth = 15;

	//Other Initialisation
	explosionStarted = false;
	this->damagePower = damagePower;
}


Projectile::~Projectile()
{
	if(m_bulletSprite)
	{
		delete m_bulletSprite;
	}

	if (m_explosionSprite)
	{
		delete m_explosionSprite;
	}

	m_currentImage = nullptr;

}

bool Projectile::UpdatePosition()
{
	if (active)
	{
		if (((m_position.m_x + int(speed_x*cosf(angleOfPath))) > 0) && ((m_position.m_x + int(speed_x*cosf(angleOfPath))) < (maxXpos - m_currentImage->GetFrameWidth())))
		{
			m_position.m_x += int(speed_x*cosf(angleOfPath));
		}
		else
		{
			active = false;
			if (!collided) collided = true;
		}
		if (((m_position.m_y + int(speed_y*sinf(angleOfPath))) > 0) && ((m_position.m_y + int(speed_y*sinf(angleOfPath))) < (maxYpos - m_currentImage->GetFrameHeight())))
		{
			m_position.m_y += int(speed_y*sinf(angleOfPath));
		}
		else
		{
			active = false;
			if (!collided) collided = true;
		}
		return true;
	}
	return false;
}

void Projectile::UpdateDirection()
{
	
}
void Projectile::Update()
{
	if (active)
	{
		if (UpdatePosition())
		{
			UpdateDirection();
			m_currentImage->DoLogic();
		}
	}
	else if (!active && isAlive) //Explosion Sequence Out
	{
		if (collided)
		{
			m_currentImage = m_explosionSprite;
			collided = false;
		}
		m_currentImage->DoLogic();
		if (m_currentImage->GetCurrentAnimationFrame() == (m_currentImage->GetMaxFrameCount() - 1))
			isAlive = false;
	}
}

void Projectile::Draw()
{
	m_currentImage->Draw( m_position, direction);
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