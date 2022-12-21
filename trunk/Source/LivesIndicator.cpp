#include "LivesIndicator.h"

LivesIndicator::LivesIndicator()
{
	///////TODO: Need Guitar and string images
	for (int i = 0; i < 6; i++)
	{
		////////////Just for now, until we get real assets
		_Strings[i] = new Sprite(Color(255, 0, 0));
		_Strings[i]->SetVisible(false);
	}

	//_Guitar = new Sprite("");
}

LivesIndicator::LivesIndicator(unsigned int commonAtlasID)
{
	for (int i = 0; i < 6; i++)
	{
		//replace with correct string name
		_Strings[i] = new Sprite(commonAtlasID, "guitar.png");
	}
	
	//_Guitar = new Sprite("");
}

LivesIndicator::~LivesIndicator()
{

}

void LivesIndicator::Init()
{
	for (int i = 0; i < 6; i++)
	{
		//remove set size when I have the correct assets
		_Strings[i]->SetSize(5.0f);
		_Strings[i]->SetPosition(RFTPoint(0.5f + (i * 5.5f), 0.5f));
		_Strings[i]->SetVisible(true);
	}
}

void LivesIndicator::Delete()
{
	for (int i = 0; i < 6; i++)
		_Strings[i]->Delete();

	//_Guitar->Delete();
}

void LivesIndicator::Hide()
{
	for (int i = 0; i < 6; i++)
		_Strings[i]->SetVisible(false);
}

///////////////////////////////////////
// Removes a string each time it's called
// returns true if no strings left
//////////////////////////////////////
bool LivesIndicator::LoseLife()
{
	for (int i = 5; i >= 0; i--)
	{
		if (_Strings[i]->GetVisible())
		{
			_Strings[i]->SetVisible(false);

			if (i != 0)
				return false;
			
			return true;
		}
	}

	return true;
}

void LivesIndicator::Reset()
{
	for (int i = 0; i < 6; i++)
		_Strings[i]->SetVisible(true);
}