#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <allegro5/allegro_font.h>
#include "GameScreen.h"
#include <functional>

class Button
{
public:
	Button( CTwoDVector position, int width, int height, std::string text, ALLEGRO_FONT* font, ALLEGRO_COLOR color, std::function<void()> callBack)
		:
		m_position( position ),
		m_witdh( width ),
		m_height( height ),
		m_text( text ),
		m_font( font ),
		m_color( color ),
		m_callBack( std::move(callBack) )
	{
		m_leftBorder = m_position.m_x - width / 2;
		m_rightBorder = m_position.m_x + width / 2;
		m_topBorder = m_position.m_y - height / 2;
		m_bottomBorder = m_position.m_y + height / 2;
	}

	Button(CTwoDVector position, int width, int height, std::string text, ALLEGRO_FONT* font, ALLEGRO_COLOR color, std::function<void()> callBack, std::function<bool()> disableCheck, ALLEGRO_COLOR disableColor)
		:
		m_position(position),
		m_witdh(width),
		m_height(height),
		m_text(text),
		m_font(font),
		m_color(color),
		m_callBack(std::move(callBack)),
		m_disableCheck( std::move(disableCheck) ),
		m_disableColor( disableColor )
	{
		m_leftBorder = m_position.m_x - width / 2;
		m_rightBorder = m_position.m_x + width / 2;
		m_topBorder = m_position.m_y - height / 2;
		m_bottomBorder = m_position.m_y + height / 2;
		m_useDisableCheck = true;
	}

	virtual ~Button() {}

	void Draw()
	{
		ALLEGRO_COLOR color = m_color;
		if (m_useDisableCheck)
		{
			if (m_disableCheck())
			{
				color = m_disableColor;
			}
		}
		Draw(color);
	}

	void Draw( ALLEGRO_COLOR color )
	{
		al_draw_text(m_font, color, m_position.m_x, m_position.m_y, ALLEGRO_ALIGN_CENTRE, m_text.c_str());
	}

	void OnClicked( CTwoDVector& mousePosition )
	{
		if( mousePosition.m_x >= m_leftBorder &&
				mousePosition.m_x <= m_rightBorder &&
				mousePosition.m_y <= m_bottomBorder &&
				mousePosition.m_y >= m_topBorder )
		{
			m_callBack();
		}
	}

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

	std::function<bool()> m_disableCheck;
	bool m_useDisableCheck = false;
	ALLEGRO_COLOR m_disableColor;
};

class MenuScreen : public CScreen
{
public:
	MenuScreen(ALLEGRO_FONT *font_18, ALLEGRO_FONT *font_24, ALLEGRO_FONT *font_72, GameScreen *current_game);
	~MenuScreen();
	enum MENUSTATE { STAYMENU, NEWGAME, HIGHSCORES, CREDITS, EXITGAME, RESUMEGAME };
	void Update();
	void Draw();
	int getCurrentMenuOption();
	void clearCurrentMenuOption() { currentOption = STAYMENU; }

private:
	void NewGame() { currentOption = NEWGAME; }
	void ResumeGame();
	void HighScores() { currentOption = HIGHSCORES; }
	void Credits() { currentOption = CREDITS; }
	void ExitGame() { currentOption = EXITGAME; }

	ALLEGRO_FONT *font18 = nullptr;
	ALLEGRO_FONT *font24 = nullptr;
	ALLEGRO_FONT *font72 = nullptr;

	GameScreen *game;
	CTwoDVector mouse;
	int currentOption;

	std::vector<Button> m_buttons;

};
#endif
