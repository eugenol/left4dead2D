#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <allegro5/allegro_font.h>
#include "GameScreen.h"
#include "CButton.h"
#include <memory>
#include <vector>

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
	void CreateButtons();
	void NewGame() { currentOption = NEWGAME; }
	void ResumeGame();
	void HighScores() { currentOption = HIGHSCORES; }
	void Credits() { currentOption = CREDITS; }
	void ExitGame() { currentOption = EXITGAME; }

	ALLEGRO_FONT *font18 = nullptr;
	ALLEGRO_FONT *font24 = nullptr;
	ALLEGRO_FONT *font72 = nullptr;

	GameScreen *game;
	CTwoDVector mouse;
	int currentOption;

	std::vector<std::unique_ptr<CButton> > m_buttons;
};
#endif
