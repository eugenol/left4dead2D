#include "GameTimer.h"
#include "InitData.h"
#include "string.h"

//-------------------------------------------------------

GameTimer::GameTimer() :
deltaTimeStr(),
isAlive(true)
{
	time(&startTime);
	timerFont = al_load_ttf_font("pirulen.ttf", 30, 0);
}

//-------------------------------------------------------

GameTimer::~GameTimer()
{
}

//-------------------------------------------------------

void GameTimer::draw()
{
	if (isAlive)
	{
		UpdateTime();
	}

	al_draw_text(timerFont, al_map_rgb(78, 239, 9), 620, 5, 0, deltaTimeStr);
}

//-------------------------------------------------------

void GameTimer::update()
{
}

//-------------------------------------------------------

void GameTimer::UpdateTime()
{
	time_t curTime;
	time(&curTime);

	int deltaSeconds = difftime(curTime, startTime);

	int hoursElapsed = (deltaSeconds / 60) / 60;
	int minutesElapsed = (deltaSeconds / 60) % 60;
	int secondsElapsed = deltaSeconds % 60;

	std::string minutesStr = "";
	std::string secondsStr = "";
	std::string hoursStr = "";

	std::string timeStr;

	char hoursCharBuffer[1000000];
	_itoa_s(hoursElapsed,hoursCharBuffer, 10);

	std::string hoursConvertedToString = hoursCharBuffer;

	char minutesCharBuffer[3];
	_itoa_s(minutesElapsed, minutesCharBuffer, 10);

	std::string minutesConvertedToString = minutesCharBuffer;

	char secondsCharBuffer[3];
	_itoa_s(secondsElapsed, secondsCharBuffer, 10);

	std::string secondsConvertedToString = secondsCharBuffer;

	if (hoursElapsed < 10)
	{
		if (hoursElapsed == 0)
		{
			hoursStr = "00";
		}
		else
		{
			hoursStr = "0" + hoursConvertedToString;
		}
	}
	else
	{
		hoursStr = hoursStr + hoursConvertedToString;
	}

	if (minutesElapsed < 10)
	{
		if (minutesElapsed == 0)
		{
			minutesStr = "00";
		}
		else
		{
			minutesStr = "0" + minutesConvertedToString;
		}
	}
	else
	{
		minutesStr = minutesStr + minutesConvertedToString;
	}
	if (secondsElapsed < 10)
	{
		if (secondsElapsed == 0)
		{
			secondsStr = "00";
		}
		else
		{
			secondsStr = "0" + secondsConvertedToString;
		}
	}
	else
	{
		secondsStr = secondsStr + secondsConvertedToString;
	}

	timeStr = hoursStr + ":" + minutesStr + ":" + secondsStr;
	strcpy_s(deltaTimeStr, timeStr.c_str());
}

//-------------------------------------------------------