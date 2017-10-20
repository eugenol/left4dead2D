#include "CSprite.h"

//-------------------------------------------------------

CSprite::CSprite( std::string imageName, SpriteSheetProperties& properties)
	:
	m_ownsImage( true ),
	m_image( nullptr ),
	m_properties( properties ),
  m_frameTime( 0.0 ),
	m_animationComplete( false ),
	m_frameDelay( properties.m_frameDelay )
{
	m_image = al_load_bitmap( imageName.c_str() );
}

//-------------------------------------------------------

CSprite::CSprite( ALLEGRO_BITMAP* imageToUse, SpriteSheetProperties& properties)
	:
	m_ownsImage( false ),
	m_image( imageToUse ),
	m_properties( properties ),
	m_frameTime( 0.0 ),
	m_animationComplete( false ),
	m_frameDelay( properties.m_frameDelay )
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
	int frameX = m_currentFrame*m_properties.m_animationFrameWidth;
	int frameY = direction*m_properties.m_animationFrameHeight;
	int frameWidth = m_properties.m_animationFrameWidth;
	int frameHeight = m_properties.m_animationFrameHeight;
	int posX = position.m_x - m_properties.m_animationFrameWidth / 2;
	int posY = position.m_y - m_properties.m_animationFrameHeight / 2;

	al_draw_bitmap_region( m_image, frameX, frameY, frameWidth, frameHeight, posX, posY, 0);
}

//-------------------------------------------------------

void CSprite::Draw( ALLEGRO_COLOR tintColor, CTwoDVector& position, int direction )
{
	int frameX = m_currentFrame*m_properties.m_animationFrameWidth;
	int frameY = direction*m_properties.m_animationFrameHeight;
	int frameWidth = m_properties.m_animationFrameWidth;
	int frameHeight = m_properties.m_animationFrameHeight;
	int posX = position.m_x - m_properties.m_animationFrameWidth / 2;
	int posY = position.m_y - m_properties.m_animationFrameHeight / 2;

	al_draw_tinted_bitmap_region( m_image, tintColor, frameX, frameY, frameWidth, frameHeight, posX, posY, 0);
}

void CSprite::DoLogic( double deltaTime )
{
	UpdateAnimation( deltaTime );
}

//-------------------------------------------------------

void CSprite::UpdateAnimation( double deltaTime )
{
	m_frameTime += deltaTime;

	if( m_frameTime >= m_frameDelay )
	{
		if (m_currentFrame < m_properties.m_maxFrameCount - 1)
		{
			m_currentFrame++;
		}
		else
		{
			m_currentFrame = m_properties.m_minFrameCount;
			m_animationComplete = true;
		}
		m_frameTime = 0;
	}
}

void CSprite::ResetAnimation()
{
	m_frameTime = 0.0;
	m_currentFrame = 0;
	m_animationComplete = false;
}
