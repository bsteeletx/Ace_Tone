#include "ChordDisplayBox.h"
#include "AGKCore.h"

ChordDisplayBox::ChordDisplayBox()
{
}

ChordDisplayBox::ChordDisplayBox(Text ChordName)
{
	AGKCore Counter;
	int count = Counter.CountStringTokens(ChordName, ',');

	for (int i = 0; i < count; i++)
	{
		Text *TempText = new Text("", true);

		ChordName.SplitAtDelimeter(TempText, &ChordName, ',');
		TempText->SetVisible(false);

		if (*TempText != "")
			_ChordNames.push_back(TempText);
		else
		{
			TempText->SetString(ChordName.GetCString());
			_ChordNames.push_back(TempText);
		}

		//TempText->Delete();
	}

	/*_Background = new Sprite(Color(0, 0, 255));
	_Background->SetVisible(false);*/
	_currentChord = 0;
	_flashing = false;
	_correctChordTime = 0;
}

ChordDisplayBox::~ChordDisplayBox()
{

}

void ChordDisplayBox::Delete()
{
	for (int i = 0; i < _ChordNames.size(); i++)
		_ChordNames[i]->Delete();

	//_Background->Delete();
	_ChordNames.clear();
}

void ChordDisplayBox::DisplayNextChord(unsigned int currentTime)
{
	if (!_flashing)
	{
		_flashing = true;
		_correctChordTime = currentTime;
	}
	else
	{
	 	_ChordNames[_currentChord++]->SetVisible(false);
		_ChordNames[_currentChord]->SetVisible(true);
		_flashing = false;
	}
}

//////////////////////////
// Should return Text with appropriate Font
///////////////////////
Text ChordDisplayBox::GetName()
{
	return *_ChordNames[_currentChord];
}

void ChordDisplayBox::Hide()
{
	_ChordNames[_currentChord]->SetVisible(false);
}

void ChordDisplayBox::Init()
{
	/*_Background->SetVisible(true);
	_Background->SetSize(10.0f, 5.0f);
	_Background->SetPosition(Point(42.5f, 1.0f));
	_Background->SetDepth(10);*/

	for (int i = 0; i < _ChordNames.size(); i++)
	{
		_ChordNames[i]->SetColor(Color(0, 0, 0));
		_ChordNames[i]->SetDepth(5);
		_ChordNames[i]->SetAlignment(CENTER_ALIGNED);
		_ChordNames[i]->SetPosition(RFTPoint(50.0f, 1.0f));
		_ChordNames[i]->SetSize(7.5f);
		_ChordNames[i]->SetVisible(false);
	}

	_ChordNames[0]->SetVisible(true);
}

void ChordDisplayBox::Reset()
{
	_ChordNames[_currentChord]->SetVisible(false);
	
	_currentChord = 0;

	_ChordNames[_currentChord]->SetVisible(true);

	_ChordNames[_currentChord]->SetColor(Color(0, 0, 0));
}

void ChordDisplayBox::Update(unsigned int currentTime)
{
	if (_flashing)
	{
		if (currentTime - _correctChordTime < 500)
			_ChordNames[_currentChord]->SetColor(Color(0, 0, 255));
		else if (currentTime - _correctChordTime < 1000)
			_ChordNames[_currentChord]->SetColor(Color(255, 0, 0));
		else if (currentTime - _correctChordTime < 1500)
			_ChordNames[_currentChord]->SetColor(Color(0, 0, 255));
		else if (currentTime - _correctChordTime < 2000)
			_ChordNames[_currentChord]->SetColor(Color(255, 0, 0));
		else if (currentTime - _correctChordTime < 2500)
			_ChordNames[_currentChord]->SetColor(Color(0, 0, 255));
		else if (currentTime - _correctChordTime < 3000)
			_ChordNames[_currentChord]->SetColor(Color(255, 0, 0));
		else
			DisplayNextChord(currentTime);
	}
}