#ifndef MENUSCREEN_H
#define MENUSCREEN_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "GameScreen.h"


class MenuScreen : public CScreen
{
public:
	MenuScreen(ALLEGRO_FONT *font_18, ALLEGRO_FONT *font_24, ALLEGRO_FONT *font_72, GameScreen *current_game);
	~MenuScreen();
	enum MENUSTATE { STAYMENU, NEWGAME, HIGHSCORES, CREDITS, EXITGAME, RESUMEGAME };
	void Update();
	void Draw();
	int getCurrentMenuOption();
	void clearCurrentMenuOption() { currentOption = STAYMENU; }

private:
	ALLEGRO_FONT *font18 = NULL;
	ALLEGRO_FONT *font24 = NULL;
	ALLEGRO_FONT *font72 = NULL;
	const int DISPLAY_HEIGHT = 600;
	const int DISPLAY_WIDTH = 800;
	int menuSlot[7];
	GameScreen *game;
	int mouse_x, mouse_y;
	int menuItem;
	int currentOption;

};
#endif
