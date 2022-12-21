#ifndef _PROGRESSSTAFF_H_
#define _PROGRESSSTAFF_H_

#include "Sprite.h"
#include "Text.h"
#include "Globals.h"

#define SIZE_OF_NOTE 0.75f
#define NOTE_INCREMENTS 0.4f

class ProgressStaff
{
public:
	ProgressStaff();
	ProgressStaff(unsigned int commonAtlasID, Text ChordNames);
	~ProgressStaff();

	void Delete();

	void Hide();

	void Init();

	void Reset();

	bool ShowChord();

private:
	std::vector<Sprite*> _Chords;
	std::vector<unsigned int> _numberOfNotes;
	std::vector<Text> _ChordsInProgression;
	std::vector<Sprite*> _Staves;
	//Sprite *_Staff;

	unsigned short _currentChord;
	unsigned short _numberOfChords;
	unsigned int _commonAtlasID;
	unsigned short _noteCounter;
	float _lowestYValue;
	unsigned short _chordInit;

	RFTPoint _GetNoteLocation(unsigned int chordNumber, Text NoteLetter = "");
	NoteValues _ConvertToNoteValues(Text NoteLetter);
};

#endif