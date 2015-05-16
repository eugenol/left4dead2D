#pragma once

#include "allegro5\allegro.h"
#include "GameEntity.h"
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>

//-------------------------------------------------------

class GameTimer : public GameEntity
{
public:
	GameTimer();
	virtual ~GameTimer();

	virtual void draw();
	virtual void update();
	virtual void Collided(GameEntity *otherObject) {}
	virtual bool UpdatePosition() { return false; }
	virtual void UpdateDirection() {}

	void UpdateTime();
	void SetPlayerAliveStatus(bool value) { isAlive = value; }

private:
	time_t startTime;
	char deltaTimeStr[9];
	ALLEGRO_FONT *timerFont;
	bool isAlive;
};

//-------------------------------------------------------

