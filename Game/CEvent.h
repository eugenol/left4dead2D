#pragma once
#include <string>

enum EventType
{
	EVENT_PLAYER_STATS,
};

class CEvent
{
public:
	CEvent(EventType event, int message);
	virtual ~CEvent();

	EventType GetEventType();
	int GetMessage();

private:
	EventType m_event;
	int m_message;
};

class CPlayerStatEvent : public CEvent
{
public:
	CPlayerStatEvent(EventType event, int message, int health, int lives, int score, int megaShotCount)
	: CEvent(event, message), m_health(health), m_lives(lives), m_score(score), m_megaShotCount(megaShotCount) {}
	~CPlayerStatEvent() {}

	int GetPlayerHealth() { return m_health; }
	int GetPlayerLives() { return m_lives; }
	int GetPlayerScore() { return m_score; }
	int GetPlayerMegaShotCount() { return m_megaShotCount; }

private:
	int m_health;
	int m_lives;
	int m_score;
	int m_megaShotCount;
};