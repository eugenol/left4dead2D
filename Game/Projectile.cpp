#include "Projectile.h"
#include <math.h>


Projectile::Projectile(int destination_x, int destination_y, int lif, int maxX, int maxY, int xPos, int yPos, int speedX, int speedY, int Dir, bool activ, int hitboxR, int Identity, ALLEGRO_BITMAP *imag) : GameEntity(lif, maxX, maxY, xPos, yPos, speedX, speedY, Dir, activ, hitboxR, Identity, imag)
{
	old_pos_x = xPos;
	old_pos_y = yPos;
	destinationY = destination_y;
	destinationX = destination_x;
	angleOfPath = atan2f(destinationY - old_pos_y, destinationX - old_pos_x);

	active = 1;
   
}


Projectile::~Projectile()
{
}

bool Projectile::UpdatePosition()
{
	if (active)
	{
		pos_x += int(speed_x*cosf(angleOfPath));
		pos_y += int(speed_y*sinf(angleOfPath));
		return 1;
	}
	else return 0;
}

void Projectile::draw()
{
	al_draw_filled_circle(pos_x, pos_y, 20, al_map_rgb(255, 0, 255));
}

void Projectile::UpdateAnimation()
{

}
void Projectile::UpdateDirection()
{

}