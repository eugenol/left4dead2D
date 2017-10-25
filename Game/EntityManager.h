/*
* This singleton class is used to manage all entities it should make it easier to handle the
* dynamic creation and destruction of bullets and enemies.
* Pointer to all entities are stored in a doubly linked list created in main(); It is created as follow:
*
*			std::list<GameEntity*> objects;
*
* After it is created, to following call is performed to instanciate the Manager, and pass a reference to the list:
*
*			EntityManager::getInstance().getEntityList(&objects);
*
* The entity manager will now keep track of objects in the list. To add an object use the following procedure
*
*  Example: GameEntity *player = new Player (...........); //dynamically allocate memory for object
*			EntityManager::getInstance().AddEntity(player); //adds player to the manager
*
* Note: An object will automatically be removed from the list during the update routine if its isAlive member variable is false, so when creating
* an object that you want managed, make sure isAlive = true when it is created, or it will be deleted the next cycle.
*
* NB: DO NOT DEALLOCATE MEMORY OF AN OBJECT THAT YOU ADDED TO THE MANAGER, THIS WILL LEAVE THE POINTER IN THE LIST OB OBJECTS AND IT WILL CAUSE ERRORS.
*
*
* - E
*/
#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <list>
#include "GameEntity.h"
#include "Enemy.h"

class EntityManager
{

public:
	static EntityManager & getInstance();
	~EntityManager();

	std::list<GameEntity*>& getEntityList();
	void UpdateList();
	void AddEntity(GameEntity *entity);
	void KillAll();

	void Update( double deltaTime );
	void Draw();
	void DoCollisions();

	void RegisterPlayer( Player* player );
	void UnregisterPlayer();
	Player* GetPlayer();

	template<typename T, typename... TArgs>
	GameEntity* MakeEntity(TArgs&&... mArgs);
	//Can't use these methods to accidentally copy the input manager.
	EntityManager(EntityManager const&) = delete;
	void operator=(EntityManager const&) = delete;

private:
	EntityManager(); //Make constructor Private, so that only one instance can be made
	std::list<GameEntity*> entityList;
	Player* m_player;
};

template < typename T, typename ... TArgs >
GameEntity* EntityManager::MakeEntity( TArgs&&... mArgs )
{
	static_assert(std::is_base_of<GameEntity, T>::value,
		"`T` must be derived from `Entity`");

	GameEntity* ptr = new T(std::forward<TArgs>(mArgs)...);
	
	entityList.push_back( ptr );

	if ( std::is_same< Player, T >::value )
	{
		RegisterPlayer(dynamic_cast<Player*>(ptr));
	}

	return ptr;
}

#endif

