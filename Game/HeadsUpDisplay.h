#pragma once
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "IObserver.h"

class HeadsUpDisplay : public IObserver
{
public:
	HeadsUpDisplay();
	~HeadsUpDisplay();
	void Update(int health, int lives, int score, int megashotCount);
	void Draw();

	virtual void OnNotify(const GameEntity& entity, CEvent event);

private:
	//Variables from Player to Display on the HUD
	int health, lives, score, megaShotCount;

	//Font For The HUD
	ALLEGRO_FONT *Scorefont20;
};

