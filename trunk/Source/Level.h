#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "ChordDisplayBox.h"
#include "FailScreen.h"
#include "LivesIndicator.h"
#include "SettingsButton.h"
//#include "ProgressStaff.h"
#include "Score.h"
#include "Song.h"
#include "SuccessScreen.h"
#include "TutorialScreen.h"
#include "FileRead.h"
#include "AGKCore.h"
#include "SpriteEmitter.h"
#include "LevelBackground.h"
#include "LevelTimer.h"
#include "Image.h"
#include "2DPhysics.h"
#include "InputPointer.h"
#include "SuccessSound.h"
#include "FailSound.h"
#include "SettingsScreen.h"
#include "ScoreRecord.h"
#include "MagicPointer.h"

class Level
{
public:
	Level(unsigned int level, unsigned int commonAtlasID);
	~Level();

	//Level& operator= (const Level& NewLevel);
	void Delete();

	void Init();

	//void SetLevelNumber(unsigned int level);

	//returns score, -1 if still playing, 0 for fail
	ExitLevelCode Update();

private:
	FailScreen *_FailScreen;
	SuccessScreen *_SuccessScreen;
	SpriteEmitter *_SpriteEmitter;
	LivesIndicator *_LivesIndicator;
	SettingsButton *_SettingsButton;
	LevelTimer *_LevelTimer;
	LevelBackground *_LevelBackground;
	//Image *_CommonAtlas;
	Image *_LevelAtlas;
	Physics2D *_PhysicsSettings;
	AGKCore *_UpdateTimer;
	MagicPointer *_Pointer;
	SuccessSound *_SuccessSound;
	FailSound *_FailSound;
	Song *_Song;
	//ProgressStaff *_ProgressStaff;
	TutorialScreen *_TutorialScreen;
	SettingsScreen *_SettingsScreen;
	Sound *_AddTime;
	Sound *_LoseTime;
	ScoreRecord *_Records[3];
	RFTPoint *_LastMousePos;
	Sprite *_UIElements;

	unsigned short _levelID;
	unsigned int _currentSeconds;
	unsigned int _drumStartTime;
	unsigned int _commonAtlasID;
	bool _playedDrums;
	bool _passedLevel;
	bool _justStarted;
	float _notePercentages[NUMBER_OF_NOTES];
	
#if OS == PC
	bool _mouseDown;
	Vector *_DragLine;
#endif
	bool _HasMouseMoved(RFTPoint CurrentPos);
	
	void _Load(Text TextFile);

	void _PauseGame();
	void _PauseHandler();

	void _Restart(unsigned int currentTime);
	void _ResumeGame();

	void _ShowTutorial();
	void _SlashHandler();
	bool _SongHandler();

	void _UpdateSpriteEmitter();
	void _UpdateLevelTimer();
	ExitLevelCode _UpdateUI();

	
};
#endif