#include "HealthBar.h"

//-------------------------------------------------------

HealthBar::HealthBar(ALLEGRO_BITMAP *healthBarSpriteSheet) :
m_healthBar(healthBarSpriteSheet),
m_imageWidth(0),
m_imageHeight(0),
m_frameWidth(0),
m_currentAnimationFrame(1)
{
	//al_convert_mask_to_alpha(m_healthBar, al_map_rgb(255, 255, 255));

	m_imageWidth = al_get_bitmap_width(m_healthBar);
	m_imageHeight = al_get_bitmap_height(m_healthBar);
	m_frameWidth = m_imageWidth / 5;
}

//-------------------------------------------------------

HealthBar::~HealthBar()
{
}

//-------------------------------------------------------

void HealthBar::Draw()
{
	al_draw_bitmap_region(m_healthBar,
					      m_currentAnimationFrame * m_frameWidth,
						  0,
						  m_frameWidth,
					      m_imageHeight,
						  430,
						  560,
						  0);
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
}

//-------------------------------------------------------