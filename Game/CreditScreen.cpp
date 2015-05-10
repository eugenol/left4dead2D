#include "CreditScreen.h"


CreditScreen::CreditScreen(ALLEGRO_FONT *font_18, ALLEGRO_FONT *font_24, ALLEGRO_FONT *font_72) : font18(font_18), font24(font_24), font72(font_72)
{
}


CreditScreen::~CreditScreen()
{
}

void CreditScreen::update()
{

}

void CreditScreen::draw()
{
	al_draw_text(font24, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, 80, ALLEGRO_ALIGN_CENTRE, "Game Team");
	al_draw_text(font18, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, 120, ALLEGRO_ALIGN_CENTRE, "Eugene");
	al_draw_text(font18, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, 160, ALLEGRO_ALIGN_CENTRE, "Bernard");
	al_draw_text(font18, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, 200, ALLEGRO_ALIGN_CENTRE, "Janice");
	al_draw_text(font18, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, 240, ALLEGRO_ALIGN_CENTRE, "David");
	al_draw_text(font18, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, 280, ALLEGRO_ALIGN_CENTRE, "Sahil");
}



