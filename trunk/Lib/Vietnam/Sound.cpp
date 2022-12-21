#include "agk.h"
#include "AGKCore.h"
#include "Sound.h"

/*FMOD::System *system;
FMOD_RESULT result;
unsigned int version;*/

Sound::Sound(void)
{
	_soundID = 0;
}

Sound::~Sound(void)
{

}

Sound::Sound(unsigned int assignedNumber, Text Filename)
{
	




	/*if (assignedNumber)
	{
		if (_Filename(Filename))
		{
			agk::LoadSound(assignedNumber, Filename.GetCString());
			_soundID = assignedNumber;
		}
	} */
}

Sound::Sound(Text Filename, bool loop)
{	   /*
	//FMOD Setup
	result = FMOD::System_Create(&system);

	if (result != FMOD_OK)
	{
		//error
	}

	if (version < FMOD_VERSION)
	{
		//error
	}

	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);

	if (result != FMOD_OK)
	{
		//error
	}

	result = system->createSound(Filename.GetCString(), FMOD_DEFAULT, 0, &sound);

	if (result != FMOD_OK)
	{
		//error
	}

	if (loop)
	{
		result = sound->setMode(FMOD_LOOP_OFF);

		if (result != FMOD_OK)
		{
			//error
		}

	}	   */

	if (_Filename(Filename))
		_soundID = agk::LoadSound(Filename.GetCString());
}

void Sound::Delete()
{
	agk::DeleteSound(_soundID);
}

bool Sound::GetExists(void)
{
	if (agk::GetSoundExists(_soundID) == 1)
		return true;

	return false;
}

unsigned int Sound::GetInstances(void)
{
	return agk::GetSoundInstances(_soundID);
}

/* Not Functional Yet
bool Sound::IsRecording()
{
	return (bool)agk::IsSoundRecording();
}
*/

void Sound::Play(unsigned short volume, bool loop)
{
	if (volume <= 100)
	{
		if (loop)
			agk::PlaySound(_soundID, volume, 1);
		else
			agk::PlaySound(_soundID, volume, 0);
	}
}

void Sound::SetSystemVolume(unsigned short volume)
{
	if (volume <= 100)
		agk::SetSoundSystemVolume(volume);
}

void Sound::Stop(void)
{
	agk::StopSound(_soundID);
}

bool Sound::_Filename(Text Filename)
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

	return false;
}