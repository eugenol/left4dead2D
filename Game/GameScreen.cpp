#include "GameScreen.h"

GameScreen::GameScreen(ALLEGRO_BITMAP *playerImage, ALLEGRO_BITMAP *bulletImage, ALLEGRO_BITMAP *zombieImage, ALLEGRO_BITMAP *healthBarSpriteSheet, ALLEGRO_BITMAP *skullImage, ALLEGRO_BITMAP *gameoverImage, ALLEGRO_BITMAP *potionImage) : playerSpriteSheet(playerImage), bulletSpriteSheet(bulletImage), meleeZombieSpriteSheet(zombieImage), healthBarSpriteSheet(healthBarSpriteSheet), skullImage(skullImage), gameoverImage(gameoverImage), potionImage(potionImage)
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
	if (++EnemySpawnTimerCurrent >= EnemySpawnTimerMax)
	{
		EnemySpawnTimerMax = FPS*(4 + rand() % 3 )-1.7*gameTime;//zombies spawn after FPS*(random+3)-3*seconds elapsed
		if (EnemySpawnTimerMax < 3)
			EnemySpawnTimerMax = 3;
		int spawnCentre_x = rand() % DISPLAY_WIDTH;
		int spawnCentre_y = rand() % DISPLAY_HEIGHT;
		
		for (int i = 0, spawnNumber = rand() % 5 + ((int)(gameTime / 40)); i < spawnNumber; i++){
			//spawns a random number of zombies + 1 zombie per 20 seconds
			//zombies are spawned in proximity of each other, with proximity radius dependant on number spawned
			if(Enemy::getCount()<45){
				GameEntity * entity = new MeleeZombie(spawnCentre_x + (40 - rand() % 20)*(spawnNumber*1.3),
					spawnCentre_y + (40 - rand() % 20)*(spawnNumber*1.3), meleeZombieSpriteSheet);
				EntityManager::getInstance().AddEntity(entity);
			}
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