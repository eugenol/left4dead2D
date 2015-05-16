#include "GameScreen.h"


GameScreen::GameScreen(ALLEGRO_BITMAP *playerImage, ALLEGRO_BITMAP *bulletImage, ALLEGRO_BITMAP *zombieImage, ALLEGRO_BITMAP *healthBarSpriteSheet, ALLEGRO_BITMAP *skullImage, ALLEGRO_BITMAP *gameoverImage) : playerSpriteSheet(playerImage), bulletSpriteSheet(bulletImage), meleeZombieSpriteSheet(zombieImage), healthBarSpriteSheet(healthBarSpriteSheet), skullImage(skullImage), gameoverImage(gameoverImage)
{
	EntityManager::getInstance().getEntityList(&objects); // send to object manager.
	font20 = al_load_font("pirulen.ttf", 20, 0);
}


GameScreen::~GameScreen()
{
	al_destroy_font(font20);
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
		int timeReduction = al_get_time()/12;//a reduction in time between spawns based on current game time
		if (timeReduction > 8)
			timeReduction = 8;
		EnemySpawnTimerMax = FPS*(3 + rand() % 6 -timeReduction);//zombies spawn every 3+rand(0->5) - reduction
		if (EnemySpawnTimerMax < 0)
			EnemySpawnTimerMax = 0;
		for (int i = 0, maxSpawns = rand(); i < (maxSpawns % 5 + al_get_time()/20); i++){//spawn a random number of zombies, increasing numbers per game time
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

	al_draw_textf(font20, al_map_rgb(255, 0, 0), 400, 300, 0, "%d", objects.size());
}

void GameScreen::newGame()
{
	 //destroy all existing entities
	EntityManager::getInstance().KillAll();
	// Create newplayer
	Player *player = new Player(0, 100, 800, 600, 100, 100, 10, 10, 0, 1, 32, PLAYER, playerSpriteSheet, bulletSpriteSheet, healthBarSpriteSheet, skullImage, gameoverImage);
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