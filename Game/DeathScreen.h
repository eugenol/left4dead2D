#ifndef DEATHSCREEN_H
#define DEATHSCREEN_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "InputManager.h"

class DeathScreen
{
private:
	ALLEGRO_FONT *font18 = NULL;
	ALLEGRO_FONT *font24 = NULL;
	ALLEGRO_FONT *font72 = NULL;
	ALLEGRO_BITMAP *image = NULL;
	const int DISPLAY_HEIGHT = 600;
	const int DISPLAY_WIDTH = 800;
	bool returnToMenu;
public:
	DeathScreen(ALLEGRO_FONT *font_18, ALLEGRO_FONT *font_24, ALLEGRO_FONT *font_72);
	~DeathScreen();
	void update();
	void draw();
	bool getReturnToMenu() { return returnToMenu; }
	void setReturnToMenu() { returnToMenu = false; }
};
#endif

