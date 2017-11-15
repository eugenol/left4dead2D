#include "CAIZombie.h"



CAIZombie::CAIZombie( CTwoDVector position, ALLEGRO_BITMAP* image, ALLEGRO_BITMAP* zombieDeathAnimationSpriteSheet )
	: Enemy( 0, position, 0, 0, 0, image, true, 0, 0, 0, 0 )
{
	LoadSprites( image, zombieDeathAnimationSpriteSheet );
	m_targetPosition = CTwoDVector( 700, 500 );
	m_baseSpeed = 3;

	std::vector<CTwoDVector> path;
	path.emplace_back(100, 100);
	path.emplace_back(700, 100);
	path.emplace_back(700, 500);
	path.emplace_back(100, 500);
	m_path = path;
}

CAIZombie::~CAIZombie()
{
	m_currentSprite = nullptr;
}

void CAIZombie::DoLogic( double deltaTime )
{
	FollowPath( 30, deltaTime );

	// random walks
	//CTwoDVector diff = m_targetPosition - m_position;

	//if( diff.Magnitude() > 2 )
	//{
	//	m_speed = m_baseSpeed*(diff.Magnitude()+1);
	//	WalkToTarget(m_targetPosition, m_speed, deltaTime);
	//}
	//else
	//{
	//	m_targetPosition = CTwoDVector( rand() % DISPLAY_WIDTH , rand() % DISPLAY_HEIGHT);
	//}
}

void CAIZombie::Update( double deltaTime )
{
	DoLogic( deltaTime );
	m_currentSprite->DoLogic( deltaTime );
	DoStateLogic( deltaTime );
}

void CAIZombie::Draw()
{
	m_currentSprite->Draw( m_position, direction );
	m_path.Draw();
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

void CAIZombie::WalkToTarget( CTwoDVector target, double speed, double deltaTime )
{
	m_direction = (target - m_position).EuclideanNorm();

	setDirection(180.0 / PI * atan2(m_direction.m_y, m_direction.m_x));

	m_velocity = speed*m_direction;
	m_position += m_velocity*deltaTime;
}

void CAIZombie::FollowPath( double speed, double deltaTime )
{
	static size_t index = 0;

	if (index < m_path.Size())
	{
		CTwoDVector target = m_path[index];
		WalkToTarget( target, speed, deltaTime );
		CTwoDVector diff = target - m_position;

		if (diff.Magnitude() < 2)
		{
			index++;
		}
	}
	else
	{
		index = 0;
	}
}

void CAIZombie::DoStateLogic(double delta_time)
{
	switch( m_state )
	{
	case RandomWalk:
			 break;
	case ChasePlayer:
			break;
	}
}
