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
	int pos_x;
	int pos_y;
	int speed_x;
	int speed_y;
	int direction_y;
	int direction_x;
	int direction;

	bool active = false;//is the entity actively being used?
	int hitboxRadius;//defines radius (for a square) for entity collision detection
	int ID;

	//Animation Variables
	//possibly moved to sprite class?? will see
	ALLEGRO_BITMAP *image;
	int animationFrame;//this is the frame we are on
	int animationFrameWidth;//this is the width of the bitmap region
	int animationFrameHeight;//this is the height of bitmap region
	int frameCount; //holds Frame Number to control animation sequence
	int maxFrame; //Total Number of frames in animation sequence
	int frameDelay; //Delay associated with animation

	//Subroutines
	void UpdateAnimation();
	void UpdatePosition(int &verticleMove, int &horizontalMove); //Updates Position of Entity

public:
	GameEntity(int pos_x, int pos_y, int speed_x, int speed_y, int direction_x, int direction_y, bool active,
	int hitboxRadius, int ID, ALLEGRO_BITMAP *image);
	GameEntity();
	virtual ~GameEntity() = 0;

	void draw(); //Draws entity
	
	//updates entity, shall call UpdateAnimation and UpdatePosition
	void update(int horizontalMove, int verticleMove, int damage, int direction);
	
	
};
#endif
