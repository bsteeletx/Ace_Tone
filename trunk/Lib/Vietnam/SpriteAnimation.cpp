#include "agk.h"
#include "SpriteAnimation.h"

Animation::Animation()
	: Sprite()
{
}

Animation::~Animation()
{
}

Animation::Animation(unsigned int width, unsigned int height, unsigned int count, Text Filename)
	: Sprite(Filename)
{
	_Set(_spriteNumber, width, height, count);
}

/*Animation::Animation(unsigned int width, unsigned int height, unsigned int count, Point Begin, Point End)
	: Sprite(Begin, End)
{
	_Set(_spriteNumber, width, height, count);
} */

Animation::Animation(unsigned int width, unsigned int height, unsigned int count, unsigned int parentImage, Text SubImageFilename)
	: Sprite(parentImage, SubImageFilename)
{
	_Set(_spriteNumber, width, height, count);
}

/*AnimatedSprite::AnimatedSprite(unsigned int width, unsigned int height, unsigned int count, unsigned int assignedImageNumber, unsigned int parentImage, Text SubImageFilename, unsigned int assignedSpriteNumber)
	: Sprite(assignedImageNumber, parentImage, SubImageFilename, assignedSpriteNumber)
{
	set(_spriteNumber, width, height, count);
}*/

/*AnimatedSprite::AnimatedSprite(unsigned int width, unsigned int height, unsigned int count, unsigned int spriteNumberToClone)
	: Sprite()
{
	this->_spriteNumber = clone(spriteNumberToClone);
	set(_spriteNumber, width, height, count);
}*/

Animation::Animation(Read FileToInit, Text PathToParent)
	: Sprite(FileToInit, PathToParent)
{
	
	FileToInit.ReOpen();

	while(!FileToInit.IsEOF())
	{
		Text Line = FileToInit.Line();
		Text Start;
		Text End;

		Line.SplitAtDelimeter(&Start, &End, ':');

		if (Start == Text("Height"))
			_height = agk::Val(End.GetCString());
		else if (Start == Text("Width"))
			_width = agk::Val(End.GetCString());
		else if (Start == Text("Count"))
			_count = agk::Val(End.GetCString());
		else if (Start == Text("PlaySpeed"))
		{
			if (End == Text(""))
				continue;
			else
				_playSpeed = (float) agk::Val(End.GetCString());
		}
	}

	_Set(_spriteNumber, _width, _height, _count);

	FileToInit.Close();
}

void Animation::AddFrame(Image NewFrame)
{
	agk::AddSpriteAnimationFrame(_spriteNumber, NewFrame.GetID());
}

unsigned int Animation::GetCurrentFrame(void)
{
	return agk::GetSpriteCurrentFrame(_spriteNumber);
}

unsigned int Animation::GetFrameCount(void)
{
	return agk::GetSpriteFrameCount(_spriteNumber);
}

/*bool AnimatedSprite::GetVisible(void)
{
	if (GetY() <= 100.0f)
		return true;

	return false;
}*/

float Animation::GetPlaySpeed(void)
{
	return _playSpeed;
}

////////////////////////////
// Returns true if the sprite is currently playing an animation, 
// false if not.
///////////////////////////
bool Animation::GetPlaying()
{
	return (bool)agk::GetSpritePlaying(_spriteNumber);
}

void Animation::IncrementFrame(void)
{
	if (GetCurrentFrame() + 1 > GetFrameCount())
		SetFrame(1);
	else
		SetFrame(GetCurrentFrame() + 1);
}

void Animation::Play(float fps, bool loop, unsigned int start, unsigned int end)
{
	if (_Frame(start))
	{
		if (_Frame(end))
		{
			if (_FPS(fps))
				agk::PlaySprite(_spriteNumber, fps, loop, start, end);
		}
	}
}

void Animation::Resume(void)
{
	agk::ResumeSprite(_spriteNumber);
}

void Animation::SetFrame(unsigned int frame)
{
	if (_Frame(frame))
		agk::SetSpriteFrame(_spriteNumber, frame);
}

void Animation::SetPosition(RFTPoint Location)
{
	_originalY = Location.GetY();
	Sprite::SetPosition(Location);
}

void Animation::SetPosition(float x, float y)
{
	_originalY = y;
	Sprite::SetPosition(x, y);
}

void Animation::SetSpeed(float fps)
{
	if (_FPS(fps))
		agk::SetSpriteSpeed(_spriteNumber, fps);
}

void Animation::SetVisible(bool value)
{
	if (value)
		SetY(200.0f);
	else
		SetY(_originalY);
}

void Animation::Stop(void)
{
	agk::StopSprite(_spriteNumber);
}

void Animation::_Set(unsigned int spriteID, unsigned int width, unsigned int height, unsigned int count)
{
	if (width > 0)
	{
		if (height > 0)
		{
			if (count > 0)
			{
				agk::SetSpriteAnimation(_spriteNumber, width, height, count);
				this->_height = height;
				this->_width = width;
				this->_count = count;
			}
		}
	}
}

bool Animation::_Frame(unsigned int frame)
{
	if (frame != 0)
	{
		if (frame <= GetFrameCount())
			return true;
	}

	return false;
}

bool Animation::_FPS(float fps)
{
	if (fps > 0.0f)
		return true;

	return false;
}