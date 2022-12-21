#ifndef _PROGRESSBOX_H_
#define _PROGRESSBOX_H_

#include "Sprite.h"
#include "Text.h"
#include "Globals.h"

class ProgressBox
{
public:
	ProgressBox();
	ProgressBox(Text ChordLetters, Image CommonParent);
	~ProgressBox();

	void Delete();

	Text GetChordProgressionNotes();
	int GetProgressionPart(NoteValues Value, unsigned int currentTime);
	unsigned short GetVisibleLetters();

	void Hide();

	void Init();
	
	void Reset();
	//might need a set color

	void Update(unsigned int currentTime);

private:
	NoteValues *_NoteOrder[4];
	//Text *_UnderScores[4];
	Text *_VisibleChord[4];
	std::vector<Text> _ChordProgression;
	//Sprite *_Background;

	bool _letterShown[4];
	unsigned short _currentChord;
	unsigned int _chordCompleteTime;

	bool _AllNotesShown();
	
	NoteValues _ConvertToNoteValues(Text TextNotes);

	void _Reset();

	void _ShowLetter(int count);
};

#endif