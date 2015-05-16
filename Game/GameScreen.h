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
#include "InitData.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "mappy_A5.h"
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#pragma warning (disable : 4996)
class GameScreen
{
private:
	const int DISPLAY_HEIGHT = 600;
	const int DISPLAY_WIDTH = 800;
	int FPS = 60; //Framerate
	ALLEGRO_BITMAP *playerSpriteSheet = NULL;
	ALLEGRO_BITMAP *bulletSpriteSheet = NULL;
	ALLEGRO_BITMAP *healthBarSpriteSheet = NULL;
	ALLEGRO_BITMAP *gameoverImage = NULL;
	ALLEGRO_BITMAP *skullImage = NULL;
	ALLEGRO_BITMAP *meleeZombieSpriteSheet = NULL;
	int EnemySpawnTimerMax = FPS*(3 + rand() % 3);
	int EnemySpawnTimerCurrent = 0;
	std::list<GameEntity*> objects;
	ALLEGRO_FONT *font20;
public:
	GameScreen(ALLEGRO_BITMAP *playerImage, ALLEGRO_BITMAP *bulletImage, ALLEGRO_BITMAP *zombieImage, ALLEGRO_BITMAP *healthBarSpriteSheet, ALLEGRO_BITMAP *skullImage, ALLEGRO_BITMAP *gameoverImage);
	~GameScreen();
	void newGame();
	void update();
	void draw();
	bool isPlayerAlive();
};
#endif
