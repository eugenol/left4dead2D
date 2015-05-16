#include "PlayerLives.h"
#include "InitData.h"

//-------------------------------------------------------

PlayerLives::PlayerLives(ALLEGRO_BITMAP *skull) :
m_skull(skull),
m_imageWidth(0),
m_imageHeight(0),
m_frameWidth(0),
numberOfLives(3)
{
	al_convert_mask_to_alpha(m_skull, al_map_rgb(255, 255, 255));

	/*float width = al_get_bitmap_width(skull);
	float height = al_get_bitmap_height(skull);*/

	m_imageWidth = al_get_bitmap_width(m_skull);
	m_imageHeight = al_get_bitmap_height(m_skull);

	/*m_skull = al_create_bitmap(200, 200);
	stretch_blit(skull, m_skull, 0, 0, width, height, 0, 0, m_imageWidth, m_imageHeight);*/

	m_frameWidth = m_imageWidth / 5;
}

//-------------------------------------------------------

PlayerLives::~PlayerLives()
{
}

//-------------------------------------------------------

void PlayerLives::draw()
{
	if (numberOfLives > 2)
	{
		al_draw_bitmap(m_skull,
					   750,
					   550,
					   0);
	}
	if (numberOfLives > 1)
	{
		al_draw_bitmap(m_skull,
					   700,
					   550,
					   0);
	}
	if (numberOfLives > 0)
	{
		al_draw_bitmap(m_skull,
			           650,
			           550,
			           0);          
	}
}

//-------------------------------------------------------

void PlayerLives::update()
{
}

//-------------------------------------------------------