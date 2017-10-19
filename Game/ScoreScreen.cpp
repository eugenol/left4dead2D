#include "ScoreScreen.h"
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Common.h"


ScoreScreen::ScoreScreen(ALLEGRO_FONT *font_18, ALLEGRO_FONT *font_24, ALLEGRO_FONT *font_72) : font18(font_18), font24(font_24), font72(font_72)
{
	returnToMenu = false;

	CTwoDVector buttonLocation(DISPLAY_WIDTH - 100, DISPLAY_HEIGHT - 28);
	ALLEGRO_COLOR buttonColor = al_map_rgb(255, 0, 0);
	auto callback = [this]() {this->returnToMenu = true; };
	m_button = std::make_unique<CButton>(buttonLocation, 200, 38, "Main Menu", font_18, buttonColor, callback);

	LoadData();
}


ScoreScreen::~ScoreScreen()
{

}

void ScoreScreen::Update()
{
	CTwoDVector mouse = InputManager::getInstance().GetMousePosition();

	returnToMenu = false;

	if (InputManager::getInstance().isMouseButtonPressed(LEFTM))
	{
		m_button->OnClicked(mouse);
	}
}

void ScoreScreen::Draw()
{
	al_draw_text(font24, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, 80, ALLEGRO_ALIGN_CENTRE, "High Scores");
	al_draw_text(font18, al_map_rgb(255, 0, 0), DISPLAY_WIDTH / 2, 150, ALLEGRO_ALIGN_CENTRE, "Rank \t Zombies Killed \t Time Survived");
	
	int scoreCount = 0;

	for (std::vector<std::pair<int, int> >::iterator i = highscores.begin(); i != highscores.end(); i++)
	{
		scoreCount++;
		al_draw_textf(font18, al_map_rgb(255, 0, 0), 160, 180 + scoreCount * 20, ALLEGRO_ALIGN_LEFT, "%d.", scoreCount);
		al_draw_textf(font18, al_map_rgb(255, 0, 0), 325, 180 + scoreCount * 20, ALLEGRO_ALIGN_LEFT, "%d",i->first);

		int minutes = i->second / 60;
		int seconds = i->second % 60;

		std::string time = minutes < 10 ? "0" : "";
		time += std::to_string(minutes);
		time += ":";
		time += seconds < 10 ? "0" : "";
		time += std::to_string(seconds);

		al_draw_textf(font18, al_map_rgb(255, 0, 0), 555, 180 + scoreCount * 20, ALLEGRO_ALIGN_LEFT, "%s", time.c_str());
	}

	m_button->Draw();
}

void ScoreScreen::LoadData()
{
	std::fstream file("highscores.txt");
	std::vector<std::pair<int, int> > loadhighscores;
	std::string line;

	while (std::getline(file,line))
	{
		std::stringstream linestream(line);
		std::pair<int, int> temp;
		linestream >> temp.first >> temp.second;
		loadhighscores.push_back(temp);
	}
	file.close();

	std::sort(loadhighscores.rbegin(), loadhighscores.rend(), [](std::pair<int, int>& a, std::pair<int, int>& b) -> bool { return a.first < b.first; } );

	if (loadhighscores.size() > 10)
	{
		highscores.clear();
		for (std::vector<std::pair<int, int> >::iterator i = loadhighscores.begin(); i != loadhighscores.begin()+10; ++i)
		{
			highscores.push_back(*i);
		}
	}
	else
	{
		highscores.clear();
		for (std::vector<std::pair<int, int> >::iterator i = loadhighscores.begin(); i != loadhighscores.end(); ++i)
		{
			highscores.push_back(*i);
		}
	}

	file.open("highscores.txt");
	for (std::vector<std::pair<int, int> >::iterator i = highscores.begin(); i != highscores.end(); ++i)
	{
		file << i->first << " " << i->second << std::endl;
	}

	file.close();

}