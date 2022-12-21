#include "Level.h"

Level::Level(unsigned int level, unsigned int commonAtlasID)
{
	_levelID = level;

	_FailScreen = new FailScreen();
	_SuccessScreen = new SuccessScreen();
	_SpriteEmitter = new SpriteEmitter();
	_Song = new Song();
	_LivesIndicator = new LivesIndicator();
	_SettingsButton = new SettingsButton();
	_LevelTimer = new LevelTimer();
	_LevelBackground = new LevelBackground();
	_LevelAtlas = new Image();
	_PhysicsSettings = new Physics2D();
	_UpdateTimer = new AGKCore();
	_FailSound = new FailSound();
	_SuccessSound = new SuccessSound();
	//_ProgressStaff = new ProgressStaff();
	_TutorialScreen = new TutorialScreen();
	_SettingsScreen = new SettingsScreen();
	_AddTime = new Sound();
	_LoseTime = new Sound();
	_LastMousePos = new RFTPoint();
	_Pointer = new MagicPointer();
	_UIElements = new Sprite();

	//_UIElements->SetVisible(false);

	for (int i = 0; i < 3; i++)
		_Records[i] = new ScoreRecord();

	_commonAtlasID = commonAtlasID;

#if OS == PC
	_mouseDown = false;
	_DragLine = new Vector();
#endif
}

Level::~Level()
{
}

void Level::Delete()
{
	_FailScreen->Delete();
	//_PauseScreen->Delete(); //TODO: When Pause Screen is implemented
	_SuccessScreen->Delete();
	_SpriteEmitter->Delete();
	_Song->Delete();
	_LivesIndicator->Delete();
	_SettingsButton->Delete();
	_LevelTimer->Delete();
	_LevelBackground->Delete();
	_LevelAtlas->Delete();
	_PhysicsSettings->Delete();
	_FailSound->Delete();
	_SuccessSound->Delete();
	//_ProgressStaff->Delete();
	_TutorialScreen->Delete();
	_SettingsButton->Delete();
	_SettingsScreen->Delete();
	_Pointer->Delete();
	_UIElements->Delete();

	for (int i = 0; i < 3; i++)
		_Records[i]->Delete();
}

/*Level& Level::operator= (const Level &NewLevel)
{
	if (this != &NewLevel)
	{
		_ST = NewLevel._ST;
		_CDB = NewLevel._CDB;
		_Background = NewLevel._Background;
		_PB = NewLevel._PB;
		_PS = NewLevel._PS;
		_TutorialScreen = NewLevel._TutorialScreen;
	////Physics Options
		////Rest
		_Timer = NewLevel._Timer;
		_ScoreSettings = NewLevel._ScoreSettings;
		_levelID = NewLevel._levelID;
	}

	return *this;
} */

void Level::Init()
{
	//load everything
	AGKCore Converter;
	Text LevelFile = "LevelData/Level";
	Text LevelAtlasFile = "Images/Level";
	Text LevelName = "";

	LevelName += Converter.Str(_levelID);
	LevelAtlasFile += LevelName;
	LevelAtlasFile += "/Level";
	LevelAtlasFile += LevelName;
	LevelAtlasFile += Text(".png");

	_LevelAtlas = new Image(LevelAtlasFile);
	
	LevelFile += LevelName;
	LevelFile += Text(".txt");

	_PhysicsSettings->SetWallBottom(false);
	_PhysicsSettings->SetWallLeft(false);
	_PhysicsSettings->SetWallRight(false);
	_PhysicsSettings->SetWallTop(false);

	_currentSeconds = _UpdateTimer->GetMilliseconds();

	_Load(LevelFile);
	
	//init everything
	_LevelBackground->Init();
	_SpriteEmitter->Init(_notePercentages);
	_LivesIndicator->Init();
	_Song->Init(&LevelFile, _commonAtlasID, _levelID);
	//_ProgressStaff->Init();
	_LevelTimer->Init();
	_SuccessScreen->Init();
	_FailScreen->Init();
	_SettingsButton->Init();
	_SettingsScreen->Init();
	_TutorialScreen->Init();

	for (int i = 0; i < 3; i++)
		_Records[i]->Init(RFTPoint(5.0f - (i*5.0f), 15.0f));

	_justStarted = true;
}

/*void Level::SetLevelNumber(unsigned int level)
{
	_levelID = level;
} */

void Level::_Load(Text LevelFile)
{
	Read *Data = new Read(LevelFile);
	Text DataLine = "";
	Text Header = "";
	Text Index = "";
	AGKCore Convert;

	while (!Data->IsEOF())
	{
		DataLine = Data->Line();
		DataLine.SplitAtDelimeter(&Header, &Index, ':');

		/*if (Header == Text("Sharps"))
		{
			if (Index == Text("1"))
				_usesSharps = true;
			else
				_usesSharps = false;
		}
		else if (Header == Text("Flats"))
		{
			if (Index == Text("1"))
				_usesFlats = true;
			else
				_usesFlats = false;
		} */
		if (Header == "A")
			_notePercentages[A-1] = Convert.ValFloat(Index);
		else if (Header == "A#")
			_notePercentages[ASHARP-1] = Convert.ValFloat(Index);
		else if (Header == "Bf")
			_notePercentages[BFLAT-1] = Convert.ValFloat(Index);
		else if (Header == "B")
			_notePercentages[B-1] = Convert.ValFloat(Index);
		else if (Header == "B#")
			_notePercentages[BSHARP-1] = Convert.ValFloat(Index);
		else if (Header == "Cf")
			_notePercentages[CFLAT-1] = Convert.ValFloat(Index);
		else if (Header == "C")
			_notePercentages[C-1] = Convert.ValFloat(Index);
		else if (Header == "C#")
			_notePercentages[CSHARP-1] = Convert.ValFloat(Index);
		else if (Header == "Df")
			_notePercentages[DFLAT-1] = Convert.ValFloat(Index);
		else if (Header == "D")
			_notePercentages[D-1] = Convert.ValFloat(Index);
		else if (Header == "D#")
			_notePercentages[DSHARP-1] = Convert.ValFloat(Index);
		else if (Header == "Ef")
			_notePercentages[EFLAT-1] = Convert.ValFloat(Index);
		else if (Header == "E")
			_notePercentages[E-1] = Convert.ValFloat(Index);
		else if (Header == "E#")
			_notePercentages[ESHARP-1] = Convert.ValFloat(Index);
		else if (Header == "Ff")
			_notePercentages[FFLAT-1] = Convert.ValFloat(Index);
		else if (Header == "F")
			_notePercentages[F-1] = Convert.ValFloat(Index);
		else if (Header == "F#")
			_notePercentages[FSHARP-1] = Convert.ValFloat(Index);
		else if (Header == "Gf")
			_notePercentages[GFLAT-1] = Convert.ValFloat(Index);
		else if (Header == "G")
			_notePercentages[G-1] = Convert.ValFloat(Index);
		else if (Header == "G#")
			_notePercentages[GSHARP-1] = Convert.ValFloat(Index);
		else if (Header == "Af")
			_notePercentages[AFLAT-1] = Convert.ValFloat(Index);
		else if (Header == "EighthNote")
			_notePercentages[EIGHTHNOTE-1] = Convert.ValFloat(Index);
		else if (Header == "EighthRest")
			_notePercentages[EIGHTHREST-1] = Convert.ValFloat(Index);
		else if (Header == "QuarterNote")
			_notePercentages[QUARTERNOTE-1] = Convert.ValFloat(Index);
		else if (Header == "QuarterRest")
			_notePercentages[QUARTERREST-1] = Convert.ValFloat(Index);
		else if (Header == "HalfNote")
			_notePercentages[HALFNOTE-1] = Convert.ValFloat(Index);
		else if (Header == "HalfRest")
			_notePercentages[HALFREST-1] = Convert.ValFloat(Index);
		else if (Header == Text("Background Screen"))
			_LevelBackground = new LevelBackground(Index);
		else if (Header == "Background Transition")
			_LevelBackground->AddTransition(Index);
		//else if (Header == Text("Chord Progression"))
			//_ProgressStaff = new ProgressStaff(_commonAtlasID, Index);
		else if (Header == Text("Tutorial Screen"))
			_TutorialScreen = new TutorialScreen(Index, _commonAtlasID);
		////Physics Options
		else if (Header == Text("Time"))
			_LevelTimer = new LevelTimer(Index, _currentSeconds);
		////Need Tutorial Screen here

		//Delete Line, otherwise memory sink
		DataLine.Delete();
	}

	_SpriteEmitter = new SpriteEmitter(_commonAtlasID);
	_SuccessScreen = new SuccessScreen(_commonAtlasID);
	_FailScreen = new FailScreen(_commonAtlasID);
	_SettingsButton = new SettingsButton(_commonAtlasID);
	_SettingsScreen = new SettingsScreen(_commonAtlasID);
	_AddTime = new Sound("Audio/Extra time on clock.wav");
	_LoseTime = new Sound("Audio/Lose time on clock.wav");
	_UIElements = new Sprite("Images/Common/UI.png");

	_UIElements->SetVisible(true);
	_UIElements->SetSize(-1.0f, 100.00);
	
	for (int i = 0; i < 3; i++)
		_Records[i] = new ScoreRecord(_commonAtlasID);

	_playedDrums = false;
	_passedLevel = false;

	//once we have the correct assets
	_LivesIndicator = new LivesIndicator(_commonAtlasID);
	///need the file to init here

	//once we have a real tutorial screen, place above..until then...
	_TutorialScreen = new TutorialScreen("tutorial.png", _LevelAtlas->GetID());

}

//returns score, -1 if still playing, 0 for fail
ExitLevelCode Level::Update()
{
	_currentSeconds = _UpdateTimer->GetMilliseconds();

	if (_justStarted)
	{
		if (!_TutorialScreen->GetVisible())
		{
			_TutorialScreen->Show();
			return STILLPLAYING;
		}
		else
		{
			if (_Pointer->GetPressed())
			{
				if (_TutorialScreen->GetHit(_Pointer->GetPosition()))
				{
					_TutorialScreen->Hide();
					_LevelBackground->HideTransition();
					_Song->PlayDrumStart();
					_drumStartTime = _currentSeconds;
				}
				else
					return STILLPLAYING;
			}
			else
				return STILLPLAYING;
		}
	}

	_PauseHandler();
		
	if (!_SongHandler())
		return STILLPLAYING;

	_UpdateSpriteEmitter();
	_UpdateLevelTimer();

	return _UpdateUI();
}

bool Level::_HasMouseMoved(RFTPoint CurrentPos)
{
	//if last pos +/- fuzzy value still contains current position, it has not moved
	if (!(_LastMousePos->GetX() - 2.5f <= CurrentPos.GetX() && _LastMousePos->GetX() + 2.5 >= CurrentPos.GetX()))
		return true;

	if (!(_LastMousePos->GetY() - 2.5f <= CurrentPos.GetY() && _LastMousePos->GetY() + 2.5 >= CurrentPos.GetY()))
		return true;
	
	return false;
}

void Level::_PauseGame()
{
	_LevelTimer->Pause();
	_SpriteEmitter->Pause();
	_Song->PauseBackground();
	_LevelBackground->ShowTransition();
}

void Level::_PauseHandler()
{
#if PLATFORM != PC
	AGKCore PauseTester;

	if (PauseTester.GetResumed() && !_justStarted)
	{
		_SettingsScreen->Show();
		_PauseGame();
	}
#endif
	_justStarted = false;

	if (_FailScreen->GetVisible())
	{
		if (_FailScreen->Update())
			_Restart(_currentSeconds);
	}

}

void Level::_ResumeGame()
{
	_LevelTimer->Resume(_currentSeconds);
	_SpriteEmitter->Resume();
	_Song->ResumeBackground();
	_LevelBackground->HideTransition();
}

void Level::_Restart(unsigned int currentTime)
{
	_LivesIndicator->Reset();
	_LevelTimer->Restart(currentTime);
	_FailScreen->Hide();
	_SuccessScreen->Hide();
	_SettingsScreen->Hide();
	_SpriteEmitter->Reset();
	_Song->Reset();
	//_ProgressStaff->Reset();
	_playedDrums = false;
	_justStarted = true;
}

void Level::_SlashHandler()
{
	RFTPoint PointerPos = _Pointer->GetPosition();

	_Pointer->Update();

	if (_Pointer->GetState())
	{
		if (!(*_LastMousePos == RFTPoint()) && _HasMouseMoved(PointerPos) && _SpriteEmitter->CheckForHits(PointerPos))
		{
			unsigned int numberOfHits = _SpriteEmitter->GetHitCount();

			for (unsigned int i = 0; i < numberOfHits; i++) //starts at 1 because there are no id's equal to zero
			{
				NoteValues NoteInChord = _SpriteEmitter->GetHitValue(i);
				int noteInChord = 0;

				if (NoteInChord <= AFLAT)
					noteInChord = _Song->GetSuccessfulHit(NoteInChord, _currentSeconds);

				if (noteInChord != 0)
				{
					//play success sound;
					_SuccessSound->Play(50);
					//if chord is complete, display on bottom right part of screen
					if (_Song->GetOnNewChord())
					{
						//_ProgressStaff->ShowChord();

						if (noteInChord == -1)
						{
							_SuccessScreen->Show();//show success screen						
							_PauseGame();
							_Song->PlayReward();
							_passedLevel = true;

							int secondsLeft = _LevelTimer->GetSecondsLeft();
							int records = 0;

							if (secondsLeft > 24)
								_Records[records++]->Show();
							if (secondsLeft > 16)
								_Records[records++]->Show();
							if (secondsLeft > 8)
								_Records[records++]->Show();
						}
					}
				}
				else
				{
					if (NoteInChord <= AFLAT)
					{
						//play fail sound;
						_FailSound->Play(50);
						//lose life
						if (_LivesIndicator->LoseLife())
						{
							_FailScreen->Show();
							_PauseGame();
						}
					}
					else
					{//clicked on note or rest
						switch (NoteInChord)
						{
						case EIGHTHNOTE:
							_LevelTimer->RemoveTime(30 * SECONDS / 8);
							_LoseTime->Play(50);
							break;
						case EIGHTHREST:
							_LevelTimer->AddTime(30 * SECONDS / 8);
							_AddTime->Play(50);
							break;
						case QUARTERNOTE:
							_LevelTimer->RemoveTime(30 * SECONDS / 4);
							_LoseTime->Play(50);
							break;
						case QUARTERREST:
							_LevelTimer->AddTime(30 * SECONDS / 4);
							_AddTime->Play(50);
							break;
						case HALFNOTE:
							_LevelTimer->RemoveTime(30 * SECONDS / 2);
							_LoseTime->Play(50);
							break;
						case HALFREST:
							_LevelTimer->AddTime(30 * SECONDS / 2);
							_AddTime->Play(50);
							break;
						}
					}
				}
			}

			_SpriteEmitter->DeleteHits();
		}
	}
	
	_LastMousePos = new RFTPoint(PointerPos);
}

//returns true if sprite emitter should proceed
bool Level::_SongHandler()
{
	unsigned int elapsed = _currentSeconds - _drumStartTime;

	if (_Song->GetDrumLength() > elapsed + 10)
		return false;

	/*if (!_Song->IsBackgroundPlaying() && !_Song->IsRewardPlaying() && !_passedLevel)
	{
		_Song->PlayBackground();
		return true;
	} */

	if (!_passedLevel)
		_Song->PlayBackground();
	else
		_Song->PlayReward();

	return true;
}

void Level::_UpdateLevelTimer()
{
	//Check Time
	if (_currentSeconds - _LevelTimer->GetLastUpdateTime() > 0.5 * SECONDS)
	{
		bool timeOut = _LevelTimer->Update(_currentSeconds);

		if (timeOut)
		{
			_SpriteEmitter->Pause();
			_FailScreen->Show();
		}
	}

}

void Level::_UpdateSpriteEmitter()
{
	//Update Sprite Emitter
	//eventually we want this set up by Ian's textfile eventually
	if ((_currentSeconds - _SpriteEmitter->GetLastUpdateTime()) > 352)
	{
		_SpriteEmitter->Update(_currentSeconds);
	}
}

ExitLevelCode Level::_UpdateUI()
{
	//Update UI
	if ((_currentSeconds - _SettingsButton->GetLastUpdateTime()) > 10)
	{
		if (_SettingsButton->Update(_currentSeconds))
		{
			_SettingsScreen->Show();
			/*_LevelTimer->Pause();
			_SpriteEmitter->Pause();
			_Song->PauseBackground();*/
			_PauseGame();
		}

	}

	if (_SettingsScreen->GetVisible())
	{
		if (_SettingsScreen->Update())
			_Restart(_currentSeconds);

		//Remove Setting Screen if clicked
		if (_Pointer->GetPressed())
		{
			if (_SettingsScreen->GetHit(_Pointer->GetPosition()) || _SettingsButton->GetPressed())
			{
				_SettingsScreen->Hide();
				_ResumeGame();
			}
		}
	}

	//if success scree is visible, check for button presses
	if (_SuccessScreen->GetVisible())
	{
		short score = 0;
		RFTPoint MouseLoc = RFTPoint(-1.0f, 0.0f);

		for (int i = 0; i < 3; i++)
		{
			if (_Records[i]->GetVisible())
				score++;
		}

		if (_Pointer->GetPressed())
			MouseLoc = _Pointer->GetPosition();

		int updateStatus = _SuccessScreen->Update(MouseLoc);

		if (updateStatus == 1) //facebook like
		{
		}
		else if (updateStatus == 2) //Twitter?
		{
		}
		if (updateStatus == 3) //Next Level
		{
			return (ExitLevelCode)(score + 4); //4 = Next Song
		}
		else if (updateStatus == 4) //Main Menu
		{
			_LevelBackground->SetVisible(false);
			_LivesIndicator->Hide();
			_LevelTimer->Hide();
			//_ProgressStaff->Hide();
			for (int i = 0; i < 3; i++)
				_Records[i]->SetVisible(false);
			_UIElements->SetVisible(false);
			_Song->Hide();
			return (ExitLevelCode)(score); //0 = Main Menu
		}
	}

	_Song->Update(_currentSeconds);

	_SlashHandler();

	return STILLPLAYING;
}