#include "DeathScreen.h"


DeathScreen::DeathScreen(ALLEGRO_FONT *font_18, ALLEGRO_FONT *font_24, ALLEGRO_FONT *font_72) : font18(font_18), font24(font_24), font72(font_72)
{
}


DeathScreen::~DeathScreen()
{
}

void DeathScreen::update()
{
	int mouse_x = InputManager::getInstance().getMouseX();
	int mouse_y = InputManager::getInstance().getMouseY();

	returnToMenu = false;

	if (InputManager::getInstance().isMouseButtonPressed(LEFTM) && (mouse_x >= DISPLAY_WIDTH - 200)
		&& (mouse_x <= DISPLAY_WIDTH) && (mouse_y >= DISPLAY_HEIGHT - 38) && (mouse_y <= DISPLAY_HEIGHT))
	{
		returnToMenu = true;
	}
}

void DeathScreen::draw()
{
	al_draw_text(font24, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, 80, ALLEGRO_ALIGN_CENTRE, "Dead!!");

	al_draw_text(font18, al_map_rgb(255, 0, 0), DISPLAY_WIDTH - 100, DISPLAY_HEIGHT - 28, ALLEGRO_ALIGN_CENTRE, "Main Menu");
}



