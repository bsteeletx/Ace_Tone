#ifndef _SONGTITLE_H_
#define _SONGTITLE_H_

#include "Text.h"
#include "Music.h"
#include "FileRead.h"
#include "ProgressBox.h"
#include "ChordDisplayBox.h"
#include "Globals.h"
#include "Sound.h"

class Song
{
public:
	Song();
	~Song();

	void Delete();

	void Hide();

	void Init(Text *LevelFile, unsigned int commonAtlasID, unsigned short levelNum);
	bool IsBackgroundPlaying();
	bool IsDrumStartPlaying();
	bool IsRewardPlaying();

	unsigned int GetDrumLength();
	bool GetOnNewChord();
	int GetSuccessfulHit(NoteValues ChordHit, unsigned int currentTime);

	void PauseBackground();
	void PlayBackground();
	void PlayDrumStart();
	void PlayReward();

	void Reset();
	void ResumeBackground();

	void Update(unsigned int currentTime);
	
private:
	Text *_Title;
	Text *_TrackNum;
	Sound *_DrumStart;
	Music *_BackgroundMusic;
	//Music *_BackgroundMusic2;
	Music *_RewardMusic;
	ProgressBox *_ProgressBox;
	ChordDisplayBox *_ChordDisplayBox;
	std::vector<Sound*> _Chords;
	Text *_RewardMusicLocation;

	unsigned int _currentChord;
	unsigned int _drumLength;
};

#endif