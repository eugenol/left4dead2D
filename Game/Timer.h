#pragma once

//-------------------------------------------------------

class Timer 
{
public:
	Timer( double timerDuration );
	void Start();
	void Stop();
	bool IsRunning();
	void Update( double deltaTime );
	double GetTime();
	bool HasElapsed();
	void SetTimerDuration(double timerDuration);

private:
	bool m_running;
	double m_runTime;
	double m_timerDuration;
};

//-------------------------------------------------------

