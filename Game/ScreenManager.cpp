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
		m_currentScreen = game;
	}
	else if (gameState == MENU)
	{
		m_currentScreen = menu;
	}
	else if (gameState == DIED)
	{
		EntityManager::getInstance().KillAll();
		m_currentScreen = death;
	}
	else if (gameState == HIGHSCORES)
	{
		scores->LoadData();
		m_currentScreen = scores;
	}
	else if (gameState == CREDITS)
	{
		m_currentScreen = credits;
	}
}

void ScreenManager::Update()
{
	m_currentScreen->Update();
	
	if (gameState == PLAYING && !game->isPlayerAlive())
	{
		changeGameState(DIED);
	}
}

void ScreenManager::Draw()
{
	m_currentScreen->Draw();
}
