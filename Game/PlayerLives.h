#pragma once

#include "allegro5\allegro.h"
#include "GameEntity.h"
#include "CSprite.h"
#include <memory>

//-------------------------------------------------------

class PlayerLives : public GameEntity
{
public:
	PlayerLives( );
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

	std::unique_ptr<CSprite> m_heart0;
	std::unique_ptr<CSprite> m_heart1;
	std::unique_ptr<CSprite> m_heart2;

	int m_numberOfLives;
};

//-------------------------------------------------------

