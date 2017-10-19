#ifndef SCORESCREEN_H
#define SCORESCREEN_H
#include <allegro5/allegro_font.h>
#include "InputManager.h"
#include <tuple>
#include "CScreen.h"
#include "CButton.h"
#include <memory>

class ScoreScreen : public CScreen
{
public:
	ScoreScreen(ALLEGRO_FONT *font_18, ALLEGRO_FONT *font_24, ALLEGRO_FONT *font_72);
	~ScoreScreen();
	void Update() override;
	void Draw() override;
	void LoadData();
	bool GetReturnToMenu() { return returnToMenu; }
	void SetReturnToMenu() { returnToMenu = false; }

private:
	ALLEGRO_FONT *font18 = nullptr;
	ALLEGRO_FONT *font24 = nullptr;
	ALLEGRO_FONT *font72 = nullptr;
	bool returnToMenu;
	std::vector<std::pair<int, int> > highscores;
	std::unique_ptr<CButton> m_button;

};
#endif

