#pragma once

//-------------------------------------------------------

class Timer 
{
public:
	Timer();
	void Start();
	void Stop();
	bool IsRunning();
	void Update( double deltaTime );
	double GetTime();
	bool HasElapsed( double seconds );

private:
	bool m_running;
	double m_runTime;
};

//-------------------------------------------------------

