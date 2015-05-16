#ifndef SCORESCREEN_H
#define SCORESCREEN_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "InputManager.h"
#include <fstream>
#include <tuple>
#include <algorithm>

class ScoreScreen
{
private:
	ALLEGRO_FONT *font18 = NULL;
	ALLEGRO_FONT *font24 = NULL;
	ALLEGRO_FONT *font72 = NULL;
	const int DISPLAY_HEIGHT = 600;
	const int DISPLAY_WIDTH = 800;
	bool returnToMenu;
	std::vector<std::pair<int, int> > highscores;
public:
	ScoreScreen(ALLEGRO_FONT *font_18, ALLEGRO_FONT *font_24, ALLEGRO_FONT *font_72);
	~ScoreScreen();
	void update();
	void draw();
	void loadData();
	bool getReturnToMenu() { return returnToMenu; }
	void setReturnToMenu() { returnToMenu = false; }
};
#endif

