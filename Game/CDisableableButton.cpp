#include "CDisableableButton.h"

//-------------------------------------------------------

CDisableableButton::CDisableableButton(CTwoDVector position, int width, int height, std::string text, ALLEGRO_FONT* font, ALLEGRO_COLOR color, std::function<void()> callBack, std::function<bool()> disableCheck, ALLEGRO_COLOR disableColor)
	:
	CButton(position, width, height, text, font, color, std::move(callBack)),
	m_disableCheck(std::move(disableCheck)),
	m_disableColor(disableColor)
{
}

//-------------------------------------------------------

CDisableableButton::~CDisableableButton()
{
}

//-------------------------------------------------------

void CDisableableButton::Draw()
{
	if (m_disableCheck())
	{
		CButton::Draw(m_disableColor);
	}
	else
	{
		CButton::Draw();
	}
}

//-------------------------------------------------------

void CDisableableButton::Draw(ALLEGRO_COLOR color)
{
	CButton::Draw(color);
}

//-------------------------------------------------------