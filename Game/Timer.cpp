#include "Timer.h"

//-------------------------------------------------------

Timer::Timer( double timerDuration ) :
m_running( false ),
m_runTime( 0 ),
m_timerDuration( timerDuration )
{
}

//-------------------------------------------------------

void Timer::Start() 
{
	if (!m_running) 
	{
		m_runTime = 0.0;
		m_running = true;
	}
}

//-------------------------------------------------------

void Timer::Stop() 
{
	if (m_running) 
	{
		m_runTime = 0;
		m_running = false;
	}
}

//-------------------------------------------------------

bool Timer::IsRunning() 
{
	return m_running;
}

//-------------------------------------------------------

void Timer::Update( double deltaTime )
{
	m_runTime += deltaTime;
}

//-------------------------------------------------------

double Timer::GetTime() 
{
	if (m_running)
	{
		return m_runTime;
	}
	
	return -1;
}

//-------------------------------------------------------

bool Timer::HasElapsed() 
{
	if (GetTime() < 0)
	{
		return false;
	}

	return GetTime() >= m_timerDuration;
}

//-------------------------------------------------------

void Timer::SetTimerDuration( double timerDuration )
{
	m_timerDuration = timerDuration;
}

//-------------------------------------------------------
