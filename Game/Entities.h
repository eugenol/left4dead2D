#ifndef ENTITIES_H
#define ENTITIES_H
#include <allegro5/allegro.h>
//this header will contain game entity class definitions
using namespace std;

enum IDS{PLAYER,TERRAIN,ENEMY,PICKUP,PROJECTILE};

class Entity{//Virtual class all entities inherit from
private:
protected:
	int pos_x;
	int pos_y;
	int speed_x;
	int speed_y;

	bool active = false;//is the entity actively being used?
	int hitboxRadius;//defines radius (for a square) for entity collision detection
	int ID;

	int animationFrame;//this is the frame we are on
	int animationFrameWidth;//this is the width of the bitmap region
	int animationFrameHeight;//this is the height of bitmap region
	ALLEGRO_BITMAP *image;
public:
	Entity();
	virtual ~Entity() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;//updates entity
};
#endif