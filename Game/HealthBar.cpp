#include "HealthBar.h"

//-------------------------------------------------------

HealthBar::HealthBar() :
m_currentAnimationFrame(0),
m_position(CTwoDVector(532, 575))
{
	SpriteSheetProperties properties;
	properties.m_animationFrameWidth = 204;
	properties.m_animationFrameHeight = 30;
	properties.m_maxFrameCount = 5;
	properties.m_minFrameCount = 0;
	properties.m_frameDelay = -1;

	m_healthBar = std::make_unique<CSprite>( "healthbar.png", properties );
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