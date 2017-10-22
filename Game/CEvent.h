#pragma once
#include <string>

enum EventType
{
	EVENT_TEST,
};

class CEvent
{
public:
	CEvent(EventType event, std::string message);
	~CEvent();

	EventType GetEventType() { return m_event; }
	std::string GetMessage() { return m_message; }

private:
	EventType m_event;
	std::string m_message;
};

