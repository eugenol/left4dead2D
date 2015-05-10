#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H
#include "GameScreen.h"
#include "MenuScreen.h"

class ScreenManager
{
private:
	int gameState;
	bool exitState;
	GameScreen *game;
	MenuScreen *menu;
	ScreenManager();

public:
	enum GAMESTATE{ MENU, PLAYING, DIED, HIGHSCORES};
	static ScreenManager & getInstance();
	~ScreenManager();
	void changeGameState(int newState);

	void addGameScreen(GameScreen *gameScreen) { game = gameScreen; }
	void addMenuScreen(MenuScreen *menuScreen) { menu = menuScreen; }
	//void addGameScreen(GameScreen *gameScreen) { game = gameScreen; }

	bool getExitState(){ return exitState; }
};
#endif