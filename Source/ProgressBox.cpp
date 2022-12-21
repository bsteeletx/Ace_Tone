#include "ProgressBox.h"
#include "AGKCore.h"

ProgressBox::ProgressBox()
{
}

ProgressBox::ProgressBox(Text ChordLetters, Image CommonParent)
{	
	AGKCore Counter;
	Text Temp;
	int tokens = 0;

	for (int i = 0; i < 4; i++)
	{
		_NoteOrder[i] = new NoteValues();
		_VisibleChord[i] = new Text("", true);
		//_UnderScores[i] = new Text("_ ", true);
		//_UnderScores[i]->SetVisible(false);
		_letterShown[i] = false;
	}

	tokens = Counter.CountStringTokens(ChordLetters, ',');

	for (int i = 0; i < tokens; i++)
	{
		if (i + 1 == tokens)
			Temp = ChordLetters;
		else
			ChordLetters.SplitAtDelimeter(&Temp, &ChordLetters, ',');

		//Temp.SetVisible(false);
		_ChordProgression.push_back(Temp);
	}
	
	//_Background = new Sprite(Color(0, 0, 255));
	//_Background->SetVisible(false);

	_chordCompleteTime = 0;
	_currentChord = 0;
}

ProgressBox::~ProgressBox()
{

}

void ProgressBox::Delete()
{
	for (int i = 0; i < 4; i++)
	{
		*_NoteOrder[i] = NOTEERROR;
		//_UnderScores[i]->Delete();
		_VisibleChord[i]->Delete();
		_letterShown[i] = false;
	}
		
	for (unsigned int i = 0; i < _ChordProgression.size(); i++)
		_ChordProgression[i].Delete();

	_ChordProgression.clear();
		
	//_Background->Delete();
	
	_currentChord = 0;
}

void ProgressBox::Hide()
{
	for (int i = 0; i < 4; i++)
		_VisibleChord[i]->SetVisible(false);
}

void ProgressBox::Init()
{
	AGKCore Converter;
	int notesInChord = 0;

	//count how many notes are in first chord
	if (_currentChord < _ChordProgression.size())
		notesInChord = Converter.Len(_ChordProgression[_currentChord]);
	else//pause and play success screen
		return;

	//Initialize first chord
	for (int i = 0; i < notesInChord; i++)
	{
		Text TempNote;
		char currentChar = _ChordProgression[_currentChord].GetChar(i);

		if (currentChar == 'f' || currentChar == '#') //we've already included this below, so skip
			continue;
		
		//set NoteOrder equal to appropriate Notes in first chord
		TempNote = Text(currentChar, true);
		//check for flats and sharps
		if (i + 1 < notesInChord)
		{
			char nextChar = _ChordProgression[_currentChord].GetChar(i + 1);
			
			if (nextChar == 'f' || nextChar == '#')
				TempNote += nextChar;

		}

		*_NoteOrder[i] = _ConvertToNoteValues(TempNote);
		
		//set visible text
		*_VisibleChord[i] = TempNote;
		_VisibleChord[i]->SetSize(10.0f);
		_VisibleChord[i]->SetDepth(10);
		_VisibleChord[i]->SetColor(Color(0, 0, 0));
		_VisibleChord[i]->SetPosition(RFTPoint(43.0f + (i * 5.0f), 89.0f));
		_VisibleChord[i]->SetVisible(false);

		/*_UnderScores[i]->SetSize(12.0f);
		_UnderScores[i]->SetDepth(10);
		_UnderScores[i]->SetColor(Color(255, 255, 255));
		_UnderScores[i]->SetPosition(Point(40.0f + (i * 5.0f), 90.0f));
		_UnderScores[i]->SetVisible(true);*/
	}

	/*_Background->SetVisible(true);
	_Background->SetSize(16.0f, 10.0f);
	_Background->SetPosition(Point(40.0f, 90.0f));
	_Background->SetDepth(20);*/
}

//////////////////////////
// Returns which part of chord Note is in, 
// 0 if not part ofchord
///////////////////////
int ProgressBox::GetProgressionPart(NoteValues Value, unsigned int currentTime)
{
	AGKCore Converter;

	//count how many notes are in first chord
	int notesInChord = Converter.Len(_ChordProgression[_currentChord]);

	for (int i = 0; i < notesInChord; i++)
	{
		if (Value == *_NoteOrder[i] && !_letterShown[i])
		{
			_ShowLetter(i);

			if (_AllNotesShown())
				_chordCompleteTime = currentTime;

			return i + 1;
		}
	}

	return 0;
}

///////////////////////////
// Returns how many letters are visible
///////////////////////////
unsigned short ProgressBox::GetVisibleLetters()
{
	int count = 0;

	if (_AllNotesShown())
		return 0;

	for (int i = 0; i < 4; i++)
	{
		if (_letterShown[i])
			count++;
	}

	return count;
}

void ProgressBox::Reset()
{
	//unsigned int numberOfChords = _ChordProgression.size();
	_currentChord = 0;
	_Reset();

	Init();

	/*for (int i = 0; i < 4; i++)
	{
		if (i >= numberOfChords)
			_UnderScores[i]->SetVisible(false);
	} */


}

void ProgressBox::Update(unsigned int currentTime)
{
	if (_AllNotesShown())
	{
		Color Change = Color(0, 0, 0);
		if (currentTime - _chordCompleteTime < 500)
			Change = Color(0, 0, 255);
		else if (currentTime - _chordCompleteTime < 1000)
			Change = Color(255, 0, 0);
		else
		{
			_Reset();
			Init();
		}

		for (unsigned int i = 0; i < 4; i++)
			_VisibleChord[i]->SetColor(Change);
	}
}

///////////////////////
// determines if all note of current chord have been shown
//////////////////////
bool ProgressBox::_AllNotesShown()
{
	for (int i = 0; i < 4; i++)
	{
		if (!_VisibleChord[i]->GetVisible())
			return false;
	}

	return true;
}

void ProgressBox::_Reset()
{
	for (int i = 0; i < 4; i++)
	{
		//_NoteOrder[i] = new NoteValues();
		_VisibleChord[i]->Delete();
		_VisibleChord[i] = new Text("", true);
		//_UnderScores[i]->Delete();
		//_UnderScores[i] = new Text("_ ", true);
		//_UnderScores[i]->SetVisible(false);
		_letterShown[i] = false;
	}
}

//////////////////////////
// Should return Text with appropriate Font
///////////////////////
void ProgressBox::_ShowLetter(int count)
{	
	_VisibleChord[count]->SetVisible(true);
	//_UnderScores[count]->SetVisible(false);
	_letterShown[count] = true;

	if (_AllNotesShown())
		_currentChord++;
}

////////////////////////////
// Converts Text Notes to NoteValues
////////////////////////////
NoteValues ProgressBox::_ConvertToNoteValues(Text Notes)
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