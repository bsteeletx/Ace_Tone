#pragma once
#include "Sprite.h"
//#include "File.h"

class Animation :
	public Sprite
{
public:
	~Animation(void);
	Animation(void);
	//Animation(unsigned int width, unsigned int height, unsigned int count, Text Filename, unsigned int assignedImageNumber, unsigned int assignedSpriteNumber = 0);
	Animation(unsigned int width, unsigned int height, unsigned int count, RFTPoint Begin, RFTPoint End);
	Animation(unsigned int width, unsigned int height, unsigned int count, Text Filename);
	Animation(unsigned int width, unsigned int height, unsigned int count, unsigned int parentImage, Text SubImageFilename);
	Animation(Read FileToInit, Text PathToParent);
	
	void AddFrame(Image NewFrame);

	void ClearFrames(void);
	
	unsigned int GetCurrentFrame(void);
	unsigned int GetFrameCount(void);
	bool GetPlaying();
	float GetPlaySpeed(void);
	
	void IncrementFrame(void);

	void Play(float fps = 10.0f, bool loop = true, unsigned int start = 1, unsigned int end = 0);
	
	void Resume(void);

	void SetFrame(unsigned int frame);
	void SetPosition(RFTPoint Location) override;
	void SetPosition(float x, float y) override;
	void SetSpeed(float fps);
	void SetVisible(bool visible) override;
	void Stop(void);

private:
	
	void _Set(unsigned int spriteID, unsigned int width, unsigned int height, unsigned int count);
	bool _Frame(unsigned int frame);
	bool _FPS(float fps);

	unsigned short _height;
	unsigned short _width;
	unsigned short _count;

	float _originalY;
	float _playSpeed;
};

