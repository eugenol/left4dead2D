#include "GameScreen.h"
#include "mappy_A5.h"
#include "MeleeZombie.h"
#include "CAIZombie.h"

GameScreen::GameScreen(ALLEGRO_BITMAP *bulletImage, ALLEGRO_BITMAP *zombieImage, ALLEGRO_BITMAP *zombieDeathAnimationSpriteSheet_m) 
:
bulletSpriteSheet(bulletImage), meleeZombieSpriteSheet(zombieImage), zombieDeathAnimationSpriteSheet(zombieDeathAnimationSpriteSheet_m)
{
	EnemySpawnTimerMax = (3 + rand() % 3);
	EnemySpawnTimerCurrent = 0;
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

	EntityManager::getInstance().Update( deltaTime );

	EntityManager::getInstance().DoCollisions();

	SpawnEnemies( deltaTime );

	// Update the entity manager to remove the dead.
	EntityManager::getInstance().UpdateList();
}

void GameScreen::Draw()
{
	// Draw map
	MapDrawBG(20, 20, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);

	//draw objects
	EntityManager::getInstance().Draw();
}

void GameScreen::newGame()
{
	 //destroy all existing entities
	EntityManager::getInstance().KillAll();
	// Create newplayer
	CTwoDVector playerStartPosition(100, 100);
	GameEntity* player = EntityManager::getInstance().MakeEntity<Player>(0, 100, playerStartPosition, 10, 10, 1, 32, PLAYER, bulletSpriteSheet);
	GameEntity* HUD = EntityManager::getInstance().MakeEntity<HeadsUpDisplay>();

	dynamic_cast<Player*>(player)->AddObserver(dynamic_cast<HeadsUpDisplay*>(HUD));

	gameTime = 0;
	gameTimeUpdateCounter = 0;
	runningTime = 0.0;


	CTwoDVector zombieStartPosition(400, 300);
	GameEntity* zombie = EntityManager::getInstance().MakeEntity<CAIZombie>(zombieStartPosition, meleeZombieSpriteSheet, zombieDeathAnimationSpriteSheet);
}

void GameScreen::SpawnEnemies( double deltaTime )
{
	EnemySpawnTimerCurrent += deltaTime;

	//Attempt to create new enemy
	if( EnemySpawnTimerCurrent >= EnemySpawnTimerMax )
	{
		EnemySpawnTimerMax = 4 + rand() % 4 - log(runningTime * 5) / 3;//zombies spawn after FPS*(random+3)-3*seconds elapsed
		if (EnemySpawnTimerMax < 3)
			EnemySpawnTimerMax = 3;

		CTwoDVector spawnCentre(rand() % DISPLAY_WIDTH, rand() % DISPLAY_HEIGHT);
		//spawns a random number of zombies + 1 zombie per 40 seconds
		int spawnNumber = rand() % 5 + static_cast< int >(runningTime / 40);
		if (spawnNumber > 6)
			spawnNumber = 6;
		int diffLevel = runningTime / 30;//difficulty level
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
			}
		}
		EnemySpawnTimerCurrent = 0;
		if (spawnNumber < 4)
			EnemySpawnTimerMax /= 2;
	}
}

bool GameScreen::isPlayerAlive()
{
	GameEntity* player = EntityManager::getInstance().GetPlayer();

	if (player && player->getAlive())
	{
		return true;
	}

	return false;
}
