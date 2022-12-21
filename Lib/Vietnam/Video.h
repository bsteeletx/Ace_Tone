#ifndef _VIDEO_H_
#define _VIDEO_H_

#include "Point.h"
#include "Text.h"

class Video
{
public:
	Video(Text VideoFilename);
	~Video(void);

	void Delete();

	float GetDuration(void);
	short GetError(void);
	float GetHeight(void);
	bool GetPlaying(void);
	float GetPosition(void);
	float GetWidth(void);

	void Pause(void);
	void Play(void);

	void SetDimensions(RFTPoint Location, float width, float height);
	void SetVolume(float value);
	void Stop(void);
private:
	short _error;
};

#endif