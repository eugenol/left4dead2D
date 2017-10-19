#include "MenuScreen.h"


MenuScreen::MenuScreen(ALLEGRO_FONT *font_18, ALLEGRO_FONT *font_24, ALLEGRO_FONT *font_72, GameScreen *current_game) : font18(font_18), font24(font_24), font72(font_72), game(current_game)
{
	ALLEGRO_COLOR buttonColor = al_map_rgb(255, 0, 0);
	ALLEGRO_COLOR disabledButtonColor = al_map_rgb(190, 190, 190);

	//callbacks for the buttons
	auto callback1 = std::bind(&MenuScreen::NewGame, this);
	m_buttons.emplace_back(CTwoDVector(DISPLAY_WIDTH / 2, 80), 200, 40, "New Game", font_18, buttonColor, callback1);
	auto callback2 = std::bind(&MenuScreen::ResumeGame, this);
	auto diableCheck = [this]()->bool
											{
												if (this->game->isPlayerAlive())
												{
													return false;
												}
												else
												{
													return true;
												}
											};
	m_buttons.emplace_back(CTwoDVector(DISPLAY_WIDTH / 2, 120), 200, 40, "Resume Game", font_18, buttonColor, callback2, diableCheck, disabledButtonColor);
	auto callback3 = std::bind(&MenuScreen::HighScores, this);
	m_buttons.emplace_back(CTwoDVector(DISPLAY_WIDTH / 2, 160), 200, 40, "High Scores", font_18, buttonColor, callback3);
	auto callback4 = std::bind(&MenuScreen::Credits, this);
	m_buttons.emplace_back(CTwoDVector(DISPLAY_WIDTH / 2, 200), 200, 40, "Credits", font_18, buttonColor, callback4);
	auto callback5 = std::bind(&MenuScreen::ExitGame, this);
	m_buttons.emplace_back(CTwoDVector(DISPLAY_WIDTH / 2, 240), 200, 40, "Exit Game", font_18, buttonColor, callback5);
}


MenuScreen::~MenuScreen()
{
}

void MenuScreen::Update()
{
	mouse = InputManager::getInstance().GetMousePosition();

	currentOption = STAYMENU;

	if (InputManager::getInstance().isMouseButtonPressed(LEFTM))
	{
		for( Button& button : m_buttons )
		{
			button.OnClicked( mouse );
		}
	}
}

void MenuScreen::Draw()
{
	
	al_draw_text(font24, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, 20 , ALLEGRO_ALIGN_CENTRE, "Menu");

	//m_buttons[0].Draw();
	//if (game->isPlayerAlive())
	//{
	//	m_buttons[1].Draw();
	//}
	//else
	//{
	//	m_buttons[1].Draw(al_map_rgb(190, 190, 190));
	//}
	//m_buttons[2].Draw();
	//m_buttons[3].Draw();
	//m_buttons[4].Draw();

	for( Button& button : m_buttons )
	{
		button.Draw();
	}
}

int  MenuScreen::getCurrentMenuOption()
{
	return currentOption;
}

void MenuScreen::ResumeGame()
{
	if(game->isPlayerAlive())
	{
		currentOption = RESUMEGAME;
	}
	else
	{
		currentOption = STAYMENU;
	}
}
