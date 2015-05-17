#include "GameScreen.h"
#include <cmath>

GameScreen::GameScreen(ALLEGRO_BITMAP *playerImage, ALLEGRO_BITMAP *bulletImage, ALLEGRO_BITMAP *zombieImage, ALLEGRO_BITMAP *healthBarSpriteSheet, ALLEGRO_BITMAP *skullImage, ALLEGRO_BITMAP *gameoverImage, ALLEGRO_BITMAP *potionImage, ALLEGRO_BITMAP *zombieDeathAnimationSpriteSheet_m) : playerSpriteSheet(playerImage), bulletSpriteSheet(bulletImage), meleeZombieSpriteSheet(zombieImage), healthBarSpriteSheet(healthBarSpriteSheet), skullImage(skullImage), gameoverImage(gameoverImage), potionImage(potionImage), zombieDeathAnimationSpriteSheet(zombieDeathAnimationSpriteSheet_m)
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
	if (gameTimeUpdateCounter++ == 60)
	{
		gameTime++;
		gameTimeUpdateCounter = 0;
	}
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
	spawnEnemies();
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
	Player *player = new Player(0, 100, 800, 600, 100, 100, 10, 10, 0, 1, 32, PLAYER, playerSpriteSheet, bulletSpriteSheet, healthBarSpriteSheet, skullImage, gameoverImage, potionImage);
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

void GameScreen::spawnEnemies(){
	if (++EnemySpawnTimerCurrent >= EnemySpawnTimerMax)
	{
		EnemySpawnTimerMax = FPS*(4 + rand() % 4 - logf(gameTime * 5) / 3);//zombies spawn after FPS*(random+3)-3*seconds elapsed
		if (EnemySpawnTimerMax < 3)
			EnemySpawnTimerMax = 3;
		int spawnCentre_x = rand() % DISPLAY_WIDTH;
		int spawnCentre_y = rand() % DISPLAY_HEIGHT;
		//spawns a random number of zombies + 1 zombie per 40 seconds
		int spawnNumber = rand() % 5 + ((int)(gameTime / 40));
		if (spawnNumber > 6)
			spawnNumber = 6;
		int diffLevel = gameTime / 30;//difficulty level
		if (diffLevel > 3)
			diffLevel = 3;
		for (int i = 0; i < spawnNumber; i++){
			//zombies are spawned in proximity of each other, with proximity radius dependant on number spawned
			if (Enemy::getCount()<40){//max number of zombies allowed
				GameEntity * entity = new MeleeZombie(spawnCentre_x + (40 - rand() % 20)*(spawnNumber*3),
					spawnCentre_y + (40 - rand() % 20)*(spawnNumber*3), diffLevel, meleeZombieSpriteSheet, zombieDeathAnimationSpriteSheet);
				EntityManager::getInstance().AddEntity(entity);
			}
		}
		EnemySpawnTimerCurrent = 0;
		if (spawnNumber < 4)
			EnemySpawnTimerMax /= 2;
	}

}