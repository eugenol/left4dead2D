#include "Timer.h"

//-------------------------------------------------------

Timer::Timer() :
m_running(false),
m_start(0)
{
}

//-------------------------------------------------------

void Timer::Start() 
{
	if (!m_running) 
	{
		m_start = (unsigned long)clock();
		m_running = true;
	}
}

//-------------------------------------------------------

void Timer::Stop() 
{
	if (m_running) 
	{
		m_start = 0;
		m_running = false;
	}
}

//-------------------------------------------------------

bool Timer::IsRunning() 
{
	return m_running;
}

//-------------------------------------------------------

unsigned long Timer::GetTime() 
{
	if (m_running)
	{
		return ((unsigned long)clock() - m_start) / CLOCKS_PER_SEC;
	}
	
	return -1;
}

//-------------------------------------------------------

bool Timer::HasElapsed(unsigned long seconds) 
{
	if (GetTime() == -1)
	{
		return false;
	}

	return GetTime() >= seconds;
}

//-------------------------------------------------------
