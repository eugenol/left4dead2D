#ifndef GAMEENTITY_H
#define GAMEENTITY_H
#include "CTwoDVector.h"
#include "Common.h"

extern int gameTime;
extern int gameTimeUpdateCounter;

enum IDS{ PLAYER, TERRAIN, ENEMY, PICKUP, PROJECTILE };
enum DIRECTIONS{NORTH,NORTHEAST,EAST,SOUTHEAST,SOUTH,SOUTHWEST,WEST,NORTHWEST};

class GameEntity
{
public:
	GameEntity();
	GameEntity(int life, CTwoDVector position, int speed_x, int speed_y, int direction, bool active, int ID);
	virtual ~GameEntity();
	
	int getID();
	bool active = false;	//is the entity actively being used?
	virtual void Draw() {}
	virtual void Update( double deltaTime ) = 0;//general Update Entity, calls specific Update Functions
	bool getAlive() { return isAlive; } //return Alive state

	// for colissions, can make these virtual, but that can be done later.
	bool SameRegion(GameEntity* otherObject);
	bool CheckCollision(GameEntity *otherObject);
	virtual void Collided(GameEntity *otherObject);

	//Virtual Functions for Collisions (Perhaps we shall find another way...)
	virtual void takeDamage(int damageAmount);
	virtual int getDamagePower();

protected:
	int life;
	int speed_x;
	int speed_y;
	int direction;		  //Single Direction Variable from 0 to 3 Describes direction

	bool collided;
	
	int hitboxWidth;
	int hitboxHeight;
	int ID;
	bool isAlive = true; //used for EntityManager

	CTwoDVector m_position;
	CTwoDVector m_oldPosition;

	//Update functions
	//virtual bool UpdatePosition() = 0;
	//virtual void UpdateDirection() = 0;
	
	//Collision functions
	//void bounceBack(GameEntity * entity1, GameEntity * entity2);
	//void EnemyHitsPlayer(GameEntity * Player, GameEntity * Enemy);
	//void ProjectileHitsEnemy(GameEntity * Enemy, GameEntity * Projectile);

	//Hold window size to prevent the player from moving off the screen
	int maxXpos = DISPLAY_WIDTH;
	int maxYpos = DISPLAY_HEIGHT;
};
#endif
