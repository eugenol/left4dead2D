#pragma once

#include "allegro5\allegro.h"
#include "GameEntity.h"
#include "Timer.h"
#include "CSprite.h"
#include <memory>

//-------------------------------------------------------

class Potion : public GameEntity
{
public:
	Potion();
	virtual ~Potion();

	virtual void Draw();
	virtual void Update( double deltaTime );
	virtual void Collided(GameEntity *otherObject) {}
	virtual bool UpdatePosition() { return false; }
	virtual void UpdateDirection() {}

	void DoLogic(int playerXPos, int playerYPos, bool isAlive);
	bool CollectedPotion() { return m_collectedPotion; }

private:
	ALLEGRO_BITMAP *m_potionImage;
	std::unique_ptr<CSprite> m_potionSprite;
	int m_randomPosX;
	int m_randomPosY;
	Timer m_noPotionTimer;
	Timer m_showPotionTimer;
	int m_imageWidth;
	int m_imageHeight;
	bool m_collectedPotion;
};

//-------------------------------------------------------

