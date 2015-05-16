#pragma once
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class HeadsUpDisplay
{
public:
	HeadsUpDisplay();
	~HeadsUpDisplay();
	void Update(int health, int lives, int score, int megashotCount);
private:
	//Variables from Player to Display on the HUD
	int health, lives, score, megaShotCount;
	
	//Font For The HUD
	ALLEGRO_FONT *Scorefont20;

	void draw();
	
};

