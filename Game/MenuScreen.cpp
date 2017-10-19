#include "MenuScreen.h"
#include "CDisableableButton.h"
#include "InputManager.h"


MenuScreen::MenuScreen(ALLEGRO_FONT *font_18, ALLEGRO_FONT *font_24, ALLEGRO_FONT *font_72, GameScreen *current_game) : font18(font_18), font24(font_24), font72(font_72), game(current_game)
{
	CreateButtons();
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
		for (std::unique_ptr<CButton>& button : m_buttons)
		{
			button->OnClicked( mouse );
		}
	}
}

void MenuScreen::Draw()
{
	
	al_draw_text(font24, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, 20 , ALLEGRO_ALIGN_CENTRE, "Menu");

	for(std::unique_ptr<CButton>& button : m_buttons )
	{
		button->Draw();
	}
}

int  MenuScreen::getCurrentMenuOption()
{
	return currentOption;
}

void MenuScreen::CreateButtons()
{
	ALLEGRO_COLOR buttonColor = al_map_rgb(255, 0, 0);
	ALLEGRO_COLOR disabledButtonColor = al_map_rgb(190, 190, 190);

	//callbacks for the buttons
	auto callback1 = std::bind(&MenuScreen::NewGame, this);
	std::unique_ptr<CButton> button1 = std::make_unique<CButton>(CTwoDVector(DISPLAY_WIDTH / 2, 80), 200, 40, "New Game", font18, buttonColor, callback1);
	m_buttons.push_back(std::move(button1));

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
	std::unique_ptr<CButton> button2 = std::make_unique<CDisableableButton>(CTwoDVector(DISPLAY_WIDTH / 2, 120), 200, 40, "Resume Game", font18, buttonColor, callback2, diableCheck, disabledButtonColor);
	m_buttons.push_back(std::move(button2));


	auto callback3 = std::bind(&MenuScreen::HighScores, this);
	std::unique_ptr<CButton> button3 = std::make_unique<CButton>(CTwoDVector(DISPLAY_WIDTH / 2, 160), 200, 40, "High Scores", font18, buttonColor, callback3);
	m_buttons.push_back(std::move(button3));

	auto callback4 = std::bind(&MenuScreen::Credits, this);
	std::unique_ptr<CButton> button4 = std::make_unique<CButton>(CTwoDVector(DISPLAY_WIDTH / 2, 200), 200, 40, "Credits", font18, buttonColor, callback4);
	m_buttons.push_back(std::move(button4));

	auto callback5 = std::bind(&MenuScreen::ExitGame, this);
	std::unique_ptr<CButton> button5 = std::make_unique<CButton>(CTwoDVector(DISPLAY_WIDTH / 2, 240), 200, 40, "Exit Game", font18, buttonColor, callback5);
	m_buttons.push_back(std::move(button5));
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