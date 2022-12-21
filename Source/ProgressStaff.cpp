#include "ProgressStaff.h"
#include "AGKCore.h"

ProgressStaff::ProgressStaff()
{
	//_Staff = new Sprite();
}

ProgressStaff::ProgressStaff(unsigned int commonAtlasID, Text ChordNames)
{
	AGKCore Counter;
	Text Temp = "";
	Text ChordLetters = ChordNames;
	_commonAtlasID = commonAtlasID;
	_numberOfChords = Counter.CountStringTokens(ChordNames, ',');
	
	for (int i = 0; i < _numberOfChords; i++)
	{
		if (i + 1 == _numberOfChords)
			Temp = ChordLetters;
		else
			ChordLetters.SplitAtDelimeter(&Temp, &ChordLetters, ',');

		_ChordsInProgression.push_back(Temp);

		_Staves.push_back(new Sprite(Color(0, 0, 0)));
		_Staves[i]->SetVisible(false);
	} 

	//_Staff = new Sprite();
	//_Staff->SetVisible(false);
	
	_currentChord = 0;
	_noteCounter = 0;
	_lowestYValue = 100.0f;
	_chordInit = 0;
}

ProgressStaff::~ProgressStaff()
{}

void ProgressStaff::Delete()
{
	for (unsigned int i = 0; i < _Chords.size(); i++)
		_Chords[i]->Delete();

	//_Staff->Delete();

	_Chords.clear();

	_ChordsInProgression.clear();
}

RFTPoint ProgressStaff::_GetNoteLocation(unsigned int chordNumber, Text NoteLetter)
{
	RFTPoint Default = RFTPoint(65.0f + (chordNumber * 5.0f), 93.5f);

	if (_chordInit != chordNumber)
	{
		_chordInit = chordNumber;
		_lowestYValue = 100.0f;
	}

	if (NoteLetter == "")
	{
		Default.SetY(_lowestYValue + NOTE_INCREMENTS);
		return Default;
	}

	NoteValues ThisNote = _ConvertToNoteValues(NoteLetter);
	
	
	switch (ThisNote)
	{
	case A:
		Default.AddPoint(RFTPoint(0.0f, NOTE_INCREMENTS * 2));
		break;
	case ASHARP:
		Default.AddPoint(RFTPoint(0.0f, NOTE_INCREMENTS * 2));
		break;
	case BFLAT:
		Default.AddPoint(RFTPoint(0.0f, NOTE_INCREMENTS));
		break;
	case B:
		Default.AddPoint(RFTPoint(0.0f, NOTE_INCREMENTS));
		break;
	case BSHARP:
		Default.AddPoint(RFTPoint(0.0f, NOTE_INCREMENTS));
		break;
	case CFLAT:
		break;
	case C:
		break;
	case CSHARP:
		break;
	case DFLAT:
		Default.AddPoint(RFTPoint(0.0f, NOTE_INCREMENTS * 6));
		break;
	case D:
		Default.AddPoint(RFTPoint(0.0f, NOTE_INCREMENTS * 6));
		break;
	case DSHARP:
		Default.AddPoint(RFTPoint(0.0f, NOTE_INCREMENTS * 6));
		break;
	case EFLAT:
		Default.AddPoint(RFTPoint(0.0f, NOTE_INCREMENTS * 5));
		break;
	case E:
		Default.AddPoint(RFTPoint(0.0f, NOTE_INCREMENTS * 5));
		break;
	case ESHARP:
		Default.AddPoint(RFTPoint(0.0f, NOTE_INCREMENTS * 5));
		break;
	case FFLAT:
		Default.AddPoint(RFTPoint(0.0f, NOTE_INCREMENTS * 4));
		break;
	case F:
		Default.AddPoint(RFTPoint(0.0f, NOTE_INCREMENTS * 4));
		break;
	case FSHARP:
		Default.AddPoint(RFTPoint(0.0f, NOTE_INCREMENTS * 4));
		break;
	case GFLAT:
		Default.AddPoint(RFTPoint(0.0f, NOTE_INCREMENTS * 3));
		break;
	case G:
		Default.AddPoint(RFTPoint(0.0f, NOTE_INCREMENTS * 3));
		break;
	case GSHARP:
		Default.AddPoint(RFTPoint(0.0f, NOTE_INCREMENTS * 3));
		break;
	case AFLAT:
		Default.AddPoint(RFTPoint(0.0f, NOTE_INCREMENTS * 2));
		break;
	}

	if (_lowestYValue > Default.GetY())
		_lowestYValue = Default.GetY();

	return Default;
}

void ProgressStaff::Hide()
{
	for (unsigned int i = 0; i < _Chords.size(); i++)
		_Chords[i]->SetVisible(false);

	//_Staff->SetVisible(false);
}

void ProgressStaff::Init()
{
	for (unsigned int i = 0; i < _ChordsInProgression.size(); i++)
	{
		for (unsigned int j = 0; j < _ChordsInProgression[i].GetLength(); j++)
		{
			Sprite *Chord = new Sprite(_commonAtlasID, "note.png");
			Chord->SetPosition(_GetNoteLocation(i, _ChordsInProgression[i].GetChar(j)));
			Chord->SetSize(SIZE_OF_NOTE);
			Chord->SetDepth(5);
			Chord->SetVisible(false);
			_Chords.push_back(Chord);
		}

		_numberOfNotes.push_back(_ChordsInProgression[i].GetLength());

		_Staves[i]->SetPosition(_GetNoteLocation(i));
		_Staves[i]->SetSize(0.125f, SIZE_OF_NOTE * 6);
		_Staves[i]->SetDepth(5);
		_Staves[i]->SetVisible(false);
	}

	//_Staff = new Sprite(_commonAtlasID, "staff.jpg");

	//_Staff->SetSize(33.3f);
	//_Staff->SetPosition(Point(55.0f, 90.0f));
	//_Staff->SetVisible(true);
}

void ProgressStaff::Reset()
{
	for (unsigned int i = 0; i < _Chords.size(); i++)
		_Chords[i]->SetVisible(false);

	_currentChord = 0;
	_noteCounter = 0;
}										

//////////////////////////////
// Shows next chord
// if song is complete, returns true
bool ProgressStaff::ShowChord()
{
	for (unsigned int i = 0; i < _numberOfNotes[_currentChord]; i++)
		_Chords[_noteCounter++]->SetVisible(true);
	
	_Staves[_currentChord++]->SetVisible(true);

	if (_currentChord == _numberOfChords)
		return true;

	return false;
}


////////////////////////////
// Converts Text Notes to NoteValues
////////////////////////////
NoteValues ProgressStaff::_ConvertToNoteValues(Text Notes)
{
	///////////Not sure there's a better way than this :(
	if (Notes == "A")
		return A;
	if (Notes == "A#")
		return ASHARP;
	if (Notes == "Bf")
		return BFLAT;
	if (Notes == "B")
		return B;
	if (Notes == "B#")
		return BSHARP;
	if (Notes == "Cf")
		return CFLAT;
	if (Notes == "C")
		return C;
	if (Notes == "C#")
		return CSHARP;
	if (Notes == "Df")
		return DFLAT;
	if (Notes == "D")
		return D;
	if (Notes == "D#")
		return DSHARP;
	if (Notes == "Ef")
		return EFLAT;
	if (Notes == "E")
		return E;
	if (Notes == "E#")
		return ESHARP;
	if (Notes == "Ff")
		return FFLAT;
	if (Notes == "F")
		return F;
	if (Notes == "F#")
		return FSHARP;
	if (Notes == "Gf")
		return GFLAT;
	if (Notes == "G")
		return G;
	if (Notes == "G#")
		return GSHARP;
	if (Notes == "Af")
		return AFLAT;

	return NOTEERROR;
}