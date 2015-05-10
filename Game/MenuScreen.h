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

class MenuScreen
{
private:
	enum MENUSTATE{NEWGAME, RESUMEGAME,HIGHSCORES, EXITGAME};
	ALLEGRO_FONT *font18 = NULL;
	ALLEGRO_FONT *font24 = NULL;
	ALLEGRO_FONT *font72 = NULL;
	const int DISPLAY_HEIGHT = 600;
	const int DISPLAY_WIDTH = 800;
public:
	MenuScreen(ALLEGRO_FONT *font_18, ALLEGRO_FONT *font_24, ALLEGRO_FONT *font_72);
	~MenuScreen();
	void update();
	void draw();
};
#endif
