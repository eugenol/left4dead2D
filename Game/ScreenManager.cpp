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
