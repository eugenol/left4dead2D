#include "ScreenManager.h"


ScreenManager::ScreenManager()
{
	gameState = MENU;
	exitState = false;
}


ScreenManager::~ScreenManager()
{

}

ScreenManager & ScreenManager::getInstance()
{
	static ScreenManager instance;
	return instance;
}

void ScreenManager::changeGameState(int newState)
{
	gameState = newState;
	if (gameState == PLAYING)
	{
		if (newGame)
		{
			game->newGame();
			newGame = false;
		}
		else
		{
			
		}
	}
	else if (gameState == MENU)
	{

	}

}

void ScreenManager::update()
{
	switch (gameState)
	{
		case MENU:
		{
			menu->update();
			break;
		}
		case PLAYING:
		{
			game->update();
			break;
		}
	}
}

void ScreenManager::draw()
{
	switch (gameState)
	{
		case MENU:
		{
			menu->draw();
			break;
		}
		case PLAYING:
		{
			game->draw();
			break;
		}
	}
}
