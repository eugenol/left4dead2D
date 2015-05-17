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
	else if (gameState == DIED)
	{
		EntityManager::getInstance().KillAll();
	}
	else if (gameState == HIGHSCORES)
	{
		scores->loadData();
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
			if (!game->isPlayerAlive())
				changeGameState(DIED);
			break;
		}
		case CREDITS:
		{
			credits->update();
			break;
		}
		case DIED:
		{
			death->update();
			break;
		}
		case HIGHSCORES:
		{
			scores->update();
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
		case CREDITS:
		{
			credits->draw();
			break;
		}
		case DIED:
		{
			death->draw();
			break;
		}
		case HIGHSCORES:
		{
			scores->draw();
			break;
		}
	}
}
