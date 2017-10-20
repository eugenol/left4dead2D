#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H
#include "GameScreen.h"
#include "MenuScreen.h"
#include "InputManager.h"
#include "CreditScreen.h"
#include "ScoreScreen.h"
#include "DeathScreen.h"

class ScreenManager
{
public:
	enum GAMESTATE { MENU, PLAYING, CREDITS, DIED, HIGHSCORES };
	static ScreenManager & getInstance();
	~ScreenManager();
	void changeGameState( GAMESTATE newState );

	void addGameScreen(GameScreen *gameScreen) { game = gameScreen; }
	void addMenuScreen(MenuScreen *menuScreen) { menu = menuScreen; m_currentScreen = menu; }
	void addCreditScreen(CreditScreen *creditScreen) { credits = creditScreen; }
	void addScoreScreen(ScoreScreen *scoreScreen) { scores = scoreScreen; }
	void addDeathScreen(DeathScreen *deathScreen) { death = deathScreen; }

	void Update();
	void Draw();

	void setNewGame() { newGame = true; }
	int getScreenState() { return gameState; }
	bool getExitState() { return exitState; }
	void setExitState(bool done) { exitState = done; }
	bool isGameActive() { return game->isPlayerAlive(); }

	//Can't use these methods to accidentally copy the screen manager.
	ScreenManager(ScreenManager const&) = delete;
	void operator=(ScreenManager const&) = delete;

private:
	GAMESTATE gameState;
	bool exitState;
	bool newGame = false;
	GameScreen *game;
	MenuScreen *menu;
	CreditScreen *credits;
	ScoreScreen *scores;
	DeathScreen *death;
	ScreenManager();

	CScreen* m_currentScreen;
};
#endif