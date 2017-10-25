#include "PlayerLives.h"
#include "CSprite.h"

//-------------------------------------------------------

PlayerLives::PlayerLives() :
m_imageWidth(0),
m_imageHeight(0),
m_frameWidth(0),
m_numberOfLives(3)
{
	m_skull = al_load_bitmap( "skull.png" );
	al_convert_mask_to_alpha(m_skull, al_map_rgb(255, 255, 255));
	m_imageWidth = al_get_bitmap_width(m_skull);
	m_imageHeight = al_get_bitmap_height(m_skull);

	SpriteSheetProperties properties;
	properties.m_animationFrameWidth = m_imageWidth;
	properties.m_animationFrameHeight = m_imageHeight;
	properties.m_maxFrameCount = 0;
	properties.m_minFrameCount = 0;
	properties.m_frameDelay = -1;

	m_heart0 = std::make_unique<CSprite>(m_skull, properties);
	m_heart1 = std::make_unique<CSprite>(m_skull, properties);
	m_heart2 = std::make_unique<CSprite>(m_skull, properties);
}

//-------------------------------------------------------

PlayerLives::~PlayerLives()
{
	al_destroy_bitmap( m_skull );
}

//-------------------------------------------------------

void PlayerLives::Draw()
{
	if (m_numberOfLives > 2)
	{
		CTwoDVector heart0Pos(750 + m_imageHeight / 2, 550 + m_imageHeight / 2);
		m_heart0->Draw(heart0Pos);
	}
	if (m_numberOfLives > 1)
	{
		CTwoDVector heart1Pos(700 + m_imageHeight / 2, 550 + m_imageHeight / 2);
		m_heart1->Draw(heart1Pos);
	}
	if (m_numberOfLives > 0)
	{  
		CTwoDVector heart2Pos(650 + m_imageHeight / 2, 550 + m_imageHeight / 2);
		m_heart2->Draw(heart2Pos);
	}
}

//-------------------------------------------------------

void PlayerLives::Update( double deltaTime )
{
}

//-------------------------------------------------------