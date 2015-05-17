#include "HeadsUpDisplay.h"
#include <allegro5\allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

HeadsUpDisplay::HeadsUpDisplay()
{
	Scorefont20 = al_load_ttf_font("pirulen.ttf", 20, 0);
	health = 0;
	lives = 0;
	score = 0;
	megaShotCount = 0;

	//animation initialisation
	//megaShotCountStar = al_load_bitmap("stars_3.png");
	megaShotCountStar = al_load_bitmap("stars_2.png");
	animationFrameHeight = 64;
	animationFrameWidth = 64;
	currentAnimationFrame = 0;
	frameCount = 0;
	frameDelay = 3;
	maxFrameCount = 6;
	rotationAngle = 0;
}


HeadsUpDisplay::~HeadsUpDisplay()
{
	al_destroy_font(Scorefont20); 
	al_destroy_bitmap(megaShotCountStar);
}

void HeadsUpDisplay::Update(int health, int lives, int score, int megashotCount)
{
	animationUpdate();
	this->health = health;
	this->lives = lives;
	this->score = score;
	this->megaShotCount = megashotCount;
}

void HeadsUpDisplay::draw()
{
	al_draw_textf(Scorefont20, al_map_rgb(255, 0, 0), 0, 560, 0, "Zombies Killed: %i", score);
	al_draw_textf(Scorefont20, al_map_rgb(255, 0, 0), 0, 580, 0, "MegaShots Stored: %i", megaShotCount);
	//al_draw_bitmap_region(megaShotCountStar, currentAnimationFrame*animationFrameWidth, 0, animationFrameWidth, animationFrameHeight, 200, 200, 0);
	al_draw_tinted_scaled_rotated_bitmap_region(megaShotCountStar, currentAnimationFrame*animationFrameWidth, 0, animationFrameWidth, animationFrameHeight, al_map_rgb(rand() % 256, rand() % 256, rand() % 256), animationFrameHeight / 2, animationFrameWidth / 2, 400, 580, 1, 1, rotationAngle, 0);
}

void HeadsUpDisplay::animationUpdate()
{
	//Generates /Advances Animation
	if (++frameCount >= frameDelay)
	{
		if ((rotationAngle += 30) == 360)
		{
			rotationAngle = 0;
		}
		if (++currentAnimationFrame >= maxFrameCount)
			currentAnimationFrame = minFrameCount;
		frameCount = 0;
	}
}