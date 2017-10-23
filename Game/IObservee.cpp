#include "IObservee.h"
#include "CEvent.h"
#include "IObserver.h"
#include <algorithm>


IObservee::IObservee()
{
}


IObservee::~IObservee()
{
}

void IObservee::AddObserver( IObserver* observer )
{
	std::vector<IObserver*>::iterator it;
	it = find(begin(m_observers), end(m_observers), observer);
	if ( it == end(m_observers))
	{
		m_observers.push_back( observer );
	}
}

void IObservee::RemoveObserver( IObserver* observer )
{
	m_observers.erase(std::remove(begin(m_observers), end(m_observers), observer), end(m_observers));
}

void IObservee::Notify( const GameEntity& entity, CEvent* event )
{
	for( IObserver* observer: m_observers )
	{
		observer->OnNotify( entity, event );
	}
}
