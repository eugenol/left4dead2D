#pragma once

#include <conio.h>
#include <time.h>

//-------------------------------------------------------

class Timer 
{
public:
	Timer();
	void Start();
	void Stop();
	bool IsRunning();
	unsigned long  GetTime();
	bool HasElapsed(unsigned long seconds);

private:
	bool m_running;
	unsigned long m_start;
};

//-------------------------------------------------------

