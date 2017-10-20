#pragma once

#include "allegro5\allegro.h"
#include "GameEntity.h"

//-------------------------------------------------------

class PlayerLives : public GameEntity
{
public:
	PlayerLives(ALLEGRO_BITMAP *skulls);
	virtual ~PlayerLives();

	virtual void Draw();
	virtual void Update( double deltaTime );
	virtual void Collided(GameEntity *otherObject) {}
	virtual bool UpdatePosition() { return false; }
	virtual void UpdateDirection() {}

	void SetLivesLeft(int livesLeft) { m_numberOfLives = livesLeft; }

private:
	ALLEGRO_BITMAP *m_skull;
	int m_imageWidth;
	int m_imageHeight;
	int m_frameWidth;

	int m_numberOfLives;
};

//-------------------------------------------------------

