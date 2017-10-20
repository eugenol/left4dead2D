#ifndef CREDITSCREEN_H
#define CREDITSCREEN_H

#include <allegro5/allegro_font.h>
#include "CScreen.h"
#include <memory>
#include "CButton.h"

class CreditScreen : public CScreen
{
public:
	CreditScreen(ALLEGRO_FONT *font_18, ALLEGRO_FONT *font_24, ALLEGRO_FONT *font_72);
	~CreditScreen();

	void Update();
	void Draw();
	bool GetReturnToMenu() { return returnToMenu; }
	void SetReturnToMenu() { returnToMenu = false; }

private:
	ALLEGRO_FONT *font18 = nullptr;
	ALLEGRO_FONT *font24 = nullptr;
	ALLEGRO_FONT *font72 = nullptr;
	bool returnToMenu;
	std::unique_ptr<CButton> m_button;

};
#endif

