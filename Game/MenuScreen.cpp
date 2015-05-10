#include "MenuScreen.h"


MenuScreen::MenuScreen(ALLEGRO_FONT *font_18, ALLEGRO_FONT *font_24, ALLEGRO_FONT *font_72) : font18(font_18), font24(font_24), font72(font_72)
{

}


MenuScreen::~MenuScreen()
{
}

void MenuScreen::update()
{

}

void MenuScreen::draw()
{
	al_draw_text(font24, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, 20, ALLEGRO_ALIGN_CENTRE, "Menu");
	al_draw_text(font18, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, 80, ALLEGRO_ALIGN_CENTRE, "New Game");
	al_draw_text(font18, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, 120, ALLEGRO_ALIGN_CENTRE, "Exit Game");
}