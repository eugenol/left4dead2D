#pragma once
#include "CButton.h"

//-------------------------------------------------------

class CDisableableButton : public CButton
{
public:
	CDisableableButton(CTwoDVector position, int width, int height, std::string text, ALLEGRO_FONT* font, ALLEGRO_COLOR color, std::function< void() > callBack, std::function< bool() > disableCheck, ALLEGRO_COLOR disableColor);
	virtual ~CDisableableButton();

	void Draw() override;
	void Draw(ALLEGRO_COLOR color) override;

private:
	std::function<bool()> m_disableCheck;
	ALLEGRO_COLOR m_disableColor;
};

//-------------------------------------------------------