#include "CSprite.h"

//-------------------------------------------------------

CSprite::CSprite( std::string imageName, SpriteSheetProperties& properties)
	:
	m_ownsImage( true ),
	m_image( nullptr ),
	m_properties( properties )
{
	m_image = al_load_bitmap( imageName.c_str() );
}

//-------------------------------------------------------

CSprite::CSprite( ALLEGRO_BITMAP* imageToUse, SpriteSheetProperties& properties)
	:
	m_ownsImage( false ),
	m_image( imageToUse ),
	m_properties(properties)
{
}

//-------------------------------------------------------

CSprite::~CSprite()
{
	if( m_ownsImage &&  m_image)
	{
		al_destroy_bitmap(m_image);
	}
}

//-------------------------------------------------------

void CSprite::Draw( CTwoDVector& position, int direction )
{
	al_draw_bitmap_region( m_image, m_properties.m_currentAnimationFrame*m_properties.m_animationFrameWidth,
												 direction*m_properties.m_animationFrameHeight, m_properties.m_animationFrameWidth,
												 m_properties.m_animationFrameHeight, position.m_x - m_properties.m_animationFrameWidth / 2,
												 position.m_y - m_properties.m_animationFrameHeight / 2, 0 );
}

//-------------------------------------------------------

void CSprite::Draw( ALLEGRO_COLOR tintColor, CTwoDVector& position, int direction )
{
	al_draw_tinted_bitmap_region( m_image, tintColor, m_properties.m_currentAnimationFrame*m_properties.m_animationFrameWidth,
																direction*m_properties.m_animationFrameHeight, m_properties.m_animationFrameWidth,
																m_properties.m_animationFrameHeight, position.m_x - m_properties.m_animationFrameWidth / 2,
																position.m_y - m_properties.m_animationFrameHeight / 2, 0);
}

void CSprite::DoLogic()
{
	UpdateAnimation();
}

//-------------------------------------------------------

void CSprite::UpdateAnimation()
{
	//Generates /Advances Animation
	if( ++m_properties.m_frameCount >= m_properties.m_frameDelay )
	{
		if( ++m_properties.m_currentAnimationFrame >= m_properties.m_maxFrameCount )
		{
			m_properties.m_currentAnimationFrame = m_properties.m_minFrameCount;
		}
		m_properties.m_frameCount = 0;
	}
}