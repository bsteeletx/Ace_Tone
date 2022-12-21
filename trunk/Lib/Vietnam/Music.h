#ifndef _MUSIC_H_
#define _MUSIC_H_

#include "Text.h"

class Music
{
public:
	Music();
	~Music();
	Music(unsigned short assignedID, Text Filename);
	Music(Text Filename);

	void Delete();

	bool GetExists(void);
	unsigned int GetID();
	bool GetPlaying(void);

	void Pause(void);
	void Play(bool loop = true, unsigned int startMusicID = 0, unsigned int endMusicID = 0);
	
	void Resume(void);

	void SetFileVolume(unsigned short volume);
	void SetSystemVolume(unsigned short volume);
	void Stop(void);

private:
	unsigned short _musicNumber;

	bool _Filename(Text Filename);
};

#endif