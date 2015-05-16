#pragma once

#include "allegro5\allegro.h"
#include "GameEntity.h"
#include "Timer.h"

//-------------------------------------------------------

class Potion : public GameEntity
{
public:
	Potion(ALLEGRO_BITMAP *potionImage);
	virtual ~Potion();

	virtual void draw();
	virtual void update();
	virtual void Collided(GameEntity *otherObject) {}
	virtual bool UpdatePosition() { return false; }
	virtual void UpdateDirection() {}

	void DoLogic(int playerXPos, int playerYPos);
	bool CollectedPotion() { return m_collectedPotion; }

private:
	ALLEGRO_BITMAP *m_potionImage;
	int m_randomPosX;
	int m_randomPosY;
	Timer m_noPotionTimer;
	Timer m_showPotionTimer;
	int m_imageWidth;
	int m_imageHeight;
	bool m_collectedPotion;
};

//-------------------------------------------------------

