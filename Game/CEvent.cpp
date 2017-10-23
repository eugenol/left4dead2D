#include "CEvent.h"



CEvent::CEvent( EventType event, int message )
	:
	m_event( event ),
	m_message( message )
{
}

CEvent::~CEvent()
{
}

EventType CEvent::GetEventType()
{
	return m_event;
}

int CEvent::GetMessage()
{
	return m_message;
}
