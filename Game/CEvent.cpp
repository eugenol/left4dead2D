#include "CEvent.h"



CEvent::CEvent( EventType event, std::string message )
	:
	m_event( event ),
	m_message( message )
{
}

CEvent::~CEvent()
{
}
