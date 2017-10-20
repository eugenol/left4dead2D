#ifndef DEATHSCREEN_H
#define DEATHSCREEN_H
#include <allegro5/allegro_font.h>
#include "CScreen.h"
#include "CButton.h"
#include <memory>
#include "CSprite.h"

class DeathScreen : public CScreen
{
public:
	DeathScreen(ALLEGRO_FONT *font_18, ALLEGRO_FONT *font_24, ALLEGRO_FONT *font_72);
	~DeathScreen();

	void Update();
	void Draw();
	bool GetReturnToMenu() { return returnToMenu; }
	void SetReturnToMenu() { returnToMenu = false; }
private:
	ALLEGRO_FONT *font18 = nullptr;
	ALLEGRO_FONT *font24 = nullptr;
	ALLEGRO_FONT *font72 = nullptr;

	bool returnToMenu;
	std::unique_ptr<CSprite> m_image = nullptr;
	std::unique_ptr<CButton> m_button;
	CTwoDVector m_imagePosition;
};
#endif

