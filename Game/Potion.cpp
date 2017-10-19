#include "Potion.h"

//-------------------------------------------------------

Potion::Potion(ALLEGRO_BITMAP *potionImage) :
m_potionImage(potionImage),
m_randomPosX(0),
m_randomPosY(0),
m_noPotionTimer(),
m_showPotionTimer(),
m_collectedPotion(false)
{
	al_convert_mask_to_alpha(m_potionImage, al_map_rgb(255, 255, 255));
	m_imageWidth = al_get_bitmap_width(m_potionImage);
	m_imageHeight = al_get_bitmap_height(m_potionImage);
	m_noPotionTimer.Start();
}

//-------------------------------------------------------

Potion::~Potion()
{
}

//-------------------------------------------------------

void Potion::draw()
{
	if (m_showPotionTimer.IsRunning())
	{
		al_draw_bitmap(m_potionImage,
					   m_randomPosX,
					   m_randomPosY,
					   0);
	}
}

//-------------------------------------------------------

void Potion::update()
{
}

//-------------------------------------------------------

void Potion::DoLogic(int playerXPos, int playerYPos, bool isAlive)
{
	m_collectedPotion = false;

	if (!isAlive)
	{
		m_noPotionTimer.Stop();
		m_showPotionTimer.Stop();
	}
	else
	{
		if (m_noPotionTimer.HasElapsed(10.0))
		{
			m_noPotionTimer.Stop();
			m_showPotionTimer.Start();

			m_randomPosX = rand() % 800 + 1;
			m_randomPosY = rand() % 600 + 1;
		}
		if (m_showPotionTimer.HasElapsed(5.0))
		{
			m_showPotionTimer.Stop();
			m_noPotionTimer.Start();
		}
	}

	// Has player collected potion?
	if (m_showPotionTimer.IsRunning())
	{
		if (playerXPos >= m_randomPosX &&
			playerXPos <= (m_randomPosX + m_imageWidth) &&
			playerYPos >= m_randomPosY &&
			playerYPos <= (m_randomPosY + m_imageHeight))
		{
			m_collectedPotion = true;
			m_showPotionTimer.Stop();
			m_noPotionTimer.Start();
		}
	}
}

//-------------------------------------------------------