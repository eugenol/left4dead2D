#ifndef MELEEZOMBIE_H
#define MELEEZOMBIE_H
#include "Enemy.h"
#include "allegro5\allegro.h"
#include "allegro5\allegro_image.h"

class MeleeZombie :public Enemy {
private:
	ALLEGRO_BITMAP * image;
	void UpdateDirection();
	void setDirection(int & direction, float angle);//sets the animation direction towards zombie destination
public:
	void update();
	//quick constructor (presets most values)
	MeleeZombie(int pos_x, int pos_y, ALLEGRO_BITMAP * image);
	~MeleeZombie();
};
//128x128 tiles.  8 direction, 36 frames per direction.
#endif