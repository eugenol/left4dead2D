#ifndef MELEEZOMBIE_H
#define MELEEZOMBIE_H
#include "Enemy.h"
#include "allegro5\allegro.h"
#include "allegro5\allegro_image.h"

class MeleeZombie :public Enemy {
private:
	ALLEGRO_BITMAP * image;
	int defaultHitpoints = 87;
	int defaultRegen = 0;
	int defaultSpeed = 4;//speed is broken into x and y parts
	void UpdateDirection();
	void setDirection(int & direction, int pos_x, int pos_y, int dest_x, int dest_y);//sets the animation direction correctly
public:
	void update();
	//quick constructor (presets most values)
	MeleeZombie(int pos_x, int pos_y);
	~MeleeZombie();
};
//128x128 tiles.  8 direction, 36 frames per direction.
#endif