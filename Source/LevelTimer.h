#ifndef _LEVELTIMER_H_
#define _LEVELTIMER_H_

#include "AGKTime.h"

class LevelTimer : public AGKTime
{
public:
	LevelTimer();
	LevelTimer(Text TextSeconds, unsigned int currentTime);
	LevelTimer(unsigned short seconds);
	~LevelTimer();

	void AddTime(unsigned int amount);

	void Delete();

	unsigned int GetLastUpdateTime();
	unsigned int GetSecondsLeft();

	void Hide();

	void Init();

	void Pause();
	
	void RemoveTime(unsigned int amount);
	void Restart(unsigned int currentTime);
	void Resume(unsigned int currentTime);

	bool Update(unsigned int currentTime);

private:
	bool _isPaused;
	unsigned int _startTime;
	unsigned int _timeLimit;
	unsigned int _lastUpdate;
	Text *_TimerDisplay;
	bool _timeOut;

};

#endif