#pragma once
#include "Enemy.h"
#include <memory>

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

	//Update functions
	virtual bool UpdatePosition() { return false; }
	virtual void UpdateDirection() {}

private:	
	
	enum State
	{
		RandomWalk,
		ChasePlayer,
	};
	
	void LoadSprites( ALLEGRO_BITMAP* image, ALLEGRO_BITMAP* deathImage );
	void setDirection( float angle );

	CTwoDVector m_targetPosition;
	CTwoDVector m_intermediateTargetPosition;

	CSprite* m_currentSprite;
	std::unique_ptr<CSprite> m_zombieSprite;
	std::unique_ptr<CSprite> m_zombieDeathSprite;

	State m_state = RandomWalk;
};
