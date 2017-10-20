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

void CAIZombie::DoLogic( double deltaTime )
{
	// random walks
	CTwoDVector diff = m_targetPosition - m_position;

	setDirection(180.0 / PI * atan2(diff.m_y, diff.m_x));

	if( diff.Magnitude() > 2 )
	{
		//random jagged step
		CTwoDVector step0(0, 0);
		CTwoDVector step1(1, 1);
		CTwoDVector step2(-1, -1);
		CTwoDVector step3(1, -1);
		CTwoDVector step4(-1, 1);
		CTwoDVector step5(0, 1);
		CTwoDVector step6(0, -1);
		CTwoDVector step7(1, 0);
		CTwoDVector step8(-1, 0);

		CTwoDVector stepVector;

		int randSelect = rand() % 9;
		switch (randSelect)
		{
		case 0: stepVector = step0;
			break;
		case 1: stepVector = step1;
			break;
		case 2: stepVector = step2;
			break;
		case 3: stepVector = step3;
			break;
		case 4: stepVector = step4;
			break;
		case 5: stepVector = step5;
			break;
		case 6: stepVector = step6;
			break;
		case 7: stepVector = step7;
			break;
		case 8: stepVector = step8;
			break;
		}

		//CTwoDVector step = (12.5*diff.EuclideanNorm() + 2*stepVector)*deltaTime;
		CTwoDVector step = 80*diff.EuclideanNorm()*deltaTime;
		m_position += step;
	}
	else
	{
		m_targetPosition = CTwoDVector( rand() % DISPLAY_WIDTH , rand() % DISPLAY_HEIGHT);
	}
}

void CAIZombie::Update( double deltaTime )
{
	DoLogic( deltaTime );
	m_currentSprite->DoLogic( deltaTime );
}

void CAIZombie::Draw()
{
	m_currentSprite->Draw( m_position, direction );
}

void CAIZombie::LoadSprites(ALLEGRO_BITMAP* image, ALLEGRO_BITMAP* deathImage)
{
	SpriteSheetProperties properties;
	//properties for zombie sprite sheet
	properties.m_maxFrameCount = 8;
	properties.m_minFrameCount = 0;
	properties.m_animationFrameHeight = 128;
	properties.m_animationFrameWidth = 128;
	//to provide a slower, more visible animation
	properties.m_frameDelay = 8.0 / FPS;

	m_zombieSprite = std::make_unique<CSprite>(image, properties);
	m_currentSprite = m_zombieSprite.get();

	//Death animation spritesheet
	properties.m_maxFrameCount = 7;
	properties.m_frameDelay = 5.0 / FPS;
	properties.m_minFrameCount = 0;

	m_zombieDeathSprite = std::make_unique<CSprite>(deathImage, properties);


	hitboxWidth = 36;
	hitboxHeight = 60;
	//Death Animation Variables
	//Death Animation Variables
	runDeathAnimation = false;
}

void CAIZombie::setDirection(float angle)
{
	enum Compass { W, NW, N, NE, E, SE, S, SW };//ordered such that sprite sheet rows correlate correctly to cardinal directions
																							//function itself
	if (angle < -135 - 22.5) direction = W;
	else if (angle < -90 - 22.5) direction = NW;
	else if (angle < -45 - 22.5) direction = N;
	else if (angle < 0 - 22.5) direction = NE;
	else if (angle < 45 - 22.5) direction = E;
	else if (angle < 90 - 22.5) direction = SE;
	else if (angle < 135 - 22.5) direction = S;
	else if (angle < 180 - 22.5) direction = SW;
	else direction = W;
}