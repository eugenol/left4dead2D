#include "HealthBar.h"

//-------------------------------------------------------

HealthBar::HealthBar(ALLEGRO_BITMAP *healthBarSpriteSheet) :
//m_healthBar(healthBarSpriteSheet),
m_imageWidth(0),
m_imageHeight(0),
m_frameWidth(0),
m_currentAnimationFrame(0),
m_position(CTwoDVector(532, 575))
{
	//al_convert_mask_to_alpha(m_healthBar, al_map_rgb(255, 255, 255));

	m_imageWidth = al_get_bitmap_width(healthBarSpriteSheet);
	m_imageHeight = al_get_bitmap_height(healthBarSpriteSheet);
	m_frameWidth = m_imageWidth / 5;

	SpriteSheetProperties properties;
	properties.m_animationFrameWidth = m_frameWidth;
	properties.m_animationFrameHeight = m_imageHeight;
	properties.m_maxFrameCount = 5;
	properties.m_minFrameCount = 0;
	properties.m_frameDelay = -1;

	m_healthBar = std::make_unique<CSprite>( healthBarSpriteSheet, properties );
}

//-------------------------------------------------------

HealthBar::~HealthBar()
{
}

//-------------------------------------------------------

void HealthBar::Draw()
{
	m_healthBar->Draw( m_position );
}

//-------------------------------------------------------

void HealthBar::Update( double deltaTime )
{
}

//-------------------------------------------------------

void HealthBar::DoLogic(double lifePercentage)
{
	if (lifePercentage > 80)
	{
		m_currentAnimationFrame = 0;
	}
	else if (lifePercentage > 60)
	{
		m_currentAnimationFrame = 1;
	}
	else if (lifePercentage > 40)
	{
		m_currentAnimationFrame = 2;
	}
	else if (lifePercentage > 20)
	{
		m_currentAnimationFrame = 3;
	}
	else
	{
		m_currentAnimationFrame = 4;
	}

	m_healthBar->SetCurrentAnimationFrame(m_currentAnimationFrame);
}

//-------------------------------------------------------