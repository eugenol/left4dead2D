#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "GameEntity.h"
#include "EntityManager.h"
#include "CScreen.h"
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#pragma warning (disable : 4996)

class GameScreen : public CScreen
{
public:
	GameScreen(ALLEGRO_BITMAP *bulletImage, ALLEGRO_BITMAP *zombieImage, ALLEGRO_BITMAP *zombieDeathAnimationSpriteSheet_m);
	~GameScreen();
	void newGame();
	void SpawnEnemies( double deltaTime );
	void Update();
	void Draw();
	bool isPlayerAlive();

private:
	ALLEGRO_BITMAP *playerSpriteSheet = nullptr;
	ALLEGRO_BITMAP *bulletSpriteSheet = nullptr;
	ALLEGRO_BITMAP *meleeZombieSpriteSheet = nullptr;
	ALLEGRO_BITMAP *zombieDeathAnimationSpriteSheet = nullptr;
	double EnemySpawnTimerMax;
	double EnemySpawnTimerCurrent;

	double runningTime = 0;
	double prevRunningTime = 0;
	double deltaTime = 0;
};
#endif
