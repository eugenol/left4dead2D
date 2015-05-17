#include "ScoreScreen.h"


ScoreScreen::ScoreScreen(ALLEGRO_FONT *font_18, ALLEGRO_FONT *font_24, ALLEGRO_FONT *font_72) : font18(font_18), font24(font_24), font72(font_72)
{
	returnToMenu = false;
	loadData();
}


ScoreScreen::~ScoreScreen()
{

}

void ScoreScreen::update()
{
	int mouse_x = InputManager::getInstance().getMouseX();
	int mouse_y = InputManager::getInstance().getMouseY();

	returnToMenu = false;

	if (InputManager::getInstance().isMouseButtonPressed(LEFTM) && (mouse_x >= DISPLAY_WIDTH - 200)
		&& (mouse_x <= DISPLAY_WIDTH) && (mouse_y >= DISPLAY_HEIGHT - 38) && (mouse_y <= DISPLAY_HEIGHT))
	{
		returnToMenu = true;
	}
}

void ScoreScreen::draw()
{
	al_draw_text(font24, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, 80, ALLEGRO_ALIGN_CENTRE, "High Scores");
	al_draw_text(font18, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, 150, ALLEGRO_ALIGN_CENTRE, "Rank \t Zombies Killed \t Time Survived");
	
	int scoreCount = 0;

	for (std::vector<std::pair<int, int> >::iterator i = highscores.begin(); i != highscores.end(); i++)
	{
		scoreCount++;
		al_draw_textf(font18, al_map_rgb(255, 0, 0), 160, 180 + scoreCount * 20, ALLEGRO_ALIGN_LEFT, "%d.", scoreCount);
		al_draw_textf(font18, al_map_rgb(255, 0, 0), 325, 180 + scoreCount * 20, ALLEGRO_ALIGN_LEFT, "%d",i->first);
		al_draw_textf(font18, al_map_rgb(255, 0, 0), 555, 180 + scoreCount * 20, ALLEGRO_ALIGN_LEFT, "%d", i->second);
	}

	al_draw_text(font18, al_map_rgb(255, 0, 0), DISPLAY_WIDTH - 100, DISPLAY_HEIGHT - 28, ALLEGRO_ALIGN_CENTRE, "Main Menu");
}

void ScoreScreen::loadData()
{
	std::fstream file("highscores.txt");
	std::vector<std::pair<int, int> > loadhighscores;
	int scorecount = 0;
	std::string line;

	while (std::getline(file,line))
	{
		std::stringstream linestream(line);
		std::pair<int, int> temp;
		linestream >> temp.first >> temp.second;
		loadhighscores.push_back(temp);
	}
	file.close();

	std::sort(loadhighscores.rbegin(), loadhighscores.rend());

	if (loadhighscores.size() > 10)
	{
		std::vector<std::pair<int, int> >::const_iterator first = loadhighscores.begin();
		std::vector<std::pair<int, int> >::const_iterator last = loadhighscores.begin() + 10;
		std::vector<std::pair<int, int> > temphighscores(first, last);

		highscores.clear();
		for (std::vector<std::pair<int, int> >::iterator i = temphighscores.begin(); i != temphighscores.end(); i++)
		{
			highscores.push_back(*i);
		}
	}
	else
	{
		std::vector<std::pair<int, int> >::const_iterator first = loadhighscores.begin();
		std::vector<std::pair<int, int> >::const_iterator last = loadhighscores.end();
		std::vector<std::pair<int, int> > temphighscores(first, last);

		highscores.clear();
		for (std::vector<std::pair<int, int> >::iterator i = temphighscores.begin(); i != temphighscores.end(); i++)
		{
			highscores.push_back(*i);
		}
	}

	file.open("highscores.txt");

	for (std::vector<std::pair<int, int> >::iterator i = highscores.begin(); i != highscores.end(); i++)
	{
		file << i->first << " " << i->second << std::endl;
	}

	file.close();

}