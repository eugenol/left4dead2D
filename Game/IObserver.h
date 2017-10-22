#pragma once
#include "GameEntity.h"

class CEvent;

class IObserver
{
public:
	IObserver();
	virtual ~IObserver();
	
	virtual void OnNotify( const GameEntity& entity, CEvent event ) = 0;

};

