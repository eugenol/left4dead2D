#include "GameScreen.h"
#include "mappy_A5.h"
#include "MeleeZombie.h"
#include "CAIZombie.h"

GameScreen::GameScreen(ALLEGRO_BITMAP *bulletImage, ALLEGRO_BITMAP *zombieImage, ALLEGRO_BITMAP *healthBarSpriteSheet, ALLEGRO_BITMAP *skullImage, ALLEGRO_BITMAP *gameoverImage, ALLEGRO_BITMAP *potionImage, ALLEGRO_BITMAP *zombieDeathAnimationSpriteSheet_m) : bulletSpriteSheet(bulletImage), meleeZombieSpriteSheet(zombieImage), healthBarSpriteSheet(healthBarSpriteSheet), skullImage(skullImage), gameoverImage(gameoverImage), potionImage(potionImage), zombieDeathAnimationSpriteSheet(zombieDeathAnimationSpriteSheet_m)
{
	EntityManager::getInstance().getEntityList(&objects); // send to object manager.
}


GameScreen::~GameScreen()
{

}


void GameScreen::Update()
{	
	if (gameTimeUpdateCounter++ == 60)
	{
		gameTime++;
		gameTimeUpdateCounter = 0;
	}

	//Kinda Stupid For now, but maybe better for future?
	prevRunningTime = runningTime;
	runningTime += 1.0 / FPS;
	deltaTime = runningTime - prevRunningTime;

	for(GameEntity* object : objects)
	{
		object->Update( deltaTime );
	}
	//for (std::list<GameEntity*>::iterator iter = objects.begin(); iter != objects.end(); iter++)
	//	(*iter)->Update();

	//Check for collisions... Not the most efficient, but ok for now. can be changed later...
	//for now it campares every object, I can make it sector based later...
	for (std::list<GameEntity*>::iterator iter1 = objects.begin(); iter1 != objects.end(); iter1++)
	{
		for (std::list<GameEntity*>::iterator iter2 = objects.begin(); iter2 != objects.end(); iter2++)
		{
			if (iter1 != iter2) // Can't collide with yourself
			{
				if ((*iter1)->SameRegion(*iter2)) //Same Region?
				{
					if ((*iter1)->CheckCollision(*iter2)) //Did you collide?
					{
						(*iter1)->Collided(*iter2); //Do something about it.
					}
				}
			}
		}
	}

	SpawnEnemies();

	// Update the entity manager to remove the dead.
	EntityManager::getInstance().UpdateList();
}

void GameScreen::Draw()
{
	// Draw map
	MapDrawBG(20, 20, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);

	//draw objects
	for (GameEntity* object : objects)
	{
		object->Draw();
	}
	//for (std::list<GameEntity*>::iterator iter = objects.begin(); iter != objects.end(); iter++)
	//	(*iter)->Draw();
}

void GameScreen::newGame()
{
	 //destroy all existing entities
	EntityManager::getInstance().KillAll();
	// Create newplayer
	CTwoDVector playerStartPosition(100, 100);
	GameEntity* player = EntityManager::getInstance().MakeEntity<Player>(0, 100, playerStartPosition, 10, 10, 0, 1, 32, PLAYER, bulletSpriteSheet, healthBarSpriteSheet, skullImage, gameoverImage, potionImage);
	gameTime = 0;
	gameTimeUpdateCounter = 0;
	EntityManager::getInstance().AddEntity(player);
	Enemy::setPlayer(dynamic_cast<Player*>(player));

	CTwoDVector zombieStartPosition(400, 300);
	GameEntity* zombie = EntityManager::getInstance().MakeEntity<CAIZombie>(zombieStartPosition, meleeZombieSpriteSheet, zombieDeathAnimationSpriteSheet);
	EntityManager::getInstance().AddEntity(zombie);
}

void GameScreen::SpawnEnemies()
{
	//Attempt to create new enemy
	if (++EnemySpawnTimerCurrent >= EnemySpawnTimerMax)
	{
		EnemySpawnTimerMax = FPS*(4 + rand() % 4 - logf(gameTime * 5) / 3);//zombies spawn after FPS*(random+3)-3*seconds elapsed
		if (EnemySpawnTimerMax < 3)
			EnemySpawnTimerMax = 3;

		CTwoDVector spawnCentre(rand() % DISPLAY_WIDTH, rand() % DISPLAY_HEIGHT);
		//spawns a random number of zombies + 1 zombie per 40 seconds
		int spawnNumber = rand() % 5 + static_cast< int >(gameTime / 40);
		if (spawnNumber > 6)
			spawnNumber = 6;
		int diffLevel = gameTime / 30;//difficulty level
		if (diffLevel > 3)
			diffLevel = 3;
		for (int i = 0; i < spawnNumber; i++)
		{
			//zombies are spawned in proximity of each other, with proximity radius dependant on number spawned
			if (Enemy::getCount()<40) //max number of zombies allowed
			{
				CTwoDVector spawnOffset((40 - rand() % 20)*(spawnNumber*1.3), (40 - rand() % 20)*(spawnNumber*1.3));
				CTwoDVector zombieSpawnPoint = spawnCentre + spawnOffset;
				GameEntity* entity = EntityManager::getInstance().MakeEntity<MeleeZombie>(zombieSpawnPoint, diffLevel,
					meleeZombieSpriteSheet, zombieDeathAnimationSpriteSheet);
				EntityManager::getInstance().AddEntity(entity);
			}
		}
		EnemySpawnTimerCurrent = 0;
		if (spawnNumber < 4)
			EnemySpawnTimerMax /= 2;
	}
}

bool GameScreen::isPlayerAlive()
{
	for (GameEntity* object : objects)
	{
		if(object->getID() == PLAYER)
		{
			return true;
		}
	}
	return false;

	//for (std::list<GameEntity*>::iterator iter = objects.begin(); iter != objects.end(); iter++)
	//{
	//	if ((*iter)->getID() == PLAYER)
	//		return true;
	//}
	//return false;
}
