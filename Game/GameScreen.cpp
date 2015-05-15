#include "GameScreen.h"


GameScreen::GameScreen(ALLEGRO_BITMAP *playerImage, ALLEGRO_BITMAP *bulletImage, ALLEGRO_BITMAP *zombieImage) : playerSpriteSheet(playerImage), bulletSpriteSheet(bulletImage), meleeZombieSpriteSheet(zombieImage)
{
	EntityManager::getInstance().getEntityList(&objects); // send to object manager.
}


GameScreen::~GameScreen()
{
}


void GameScreen::update()
{
	for (std::list<GameEntity*>::iterator iter = objects.begin(); iter != objects.end(); iter++)
		(*iter)->update();

	//Check for collisions... Not the most efficient, but ok for now. can be changed later...
	//for now it campares every object, I can make it sector based later...
	for (std::list<GameEntity*>::iterator iter1 = objects.begin(); iter1 != objects.end(); iter1++)
	{
		for (std::list<GameEntity*>::iterator iter2 = objects.begin(); iter2 != objects.end(); iter2++)
		{
			if (iter1 != iter2) // Can't collide with yourself
			{
				if ((*iter1)->CheckCollision(*iter2)) //Did you collide?
					(*iter1)->Collided(*iter2); //Do something about it.
			}
		}
	}

	//Attempt to create new enemy
	if (++EnemySpawnTimerCurrent == EnemySpawnTimerMax)
	{
		EnemySpawnTimerMax = FPS*(10 + rand() % 4);
		for (int i = 0, maxSpawns = rand(); i < (maxSpawns % 5); i++){
			GameEntity * entity = new MeleeZombie(rand() % DISPLAY_WIDTH, rand() % DISPLAY_HEIGHT, meleeZombieSpriteSheet);
			EntityManager::getInstance().AddEntity(entity);
		}
		EnemySpawnTimerCurrent = 0;
	}
	// Update the entity manager to remove the dead.
	EntityManager::getInstance().UpdateList();
}

void GameScreen::draw()
{
	// Draw map
	// Draw map
	MapDrawBG(20, 20, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	//draw objects
	for (std::list<GameEntity*>::iterator iter = objects.begin(); iter != objects.end(); iter++)
		(*iter)->draw();
}

void GameScreen::newGame()
{
	 //destroy all existing entities
	EntityManager::getInstance().KillAll();
	// Create newplayer
	Player *player = new Player(0, 100, 800, 600, 100, 100, 10, 10, 0, 1, 32, PLAYER, playerSpriteSheet, bulletSpriteSheet);
	EntityManager::getInstance().AddEntity(player);
	Enemy::setPlayer(player);
}

bool GameScreen::isPlayerAlive()
{
	for (std::list<GameEntity*>::iterator iter = objects.begin(); iter != objects.end(); iter++)
	{
		if ((*iter)->getID() == PLAYER)
			return true;
	}
	return false;
}