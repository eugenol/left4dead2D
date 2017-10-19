#ifndef GAMEENTITY_H
#define GAMEENTITY_H

extern int gameTime;
extern int gameTimeUpdateCounter;

enum IDS{ PLAYER, TERRAIN, ENEMY, PICKUP, PROJECTILE };
enum DIRECTIONS{NORTH,NORTHEAST,EAST,SOUTHEAST,SOUTH,SOUTHWEST,WEST,NORTHWEST};

class GameEntity
{
public:
	GameEntity();
	GameEntity(int life, int pos_x, int pos_y, int speed_x, int speed_y, int direction, bool active,
		int hitboxRadius, int ID);
	virtual ~GameEntity();

	int getID();
	bool active = false;	//is the entity actively being used?
	virtual void Draw() {}
	virtual void Update() = 0;//general Update Entity, calls specific Update Functions
	bool getAlive() { return isAlive; } //return Alive state

																			// for colissions, can make these virtual, but that can be done later.
	bool CheckCollision(GameEntity *otherObject);
	virtual void Collided(GameEntity *otherObject);

	//Virtual Functions for Collisions (Perhaps we shall find another way...)
	virtual void takeDamage(int damageAmount);
	virtual int getDamagePower();

protected:
	int old_pos_x; //Used to check if the entity has had it's position updated
	int old_pos_y; //If not then there is no need to update direction or animation (this may differ for enemies?)
	int life;
	int pos_x;
	int pos_y;
	int speed_x;
	int speed_y;
	int direction;		  //Single Direction Variable from 0 to 3 Describes direction
	int maxXpos, maxYpos; //Hold window size to prevent the player from moving off the screen
	bool collided;
	
	int hitboxRadius;		//defines radius (for a square) for entity collision detection
	int hitboxWidth;
	int hitboxHeight;
	int ID;
	bool isAlive = true; //used for EntityManager

	//Update functions
	virtual bool UpdatePosition() = 0;
	virtual void UpdateDirection() = 0;
	
	//Collision functions
	void bounceBack(GameEntity * entity1, GameEntity * entity2);
	void EnemyHitsPlayer(GameEntity * Player, GameEntity * Enemy);
	void ProjectileHitsEnemy(GameEntity * Enemy, GameEntity * Projectile);
};
#endif
