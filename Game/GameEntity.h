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
	int pos_x;
	int pos_y;
	int speed_x;
	int speed_y;
	int direction_y;
	int direction_x;

	bool active = false;//is the entity actively being used?
	int hitboxRadius;//defines radius (for a square) for entity collision detection
	int ID;

	ALLEGRO_BITMAP *image;
	//possibly moved to sprite class?? will see
	int animationFrame;//this is the frame we are on
	int animationFrameWidth;//this is the width of the bitmap region
	int animationFrameHeight;//this is the height of bitmap region

public:
	GameEntity(int pos_x, int pos_y, int speed_x, int speed_y, int direction_y, int direction_x, bool active,
	int hitboxRadius, int ID, ALLEGRO_BITMAP *image);
	virtual ~GameEntity();

	virtual void draw() = 0;
	virtual void update() = 0;//updates entity
};
#endif
