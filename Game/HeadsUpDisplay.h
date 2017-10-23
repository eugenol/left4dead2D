#pragma once
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "IObserver.h"
#include "HealthBar.h"
#include "CEventValue.h"
#include "PlayerLives.h"
#include "GameTimer.h"

class HeadsUpDisplay : public IObserver
{
public:
	HeadsUpDisplay();
	~HeadsUpDisplay();
	void Update( double deltaTime );
	void Draw();

	virtual void OnNotify(const GameEntity& entity, CEvent* event);

private:

	void GetPlayerStats(CEvent* event);

	//Variables from Player to Display on the HUD
	int health, lives, score, megaShotCount;
	HealthBar m_healthBar;
	CEventValue<int> m_lives;
	PlayerLives m_playerLives;
	GameTimer m_gameTimer;
	//Font For The HUD
	ALLEGRO_FONT *Scorefont20;
};

