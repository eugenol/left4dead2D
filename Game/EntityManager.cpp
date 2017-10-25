#include "EntityManager.h"


EntityManager::EntityManager()
	:
	m_player( nullptr )
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

std::list<GameEntity*>& EntityManager::getEntityList()
{
	return entityList;
}

void EntityManager::UpdateList()
{
	// Call this each update loop, if the object is dead, delete it

	std::list<GameEntity*>::iterator iter = entityList.begin();
	while (iter != entityList.end())
	{
		if (!(*iter)->getAlive())
		{
			std::list<GameEntity*>::iterator prev = iter++;
			GameEntity *tempPtr = *prev;
			if (tempPtr->getID() == PLAYER)
			{
				m_player = nullptr;
			}
			entityList.erase(prev);
			delete tempPtr;
		}
		else
		{
			++iter;
		}
	}
}

void EntityManager::AddEntity(GameEntity *entity)
{
	// add entity to the list
	entityList.push_front(entity);
}

void EntityManager::KillAll()
{
	std::list<GameEntity*>::iterator iter = entityList.begin();
	while (iter != entityList.end())
	{
		std::list<GameEntity*>::iterator prev = iter++;
		GameEntity *tempPtr = *prev;
		if (tempPtr->getID() == PLAYER)
		{
			m_player = nullptr;
		}
		entityList.erase(prev);
		delete tempPtr;
	}
}

void EntityManager::Update( double deltaTime )
{
	for (GameEntity* object : entityList)
	{
		object->Update(deltaTime);
	}
}

void EntityManager::Draw()
{
	for (GameEntity* object : entityList)
	{
		object->Draw();
	}
}

void EntityManager::DoCollisions()
{
	//Check for collisions... Not the most efficient, but ok for now. can be changed later...
	//for now it campares every object, I can make it sector based later...
	for (std::list<GameEntity*>::iterator iter1 = begin(entityList); iter1 != end(entityList); ++iter1)
	{
		for (std::list<GameEntity*>::iterator iter2 = begin(entityList); iter2 != end(entityList); ++iter2)
		{
			if (iter1 != iter2) // Can't collide with yourself
			{
				if ((*iter1)->SameRegion(*iter2)) //Same Region?
				{
					if ((*iter1)->CheckCollision(*iter2)) //Did you collide?
					{
						(*iter1)->Collided(*iter2); //Do something about it.
					}
				}
			}
		}
	}
}

void EntityManager::RegisterPlayer( Player* player )
{
	m_player = player;
}

void EntityManager::UnregisterPlayer()
{
	m_player = nullptr;
}

Player* EntityManager::GetPlayer()
{
	return m_player;
}
