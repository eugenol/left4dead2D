#include "CAIZombie.h"



CAIZombie::CAIZombie( CTwoDVector position, ALLEGRO_BITMAP* image, ALLEGRO_BITMAP* zombieDeathAnimationSpriteSheet )
	: Enemy( 0, position, 0, 0, 0, image, true, 0, 0, 0, 0 )
{
	LoadSprites( image, zombieDeathAnimationSpriteSheet );
	m_targetPosition = CTwoDVector( 700, 500 );
}

CAIZombie::~CAIZombie()
{
	m_currentSprite = nullptr;
}

void CAIZombie::DoLogic()
{
	if( m_targetPosition != m_position )
	{
		CTwoDVector diff = 1.5*(m_targetPosition - m_position).EuclideanNorm();
		m_position += diff;
	}
}

void CAIZombie::Update()
{
	DoLogic();
	m_currentSprite->DoLogic();
}

void CAIZombie::Draw()
{
	m_currentSprite->Draw( m_position, 0 );
}

void CAIZombie::LoadSprites(ALLEGRO_BITMAP* image, ALLEGRO_BITMAP* deathImage)
{
	SpriteSheetProperties properties;
	//properties for zombie sprite sheet
	properties.m_maxFrameCount = 8;
	properties.m_minFrameCount = 0;
	properties.m_currentAnimationFrame = 0;
	properties.m_animationFrameHeight = 128;
	properties.m_animationFrameWidth = 128;
	properties.m_frameCount = 0;
	//to provide a slower, more visible animation
	properties.m_frameDelay = 5;

	m_zombieSprite = std::make_unique<CSprite>(image, properties);
	m_currentSprite = m_zombieSprite.get();

	//Death animation spritesheet
	properties.m_currentAnimationFrame = 0;
	properties.m_maxFrameCount = 7;
	properties.m_frameDelay = 5;
	properties.m_minFrameCount = 0;
	properties.m_frameCount = 0;

	m_zombieDeathSprite = std::make_unique<CSprite>(deathImage, properties);


	hitboxWidth = 36;
	hitboxHeight = 60;
	//Death Animation Variables
	//Death Animation Variables
	runDeathAnimation = false;
}
