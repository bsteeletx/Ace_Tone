#include "Music.h"
#include "AGKCore.h"
#include "agk.h"

Music::Music(void)
{
	_musicNumber = 0;
}

Music::~Music(void)
{
	//if(GetExists())
	//	agk::DeleteMusic(_musicNumber);
}

Music::Music(unsigned short assignedID, Text Filename)
{
	if (_Filename(Filename))
	{
		if (assignedID <= 50)
		{
			agk::LoadMusic(assignedID, Filename.GetCString());
			_musicNumber = assignedID;
		}
	}
}

Music::Music(Text Filename)
{
	if (_Filename(Filename))
		_musicNumber = agk::LoadMusic(Filename.GetCString());
}

void Music::Delete()
{
	agk::DeleteMusic(_musicNumber);
}

bool Music::GetExists(void)
{
	if (agk::GetMusicExists(_musicNumber) == 1)
		return true;

	return false;
}

unsigned int Music::GetID()
{
	return _musicNumber;
}

bool Music::GetPlaying(void)
{
	if (agk::GetMusicPlaying() == _musicNumber)
		return true;

	return false;
}

void Music::Pause(void)
{
	agk::PauseMusic();
}

void Music::Play(bool loop, unsigned int startID, unsigned int endID)
{
	int bloop = 0;

	if (loop)
		bloop = 1;

	if (startID == 0 || endID == 0)
		agk::PlayMusic(_musicNumber, bloop, _musicNumber, _musicNumber);
	else
		agk::PlayMusic(_musicNumber, bloop, startID, endID);
}

void Music::Resume(void)
{
	agk::ResumeMusic();
}

void Music::SetFileVolume(unsigned short volume)
{
	if (volume <= 100)
		agk::SetMusicFileVolume(_musicNumber, volume);
}

void Music::SetSystemVolume(unsigned short volume)
{
	if (volume <= 100)
		agk::SetMusicSystemVolume(volume);
}

void Music::Stop(void)
{
	agk::StopMusic();
}

bool Music::_Filename(Text Filename)
{
	AGKCore Conversion;
	Text Extension = Conversion.Right(Filename, 4);
	//short lengthOfString = Filename.GetLength() - 1;

	//for (int i = 3; i > 0; i--)
		//tempFilename[i] = Filename.GetChar(lengthOfString - 1);
	
	if (Extension == Text(".wav"))
		return true;
	if (Extension == Text(".mp3"))
		return true;
	if (Extension == Text(".ogg"))
		return true;
	if (Extension == Text(".m4a"))
		return true;

	return false;
}