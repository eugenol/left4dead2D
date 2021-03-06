#ifndef MELEEZOMBIE_H
#define MELEEZOMBIE_H
#include "Enemy.h"

enum difficultyEnum{ EASY, HARD, BOSS, GODLIKE };

class MeleeZombie :public Enemy {
public:
	MeleeZombie( CTwoDVector position, int difficulty, ALLEGRO_BITMAP* image, ALLEGRO_BITMAP* zombieDeathAnimationSpriteSheet );
	~MeleeZombie();

	void Update( double deltaTime ) override;
	void Draw() override;

private:
	void UpdateDirection();
	void setDirection(float angle);//sets the animation direction towards zombie destination\
																 	
	CSprite* m_currentSprite;
	CSprite* m_zombieSprite;
	CSprite* m_zombieDeathSprite;

};
//128x128 tiles.  8 direction, 36 frames per direction.
#endif