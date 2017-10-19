#include "ScreenManager.h"


ScreenManager::ScreenManager()
{
	gameState = MENU;
	exitState = false;
}


ScreenManager::~ScreenManager()
{

}

ScreenManager& ScreenManager::getInstance()
{
	static ScreenManager instance;
	return instance;
}

void ScreenManager::changeGameState(GAMESTATE newState)
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
		scores->LoadData();
	}

}

void ScreenManager::update()
{
	switch (gameState)
	{
		case MENU:
		{
			menu->Update();
			break;
		}
		case PLAYING:
		{
			game->Update();
			if (!game->isPlayerAlive())
				changeGameState(DIED);
			break;
		}
		case CREDITS:
		{
			credits->Update();
			break;
		}
		case DIED:
		{
			death->Update();
			break;
		}
		case HIGHSCORES:
		{
			scores->Update();
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
			menu->Draw();
			break;
		}
		case PLAYING:
		{
			game->Draw();
			break;
		}
		case CREDITS:
		{
			credits->Draw();
			break;
		}
		case DIED:
		{
			death->Draw();
			break;
		}
		case HIGHSCORES:
		{
			scores->Draw();
			break;
		}
	}
}
