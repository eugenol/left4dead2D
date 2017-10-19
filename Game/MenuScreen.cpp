#include "MenuScreen.h"


MenuScreen::MenuScreen(ALLEGRO_FONT *font_18, ALLEGRO_FONT *font_24, ALLEGRO_FONT *font_72, GameScreen *current_game) : font18(font_18), font24(font_24), font72(font_72), game(current_game)
{
	for (int i = 0; i < 7; i++)
		menuSlot[i] = 40 + i * 40;
	
	menuSlot[0] -= 20;
}


MenuScreen::~MenuScreen()
{
}

void MenuScreen::Update()
{
	mouse_x = InputManager::getInstance().getMouseX();
	mouse_y = InputManager::getInstance().getMouseY();

	menuItem = 0;
	currentOption = 0;

	if ((mouse_x >= 300) && (mouse_x <= 500))
	{
		for (int i = 1; i < 7; i++)
		{
			if ((mouse_y >= menuSlot[i] - 10) && (mouse_y <= menuSlot[i] + 26))
			{
				menuItem = i;
			}
		}
	}

	if (InputManager::getInstance().isMouseButtonPressed(LEFTM))
	{
			if (menuItem == 1)
			{
				currentOption = NEWGAME;
			}
			else if (menuItem == 2)
			{
				if (game->isPlayerAlive())
					currentOption = RESUMEGAME;
				else
					currentOption = STAYMENU;
			}
			else if (menuItem == 3)
			{
				currentOption = HIGHSCORES;
			}
			else if (menuItem == 4)
			{
				currentOption = CREDITS;
			}
			else if (menuItem == 5)
			{
				currentOption = EXITGAME;
			}
	}
}

void MenuScreen::Draw()
{
	int menuItem = 0;
	al_draw_text(font24, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, menuSlot[menuItem++], ALLEGRO_ALIGN_CENTRE, "Menu");
	al_draw_text(font18, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, menuSlot[menuItem++], ALLEGRO_ALIGN_CENTRE, "New Game");
	if (game->isPlayerAlive())
		al_draw_text(font18, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, menuSlot[menuItem++], ALLEGRO_ALIGN_CENTRE, "Resume Game");
	else
		al_draw_text(font18, al_map_rgb(190, 190, 190), DISPLAY_WIDTH / 2, menuSlot[menuItem++], ALLEGRO_ALIGN_CENTRE, "Resume Game");
	al_draw_text(font18, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, menuSlot[menuItem++], ALLEGRO_ALIGN_CENTRE, "High Scores");
	al_draw_text(font18, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, menuSlot[menuItem++], ALLEGRO_ALIGN_CENTRE, "Credits");
	al_draw_text(font18, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, menuSlot[menuItem++], ALLEGRO_ALIGN_CENTRE, "Exit Game");
	//al_draw_textf(font18, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, menuSlot[menuItem++], ALLEGRO_ALIGN_CENTRE, "%d", currentOption);
}

int  MenuScreen::getCurrentMenuOption()
{
	return currentOption;
}