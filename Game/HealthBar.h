#pragma once

#include "allegro5\allegro.h"
#include "GameEntity.h"
#include <memory>
#include "CSprite.h"

//-------------------------------------------------------

class HealthBar : public GameEntity
{
public:
	HealthBar();
	virtual ~HealthBar();

	virtual void Draw();
	virtual void Update( double deltaTime );
	virtual void Collided(GameEntity *otherObject) {}
	virtual bool UpdatePosition() { return false; }
	virtual void UpdateDirection() {}

	void DoLogic(double lifePercentage);

private:
	int m_currentAnimationFrame;
	std::unique_ptr<CSprite> m_healthBar;
	CTwoDVector m_position;
};

//-------------------------------------------------------

