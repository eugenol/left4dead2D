#pragma once
#include "GameEntity.h"

class CEvent;

class IObserver
{
public:
	IObserver();
	virtual ~IObserver();
	
	IObserver(const IObserver&) = delete;
	IObserver& operator=(const IObserver&) = delete;


	virtual void OnNotify( const GameEntity& entity, CEvent* event ) = 0;
};

