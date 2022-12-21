#ifndef _GLOBALS_H_
#define _GLOBALS_H_
/////////////CLASS INCLUDES
//#include "agk.h"
#include "agk.h"
//#include "VietnamCore.h"
#include "Defines.h"

enum Screens
{
	BACKGROUND,
	TUTORIAL,
	PAUSE,
	FAIL,
	SUCCESS
};

enum Buttons
{
	SETTINGS,
	RESTART,
	MUTE
};

enum NoteValues
{
	NOTEERROR,
	A,
	ASHARP,
	BFLAT,	   
	B,
	BSHARP,
	CFLAT,
	C,
	CSHARP,
	DFLAT,
	D,
	DSHARP,
	EFLAT,
	E,
	ESHARP,
	FFLAT,
	F,
	FSHARP,
	GFLAT,
	G,
	GSHARP,
	AFLAT,
	EIGHTHNOTE,
	EIGHTHREST,
	QUARTERNOTE, 
	QUARTERREST,
	HALFNOTE,
	HALFREST
};

#define NUMBER_OF_NOTES 27 //equal to HALFREST

enum Crossings
{
	NO_CROSSINGS,
	TOPANDLEFT,
	TOPANDRIGHT,
	BOTTOMANDLEFT,
	BOTTOMANDRIGHT,
	HORIZONTAL_THROUGH,
	VERTICAL_THROUGH
};

enum DIFFICULTY
{
	EASY,
	AVERAGE,
	HARD,
};

enum ExitLevelCode
{
	STILLPLAYING = -1,
	FAILEDSONG,
	RTM_1SCORE,
	RTM_2SCORE,
	RTM_3SCORE,
	NS_1SCORE = 5,
	NS_2SCORE,
	NS_3SCORE
};

#define NUMBER_OF_SONGS 36 

#endif