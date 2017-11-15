#pragma once
#include "Enemy.h"
#include <memory>
#include "CPath.h"

class CAIZombie :
	public Enemy
{
public:
	CAIZombie(CTwoDVector position, ALLEGRO_BITMAP* image, ALLEGRO_BITMAP* zombieDeathAnimationSpriteSheet);
	~CAIZombie();

	void DoLogic(double deltaTime);
	void DoStateLogic( double delta_time );
	void Update( double deltaTime ) override;
	void Draw() override;

private:	
	
	enum State
	{
		RandomWalk,
		ChasePlayer,
	};
	
	void LoadSprites( ALLEGRO_BITMAP* image, ALLEGRO_BITMAP* deathImage );
	void setDirection( float angle );
	void WalkToTarget( CTwoDVector target, double speed, double deltaTime );
	void FollowPath(double speed, double deltaTime);

	CTwoDVector m_targetPosition;
	CTwoDVector m_intermediateTargetPosition;
	CTwoDVector m_direction;

	CSprite* m_currentSprite;
	std::unique_ptr<CSprite> m_zombieSprite;
	std::unique_ptr<CSprite> m_zombieDeathSprite;

	double m_speed;
	double m_baseSpeed;
	CTwoDVector m_velocity;
	State m_state = RandomWalk;

	CPath m_path;
};
