#ifndef GAMEENTITY_H
#define GAMEENTITY_H
//allegro includes
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

enum IDS{ PLAYER, TERRAIN, ENEMY, PICKUP, PROJECTILE };

class GameEntity
{
protected:
	
	int life;
	int score;
	int pos_x;
	int pos_y;
	int speed_x;
	int speed_y;
	int direction; //Single Direction Variable from 0 to 3 Describes direction
	int maxXpos, maxYpos; //Hold window size to prevent the player from moving off the screen

	bool active = false;//is the entity actively being used?
	int hitboxRadius;//defines radius (for a square) for entity collision detection
	int ID;

	//Sprite and animation variables (possibly moved to sprite class?? will see)
	ALLEGRO_BITMAP *image;
	int animationFrameWidth;//this is the width of the bitmap region
	int animationFrameHeight;//this is the height of bitmap region
	int currentAnimationFrame;//this is the frame we are on
	int frameCount; //frame Count
	int maxFrameCount; //max no of frames in animation sequence
	int frameDelay; //delay associated to animation

	//Update functions
	void UpdateAnimation();
	virtual bool UpdatePosition() = 0;
	virtual void UpdateDirection() = 0;
public:
	GameEntity();
	GameEntity(int life, int maxXpos, int maxYpos, int pos_x, int pos_y, int speed_x, int speed_y, int direction, bool active,
		int hitboxRadius, int ID, ALLEGRO_BITMAP *image);
	virtual ~GameEntity();

	void draw();
	void update();//general Update Entity, calls specific Update Functions
};
#endif
