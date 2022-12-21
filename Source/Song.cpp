#include "Song.h"
#include "AGKCore.h"

Song::Song()
{
	_BackgroundMusic = new Music();
	//_BackgroundMusic2 = new Music();
	_DrumStart = new Sound();
	_RewardMusic = new Music();
	_ProgressBox = new ProgressBox();
	_ChordDisplayBox = new ChordDisplayBox();
	_TrackNum = new Text();
	_drumLength = 0;
}

Song::~Song()
{}

void Song::Delete()
{
	_Title->Delete();
	_BackgroundMusic->Delete();
	//_BackgroundMusic2->Delete();
	_RewardMusic->Delete();
	_ProgressBox->Delete();
	_ChordDisplayBox->Delete();
	_DrumStart->Delete();
	_TrackNum->Delete();

	for (unsigned int i = 0; i < _Chords.size(); i++)
		_Chords[i]->Delete();

	_Chords.clear();
	
	_currentChord = 0;
}

void Song::Hide()
{
	_Title->SetVisible(false);
	_TrackNum->SetVisible(false);
	_ProgressBox->Hide();
	_ChordDisplayBox->Hide();
}

void Song::Init(Text *LevelFile, unsigned int commonAtlasID, unsigned short levelNum)
{
	AGKCore Converter;
	Text DataLine = "";
	Text Header = "";
	Text Index = "";

	Read *Data = new Read(*LevelFile);
	

	while (!Data->IsEOF())
	{
		DataLine = Data->Line();
		DataLine.SplitAtDelimeter(&Header, &Index, ':');

		if (Header == Text("Song Title"))
			_Title = new Text(Index.GetCString(), true);
		else if (Header == Text("Name of Chord"))
			_ChordDisplayBox = new ChordDisplayBox(Index);
		else if (Header == Text("Chord Progression"))
			_ProgressBox = new ProgressBox(Index, commonAtlasID); //unless we make this level specific art
		else if (Header == Text("Chord Sounds"))
			_Chords.push_back(new Sound(Index));
		else if (Header == "Count Off")
			_DrumStart = new Sound(Index);
		else if (Header == "Count Off Length")
			_drumLength = Converter.Val(Index);
		else if (Header == Text("Background Music"))
		{
			_BackgroundMusic = new Music(Index);
			//_BackgroundMusic2 = new Music(Index);
		}
		else if (Header == Text("Reward Music"))
			_RewardMusic = new Music(Index);

		DataLine.Delete();
	}

	_ProgressBox->Init();
	_ChordDisplayBox->Init();

	//Title Set up
	_Title->SetFontImage(Image("Text/Humbucker.png"));
	_Title->SetColor(Color(255, 255, 255));
	_Title->SetSize(5.0f);
	_Title->SetAlignment(LEFT_ALIGNED);
	_Title->SetPosition(RFTPoint(1.0f, 95.0f));

	//Track Number set up
	_TrackNum = new Text("Track ", true);
	*_TrackNum += Converter.Str(levelNum);
	_TrackNum->SetColor(Color(255, 255, 255));
	_TrackNum->SetSize(3.5f);
	_TrackNum->SetPosition(RFTPoint(1.0f, 91.5f));

	_currentChord = 0;
}

//////////////////
//////////returns length of drum intro
//////////////////
unsigned int Song::GetDrumLength()
{
	return _drumLength;
}

bool Song::GetOnNewChord()
{
	if (_ProgressBox->GetVisibleLetters() != 0)
		return false;
	
	return true;
}

///////////////////////////////
// Takes the filename of the hit sprite and checks the scoring logic to determine a correct or incorrect note
// returns note in chord if correct
// 0 if not in chord
////////////////////////////////
int Song::GetSuccessfulHit(NoteValues Value, unsigned int currentTime)
{
	int noteInChord = _ProgressBox->GetProgressionPart(Value, currentTime);

	if (noteInChord != 0)
	{
		if (GetOnNewChord())
		{
			_Chords[_currentChord++]->Play(50);
			
			if (_currentChord == _Chords.size())
				return -1;
			else
				_ChordDisplayBox->DisplayNextChord(currentTime);
		}
	}

	return noteInChord;
}

bool Song::IsBackgroundPlaying()
{
	return _BackgroundMusic->GetPlaying();
}

bool Song::IsDrumStartPlaying()
{
	return (bool)_DrumStart->GetInstances();
}

bool Song::IsRewardPlaying()
{
	return _RewardMusic->GetPlaying();
}

void Song::PauseBackground()
{
	_BackgroundMusic->Pause();
	//_BackgroundMusic2->Pause();
}

void Song::PlayBackground()
{
	if (!IsBackgroundPlaying())
		_BackgroundMusic->Play(true);
}

void Song::PlayDrumStart()
{
	_DrumStart->Play(50);
}

void Song::PlayReward()
{
	if (_BackgroundMusic->GetPlaying())
	{
		_RewardMusic->Stop();
		_RewardMusic->Play(false);
	}
}

void Song::Reset()
{
	_ProgressBox->Reset();
	_currentChord = 0;
	_BackgroundMusic->Stop();
	_ChordDisplayBox->Reset();
}

void Song::ResumeBackground()
{
	_BackgroundMusic->Resume();
}

void Song::Update(unsigned int currentTime)
{
	_ProgressBox->Update(currentTime);
	_ChordDisplayBox->Update(currentTime);
}