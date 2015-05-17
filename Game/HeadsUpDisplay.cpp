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
}


HeadsUpDisplay::~HeadsUpDisplay()
{
	al_destroy_font(Scorefont20);
}

void HeadsUpDisplay::Update(int health, int lives, int score, int megashotCount)
{
	this->health = health;
	this->lives = lives;
	this->score = score;
	this->megaShotCount = megashotCount;
}

void HeadsUpDisplay::draw()
{
	al_draw_textf(Scorefont20, al_map_rgb(255, 0, 0), 0, 560, 0, "Zombies Killed: %i", score);
	al_draw_textf(Scorefont20, al_map_rgb(255, 0, 0), 0, 580, 0, "MegaShots Stored: %i", megaShotCount);
}
