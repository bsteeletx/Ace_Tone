#include "DifficultyToggle.h"
#include "Globals.h"


DifficultyToggle::DifficultyToggle()
{
}


DifficultyToggle::~DifficultyToggle()
{
}

DifficultyToggle::DifficultyToggle(unsigned int commonAtlasID)
{
	for (int i = 0; i < 3; i++)
	{
		_DifficultyButtons[i] = new VirtualButton(RFTPoint(30.0f + (i*5.1f), 15.0f), 5.0f);
		_DifficultySpriteUp[i] = new Sprite(Color(128, 128, 128)); //replace with sprites
		_DifficultySpriteDown[i] = new Sprite(Color(192, 192, 192));

		_DifficultyButtons[i]->SetVisible(false);
		_DifficultySpriteDown[i]->SetVisible(false);
		_DifficultySpriteUp[i]->SetVisible(false);
	}

	_difficulty = EASY;
}

void DifficultyToggle::Delete()
{
	for (int i = 0; i < 3; i++)
	{
		_DifficultyButtons[i]->Delete();
		_DifficultySpriteDown[i]->Delete();
		_DifficultySpriteUp[i]->Delete();
	}
}

void DifficultyToggle::Hide()
{
	for (int i = 0; i < 3; i++)
	{
		_DifficultyButtons[i]->SetVisible(false);
		_DifficultyButtons[i]->SetActive(false);
	}
}

void DifficultyToggle::Init()
{
	for (int i = 0; i < 3; i++)
	{
		_DifficultyButtons[i]->SetImageUp(*_DifficultySpriteUp[i]);
		_DifficultyButtons[i]->SetImageDown(*_DifficultySpriteDown[i]);
	}
}

void DifficultyToggle::Show()
{
	for (int i = 0; i < 3; i++)
	{
		_DifficultyButtons[i]->SetVisible(true);
		_DifficultyButtons[i]->SetActive(true);
	}
}

void DifficultyToggle::Update()
{
	for (int i = 0; i < 3; i++)
	{
		if (_DifficultyButtons[i]->GetPressed())
		{
			for (int j = 0; j < 3; j++)
			{
				if (i != j)
					_DifficultyButtons[j]->SetImageUp(*_DifficultySpriteUp[j]);
				else
					_DifficultyButtons[j]->SetImageUp(*_DifficultySpriteDown[j]);
			}

			_difficulty = (DIFFICULTY)i;

			break;
		}
	}
}