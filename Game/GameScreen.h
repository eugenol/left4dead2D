#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "GameEntity.h"
#include "Enemy.h"
#include "MeleeZombie.h"
#include "InputManager.h"
#include "Player.h"
#include "EntityManager.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "mappy_A5.h"
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#pragma warning (disable : 4996)
class GameScreen
{
public:
	GameScreen(ALLEGRO_BITMAP *bulletImage, ALLEGRO_BITMAP *zombieImage, ALLEGRO_BITMAP *healthBarSpriteSheet, ALLEGRO_BITMAP *skullImage, ALLEGRO_BITMAP *gameoverImage, ALLEGRO_BITMAP *potionImage, ALLEGRO_BITMAP *zombieDeathAnimationSpriteSheet_m);
	~GameScreen();
	void newGame();
	void Update();
	void Draw();
	bool isPlayerAlive();

private:
	const int DISPLAY_HEIGHT = 600;
	const int DISPLAY_WIDTH = 800;
	int FPS = 60; //Framerate
	ALLEGRO_BITMAP *playerSpriteSheet = nullptr;
	ALLEGRO_BITMAP *bulletSpriteSheet = nullptr;
	ALLEGRO_BITMAP *healthBarSpriteSheet = nullptr;
	ALLEGRO_BITMAP *gameoverImage = nullptr;
	ALLEGRO_BITMAP *skullImage = nullptr;
	ALLEGRO_BITMAP *potionImage = nullptr;
	ALLEGRO_BITMAP *meleeZombieSpriteSheet = nullptr;
	ALLEGRO_BITMAP *zombieDeathAnimationSpriteSheet = nullptr;
	int EnemySpawnTimerMax = FPS*(3 + rand() % 3);
	int EnemySpawnTimerCurrent = 0;
	std::list<GameEntity*> objects;
};
#endif
