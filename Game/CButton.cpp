#include "CButton.h"

//-------------------------------------------------------

CButton::CButton( CTwoDVector position, int width, int height, std::string text, ALLEGRO_FONT* font, ALLEGRO_COLOR color, std::function< void() > callBack ):
	m_position( position ),
	m_witdh( width ),
	m_height( height ),
	m_text( text ),
	m_font( font ),
	m_color( color ),
	m_callBack( std::move( callBack ) )
{
	m_leftBorder = m_position.m_x - width / 2;
	m_rightBorder = m_position.m_x + width / 2;
	m_topBorder = m_position.m_y - height / 2;
	m_bottomBorder = m_position.m_y + height / 2;
}

//-------------------------------------------------------

CButton::~CButton()
{
}

//-------------------------------------------------------

void CButton::Draw()
{
	al_draw_text(m_font, m_color, m_position.m_x, m_position.m_y, ALLEGRO_ALIGN_CENTRE, m_text.c_str());
}

//-------------------------------------------------------

void CButton::Draw( ALLEGRO_COLOR color )
{
	al_draw_text( m_font, color, m_position.m_x, m_position.m_y, ALLEGRO_ALIGN_CENTRE, m_text.c_str() );
}

//-------------------------------------------------------

void CButton::OnClicked( CTwoDVector& mousePosition )
{
	if ( mousePosition.m_x >= m_leftBorder &&
		mousePosition.m_x <= m_rightBorder &&
		mousePosition.m_y <= m_bottomBorder &&
		mousePosition.m_y >= m_topBorder )
	{
		m_callBack();
	}
}

//-------------------------------------------------------