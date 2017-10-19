#pragma once
#include "CTwoDVector.h"
#include <functional>
#include <allegro5/allegro_font.h>

//-------------------------------------------------------

class CButton
{
public:
	CButton( CTwoDVector position, int width, int height, std::string text, ALLEGRO_FONT* font, ALLEGRO_COLOR color, std::function< void() > callBack );
	//CButton( CTwoDVector position, int width, int height, std::string text, ALLEGRO_FONT* font, ALLEGRO_COLOR color, std::function< void() > callBack, std::function< bool() > disableCheck, ALLEGRO_COLOR disableColor );

	virtual ~CButton();

	virtual void Draw();
	virtual void Draw( ALLEGRO_COLOR color );
	virtual void OnClicked( CTwoDVector& mousePosition );

private:
	CTwoDVector m_position;
	int m_witdh;
	int m_height;
	std::string m_text;
	ALLEGRO_FONT* m_font;
	ALLEGRO_COLOR m_color;
	int m_leftBorder;
	int m_rightBorder;
	int m_topBorder;
	int m_bottomBorder;
	std::function<void()> m_callBack;
};

//-------------------------------------------------------
