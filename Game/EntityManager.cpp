#include "EntityManager.h"
#include <algorithm>


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


void EntityManager::UpdateList()
{
	// Call this each update loop, if the object is dead, delete it
	
	auto removeFunc = [this](GameEntity* entity) -> bool
	{
		if (!entity->getAlive())
		{
			GameEntity* tempPtr = entity;
			if (tempPtr->getID() == PLAYER)
			{
				m_player = nullptr;
			}
			delete tempPtr;
			return true;
		}
		else
		{
			return false;
		}
	};

	entityList.erase(std::remove_if(std::begin(entityList), std::end(entityList), removeFunc), std::end(entityList));
}

void EntityManager::AddEntity(GameEntity *entity)
{
	// add entity to the list
	entityList.push_back(entity);
}

void EntityManager::KillAll()
{
	auto removeFunc = [this](GameEntity* entity) -> bool
	{
			GameEntity* tempPtr = entity;
			if (tempPtr->getID() == PLAYER)
			{
				m_player = nullptr;
			}
			delete tempPtr;
			return true;
	};

	entityList.erase(std::remove_if(std::begin(entityList), std::end(entityList), removeFunc), std::end(entityList));
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

	for( GameEntity* entity1 : entityList )
	{
		for (GameEntity* entity2 : entityList)
		{
			if (entity1 != entity2 && entity1->SameRegion(entity2) ) // Can't collide with yourself
			{
				if (entity1->CheckCollision(entity2)) //Did you collide?
				{
					entity1->Collided(entity2); //Do something about it.
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
