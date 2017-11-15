#include "Potion.h"

//-------------------------------------------------------

Potion::Potion( ) :
m_randomPosX(0),
m_randomPosY(0),
m_noPotionTimer( 10.0 ),
m_showPotionTimer( 5.0 ),
m_collectedPotion(false)
{
	m_potionImage = al_load_bitmap("potion.png");
	al_convert_mask_to_alpha(m_potionImage, al_map_rgb(255, 255, 255));
	m_imageWidth = al_get_bitmap_width(m_potionImage);
	m_imageHeight = al_get_bitmap_height(m_potionImage);
	m_noPotionTimer.Start();

	m_potionSprite = std::make_unique<CSprite>(m_potionImage);
}

//-------------------------------------------------------

Potion::~Potion()
{
	al_destroy_bitmap( m_potionImage );
}

//-------------------------------------------------------

void Potion::Draw()
{
	if (m_showPotionTimer.IsRunning())
	{
		CTwoDVector position(m_randomPosX, m_randomPosY);
		m_potionSprite->Draw(position);
	}

}

//-------------------------------------------------------

void Potion::Update( double deltaTime )
{
	m_noPotionTimer.Update( deltaTime );
	m_showPotionTimer.Update( deltaTime );
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
		if (m_noPotionTimer.HasElapsed())
		{
			m_noPotionTimer.Stop();
			m_showPotionTimer.Start();

			m_randomPosX = rand() % 800 + 1;
			m_randomPosY = rand() % 600 + 1;
		}
		if (m_showPotionTimer.HasElapsed())
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