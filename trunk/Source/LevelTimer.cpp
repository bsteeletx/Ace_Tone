#include "LevelTimer.h"
#include "AGKCore.h"

LevelTimer::LevelTimer()
: AGKTime()
{}

LevelTimer::LevelTimer(unsigned short seconds)
: AGKTime()
{}

LevelTimer::LevelTimer(Text TextSeconds, unsigned int currentTime)
: AGKTime()
{
	AGKCore Converter;

	_startTime = currentTime;
	_timeLimit = (Converter.Val(TextSeconds) * SECONDS);
	_timeOut = false;
}

LevelTimer::~LevelTimer()
{}

void LevelTimer::AddTime(unsigned int amount)
{
	_startTime += amount;
}

void LevelTimer::Delete()
{
	_TimerDisplay->Delete();
}

void LevelTimer::Init()
{
	AGKCore Converter;

	_TimerDisplay = new Text("0:", true);
	*_TimerDisplay += Converter.Str((float)((_timeLimit - _startTime) / SECONDS), 0);
	_TimerDisplay->SetAlignment(RIGHT_ALIGNED);
	_TimerDisplay->SetColor(Color(0, 0, 255));
	_TimerDisplay->SetSize(7.5f);
	_TimerDisplay->SetPosition(RFTPoint(96.0f, 2.0f));
	_isPaused = false;
}

unsigned int LevelTimer::GetLastUpdateTime()
{
	return _lastUpdate;
}

unsigned int LevelTimer::GetSecondsLeft()
{
	AGKCore Converter;
	Text *TempSeconds = new Text();
	Text *TempMinutes = new Text();
	unsigned int timeLeft = 0;

	_TimerDisplay->SplitAtDelimeter(TempMinutes, TempSeconds, ':');

	timeLeft = Converter.Val(*TempMinutes) * 60;
	timeLeft += Converter.Val(*TempSeconds);

	return timeLeft;
}

void LevelTimer::Hide()
{
	_TimerDisplay->SetVisible(false);
}

void LevelTimer::Pause()
{
	_isPaused = true;
}

void LevelTimer::RemoveTime(unsigned int amount)
{
	_startTime -= amount;
}

void LevelTimer::Restart(unsigned int currentTime)
{
	_startTime = currentTime;
	_lastUpdate = currentTime;
	_timeOut = false;
	_isPaused = false;
}

void LevelTimer::Resume(unsigned int currentTime)
{
	unsigned int timeElapsed = currentTime - _lastUpdate;

	_startTime += timeElapsed;
	_lastUpdate += timeElapsed;

	_isPaused = false;
}

bool LevelTimer::Update(unsigned int currentTime)
{
	AGKCore Converter;
	Text *Temp = new Text("0:", true);
	short timeLeft = 0;
	bool textIsBlue = (_TimerDisplay->GetColorBlue() == 255);

	if (_timeOut || _isPaused)
	{
		Temp->SetVisible(false);
		return false;
	}

	_lastUpdate = currentTime;

	_TimerDisplay->Delete();
	_TimerDisplay = Temp;
	
	timeLeft = ((_timeLimit + _startTime) - currentTime) / SECONDS;

	if (timeLeft < 0)
		timeLeft = 0;

	if (timeLeft < 10)
		*_TimerDisplay += "0";

	if (timeLeft > 0)
		*_TimerDisplay += Converter.Str(((_timeLimit + _startTime) - currentTime) / SECONDS);
	else
		*_TimerDisplay += "0";

	_TimerDisplay->SetAlignment(RIGHT_ALIGNED);

	if (timeLeft < 10)
	{
		if (textIsBlue)
			_TimerDisplay->SetColor(Color(255, 0, 0));
		else
			_TimerDisplay->SetColor(Color(0, 0, 255));
	}
	else 
		_TimerDisplay->SetColor(Color(0, 0, 255));

	_TimerDisplay->SetSize(7.5f);
	_TimerDisplay->SetPosition(RFTPoint(96.0f, 2.0f));

	if (timeLeft == 0)
	{
		_timeOut = true;
		return true;
	}
	
	return false;
}