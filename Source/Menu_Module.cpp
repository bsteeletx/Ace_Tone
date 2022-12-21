#include "Menu_Module.h"
#include "AGKCore.h"

Module::Module(int tabnum, int modnum, unsigned int commonAtlasID)
: Sprite(Text ("/Images/Common/MenuModule.png"))
{
	_commonAtlasID = commonAtlasID;
	SetVisible(false);
	_height = 0;
	_tab_num = tabnum;
	_modnum = modnum;
	//_numsongs = numsongs;
	this->ModText = new Text("", true);
	this->ModText->SetVisible(false);
	_hitSong = 0;
	_clickedPreview = false;
}

Module::~Module()
{
}

void Module::Init(float offsetY)
{
	AGKCore Convert;
	float songOffset = 0.0f;

	current_pos = offsetY + 0.5f;// + (_modnum * 46); //position of title //TODO: Remove hard number 46
	SetSize(100.0f);
	SetPosition(0, current_pos);
	SetDepth(11);
	SetVisible(false);

	songOffset = current_pos + GetHeight();

	Text t = "Module ";
	t += Convert.Str(this->_modnum+1);
	this->ModText->SetString(t.GetCString());
	this->ModText->SetAlignment(CENTER_ALIGNED);
	this->ModText->SetSize(4.0f);
	this->ModText->SetPosition(RFTPoint(10.0f, GetPosition().GetY() + 0.5f));
	this->ModText->SetDepth(11);

	//Tab Text
	Text LocalFileName = "Text/Text_";

	LocalFileName += Convert.GetDeviceLanguage();
	LocalFileName += ".txt";
	Read *Data = new Read(LocalFileName);
	Text DataLine = "";
	Text Header = "";
	Text Index = Text("");
	Text CorrectHeader = "Tab";
		
	CorrectHeader += Convert.Str(_tab_num + 1);
	CorrectHeader += "Module";
	CorrectHeader += Convert.Str(_modnum + 1);
	CorrectHeader += "SongCount";
	unsigned int songCount = 0;

	while (!Data->IsEOF())
	{
		DataLine = Data->Line();
		DataLine.SplitAtDelimeter(&Header, &Index, ':');

		if (CorrectHeader == Header)
		{
			songCount = Convert.Val(Index);
			DataLine.Delete();
			break;
		}
		
		DataLine.Delete();
	}

	for (unsigned int i = 0; i < songCount; i++)
		_list.push_back(new MenuSong(i, songOffset, _modnum, _tab_num, _commonAtlasID));

	for (unsigned int i = 0; i < _list.size(); i++)
	{
		_list[i]->Init();
		_height += _list[i]->GetHeight(); //add up and store the total height of all songs in list
	}
}

void Module::Update(float y)
{
	//update position of module title
	if (y == 0.0f)
		return;

	SetPosition(0, current_pos - y);
	this->ModText->SetPosition(RFTPoint(10.0f, GetPosition().GetY() + 0.5f));

	//Update position of each song in list
	for(unsigned int i =0; i < _list.size(); i++)
		_list[i]->Update(y);
}

void Module::Stop() //stop updates current_position for update function
{
	for(unsigned int i =0; i<_list.size(); i++)
		_list[i]->Stop();
	current_pos = GetPosition().GetY();
}

/*float Module::Title_Pos() //needed for retrieving private member modtitle position
{
	return _modtitle->GetPosition().GetY();
} */

void Module::Hide()
{
	//hide all the songs
	for(unsigned int i=0; i<_list.size(); i++)
	{
		_list[i]->Hide();
	}
	//hide module title sprite
	SetVisible(false);
	this->ModText->SetVisible(false);
}

void Module::Reveal()
{
	//reveal all songs
	for(unsigned int i=0; i<_list.size(); i++)
	{
		_list[i]->Reveal();
	}
	//reveal title menu sprite
	SetVisible(true);
	this->ModText->SetVisible(true);
}

float Module::Bottom()
{
	return _list.at(_list.size()-1)->GetPos() + _list.at(_list.size() - 1)->GetHeight();
}

bool Module::CheckForHits(RFTPoint MouseLoc)
{
	for (unsigned int i = 0; i < _list.size(); i++)
	{
		if (_list[i]->UpdateMouseClick(MouseLoc))
		{
			_hitSong = _list[i]->GetSongNum();
			_clickedPreview = false;
			return true;
		}
		else if (_list[i]->ClickedPreview())
		{
			_hitSong = _list[i]->GetSongNum();
			_clickedPreview = true;
			return true;
		}
	}

	_clickedPreview = false;
	return false;
}

bool Module::ClickedPreview()
{
	return _clickedPreview;
}

unsigned int Module::GetSongNumber()
{
	return _hitSong;
}

float Module::GetModuleHeight()
{
	return _height + GetHeight();
}

float Module::GetPos()
{
	return current_pos;
}

void Module::UpdateScores(std::vector<int> songIndexes, std::vector<unsigned short> songScores)
{
	for (unsigned int i = 0; i < _list.size(); i++)
	{
		for (unsigned int j = 0; j < songIndexes.size(); j++)
		{
			if (_list[i]->GetSongNum() == songIndexes[j])
				_list[i]->UpdateScore(songScores[j]);
		}
	}
}