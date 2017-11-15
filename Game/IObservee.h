#pragma once
#include <vector>

class CEvent;
class GameEntity;
class IObserver;

class IObservee
{
public:
	virtual ~IObservee();

	void AddObserver( IObserver* observer );
	void RemoveObserver( IObserver* observer );

	IObservee(const IObservee&) = delete;
	IObservee& operator=(const IObservee&) = delete;

protected:
	IObservee();
	void Notify( const GameEntity& entity, CEvent* event );

private:
	std::vector<IObserver*> m_observers;
};

