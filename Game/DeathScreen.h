#ifndef DEATHSCREEN_H
#define DEATHSCREEN_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "InputManager.h"

class DeathScreen
{
public:
	DeathScreen(ALLEGRO_FONT *font_18, ALLEGRO_FONT *font_24, ALLEGRO_FONT *font_72);
	~DeathScreen();

	void Update();
	void Draw();
	bool GetReturnToMenu() { return returnToMenu; }
	void SetReturnToMenu() { returnToMenu = false; }
private:
	ALLEGRO_FONT *font18 = nullptr;
	ALLEGRO_FONT *font24 = nullptr;
	ALLEGRO_FONT *font72 = nullptr;
	ALLEGRO_BITMAP *image = nullptr;
	bool returnToMenu;
};
#endif

