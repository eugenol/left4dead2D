#pragma once

#include "allegro5\allegro.h"
#include "GameEntity.h"
#include <memory>
#include "CSprite.h"

//-------------------------------------------------------

class HealthBar : public GameEntity
{
public:
	HealthBar(ALLEGRO_BITMAP *healthBarSpriteSheet);
	virtual ~HealthBar();

	virtual void Draw();
	virtual void Update( double deltaTime );
	virtual void Collided(GameEntity *otherObject) {}
	virtual bool UpdatePosition() { return false; }
	virtual void UpdateDirection() {}

	void DoLogic(double lifePercentage);

private:
	int m_imageWidth;
	int m_imageHeight;
	int m_frameWidth;
	int m_currentAnimationFrame;
	std::unique_ptr<CSprite> m_healthBar;
	CTwoDVector m_position;
};

//-------------------------------------------------------

