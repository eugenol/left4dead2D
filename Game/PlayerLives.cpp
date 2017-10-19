#include "PlayerLives.h"

//-------------------------------------------------------

PlayerLives::PlayerLives(ALLEGRO_BITMAP *skull, ALLEGRO_BITMAP *gameoverImage) :
m_skull(skull),
m_imageWidth(0),
m_imageHeight(0),
m_frameWidth(0),
m_gameoverImage(gameoverImage),
m_gameoverImageWidth(0),
m_gameoverImageHeight(0),
m_gameoverImageFrameWidth(0),
m_numberOfLives(3)
{
	al_convert_mask_to_alpha(m_skull, al_map_rgb(255, 255, 255));

	m_imageWidth = al_get_bitmap_width(m_skull);
	m_imageHeight = al_get_bitmap_height(m_skull);

	m_frameWidth = m_imageWidth / 5;

	m_gameoverImageWidth = al_get_bitmap_width(gameoverImage);
	m_gameoverImageHeight = al_get_bitmap_height(gameoverImage);

	m_gameoverImageFrameWidth = m_gameoverImageWidth / 5;
}

//-------------------------------------------------------

PlayerLives::~PlayerLives()
{
}

//-------------------------------------------------------

void PlayerLives::Draw()
{
	if (m_numberOfLives > 2)
	{
		al_draw_bitmap(m_skull,
					   750,
					   550,
					   0);
	}
	if (m_numberOfLives > 1)
	{
		al_draw_bitmap(m_skull,
					   700,
					   550,
					   0);
	}
	if (m_numberOfLives > 0)
	{
		al_draw_bitmap(m_skull,
			           650,
					   550,
			           0);          
	}

	//if (m_numberOfLives == 0)
	//{
	//	al_draw_bitmap(m_gameoverImage,
	//				  (300 - (m_gameoverImageWidth / 2)),
	//				  (400 - (m_gameoverImageHeight / 2)),
	//				   0);
	//}
}

//-------------------------------------------------------

void PlayerLives::Update()
{
}

//-------------------------------------------------------