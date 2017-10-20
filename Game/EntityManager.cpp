#include "EntityManager.h"


EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}


EntityManager & EntityManager::getInstance()
{
	static EntityManager instance;
	return instance;
}

void EntityManager::getEntityList(std::list<GameEntity*> *entityList)
{
	EntityManager::entityList = entityList;
}

void EntityManager::UpdateList()
{
	// Call this each update loop, if the object is dead, delete it

	std::list<GameEntity*>::iterator iter = entityList->begin();
	while (iter != entityList->end())
	{
		if (!(*iter)->getAlive())
		{
			std::list<GameEntity*>::iterator prev = iter++;
			GameEntity *tempPtr;
			tempPtr = *prev;
			if (tempPtr->getID() == PLAYER)
			{
				Enemy::setPlayer( nullptr );
			}
			entityList->erase(prev);
			delete tempPtr;
		}
		else
			iter++;
	}
}

void EntityManager::AddEntity(GameEntity *entity)
{
	// add entity to the list
	entityList->push_front(entity);
}

void EntityManager::KillAll()
{
	std::list<GameEntity*>::iterator iter = entityList->begin();
	while (iter != entityList->end())
	{
		std::list<GameEntity*>::iterator prev = iter++;
		GameEntity *tempPtr;
		tempPtr = *prev;
		if (tempPtr->getID() == PLAYER)
		{
			Enemy::setPlayer( nullptr );
		}
		entityList->erase(prev);
		delete tempPtr;
	}
}