#include "Menu_Tab.h"
#include "AGKCore.h"

Tab::Tab()
{}

Tab::Tab(int tab, float y, unsigned int commonAtlasID)
: Sprite(commonAtlasID, "RedTab.png")
{
	_TabText = new Text("", true);
	_TabText->SetVisible(false);
	tab_num = tab;
	//num_modules = modules;
	_titlebar_height = y + 0.666667f;
	_commonAtlasID = commonAtlasID;
	_moduleNumber = 0;
	_Selected = new Sprite();
}

Tab::~Tab()
{
}

void Tab::Init()
{
	AGKCore Convert;
	//placeholder colors to differentiate tabs
	//Color* c = new Color(175,0,0,255);
	/*switch (GetTabNum())
	{
	case 0:
		c->SetBlue(10);
		break;
	case 1:
		c->SetGreen(10);
		break;
	case 2:
		c->SetRed(10);
		break;
	case 3:
		c->SetGreen(30);
		break;
	case 4:
		c->SetBlue(30);
		break;
	}*/

	//create sprite for tab
	//_tabsprite = new  Sprite(*c);
	SetSize(19.75, 10.0); //creating slivers by setting the width 0.1% smaller
	SetPosition((GetWidth() + 0.3125f)*tab_num, _titlebar_height); //adding 0.1 to create that sliver
	SetDepth(10);

	_Selected = new Sprite(_commonAtlasID, "DarkTab.png");
	_Selected->SetSize(19.75f, 10.0f);
	_Selected->SetPosition((GetWidth() + 0.3125f) * tab_num, _titlebar_height);
	_Selected->SetDepth(10);
	_Selected->SetVisible(false);

	//Tab Text
	Text LocalFileName = "Text/Text_";

	LocalFileName += Convert.GetDeviceLanguage();
	LocalFileName += ".txt";
	Read *Data = new Read(LocalFileName);
	Text DataLine = "";
	Text Header = "";
	Text Index = Text ("");
	Text CorrectHeader = "Tab";
	unsigned short modules = 0;
	
	CorrectHeader += Convert.Str(tab_num + 1);
	Text ModuleCountHeader = CorrectHeader;
	ModuleCountHeader += "ModuleCount";

	while (!Data->IsEOF())
	{
		DataLine = Data->Line();
		DataLine.SplitAtDelimeter(&Header, &Index, ':');
		
		if (CorrectHeader == Header)
			_TabText->SetString(Index.GetCString());
		else if (ModuleCountHeader == Header)
			modules = Convert.Val(Index);

		DataLine.Delete();
	}
		
	_TabText->SetAlignment(CENTER_ALIGNED);
	_TabText->SetSize(5.0f);
	_TabText->SetPosition(RFTPoint(((tab_num + 1) * 20.0f) - 10.0f, _titlebar_height + 2.5f)); //had to make this hard coded, as artist combined the two pieces of art that we had separated
	_TabText->SetVisible(true);

	//create song list
	for (int i = 0; i < modules; i++)
		_Module.push_back(new Module(tab_num, i, _commonAtlasID)); //have to pass in offest values

	float heightSubTotal = GetHeight() + _titlebar_height; 

	for (unsigned int i = 0; i < _Module.size(); i++)
	{
		_Module[i]->Init(heightSubTotal);
		heightSubTotal += _Module[i]->GetModuleHeight();
	}
}

int Tab::GetTabNum()
{
	return tab_num;
}

/*Sprite* Tab::TabSprite()
{
	return _tabsprite;
} */

/*void Tab::CreateModules(int tabNum)
{
	for(int i=0; i<num_modules; i++)
		_Module.push_back (new Module(tabNum, i, 3, GetHeight() + _titlebar_height )); //have to pass in offest values
} */

void Tab::Delete()
{
	Sprite::Delete();
	_TabText->Delete();
}

void Tab::Update(float y)
{
	//if the bottom of the last module is at the bottom of the screen, don't allow to scroll up
	if((_Module.at(_Module.size() - 1)->Bottom() - y) <= 100.0f)
		y = _Module.at(_Module.size() - 1)->Bottom() - 100.0f;

	//if the top of the first module is at the starting position, do not allow to scroll down
	if(_Module[0]->GetPos() - y > _titlebar_height + GetHeight())
		y = _Module[0]->GetPos() - (_titlebar_height + GetHeight());

	//Update position of all modules
	for(unsigned int i=0; i<_Module.size(); i++)
		_Module[i]->Update(y);
}

bool Tab::UpdateMouseClick(RFTPoint MouseLoc)
{
	for (unsigned int i = 0; i < _Module.size(); i++)
	{
		if (_Module[i]->CheckForHits(MouseLoc))
		{
			_moduleNumber = i;
			return true;
		}
	}

	return false;
}

int Tab::GetSongSelected()
{
	return _Module[_moduleNumber]->GetSongNumber();
}

bool Tab::ClickedOnPreview()
{
	return _Module[_moduleNumber]->ClickedPreview();
}

void Tab::Stop()
{
	for(unsigned int i=0; i<_Module.size(); i++)
		_Module[i]->Stop();
}

void Tab::HideList()
{
	for(unsigned int i=0; i<_Module.size(); i++)
		_Module[i]->Hide();

	SetVisible(true);
	_Selected->SetVisible(false);
}

void Tab::RevealList()
{
	SetVisible(false);
	_Selected->SetVisible(true);

	for(unsigned int i=0; i<_Module.size(); i++)
		_Module[i]->Reveal();
}

/*float Tab::Height()
{
	return tabsprite->GetHeight();
} */

float Tab::Bottom()//not sure if needed
{
	//float x = 0.0f;
	//for(unsigned int i=0; i<_Module.size(); i++)
		//x += _Module[i]->Bottom(); //not bottom, height of module

	//Get Last Module, and return the bottom of it
	return _Module.at(_Module.size() - 1)->Bottom();// GetPos() + _list.at(_list.size() - 1)->GetHeight();)

	//return x;
}

void Tab::UpdateScores(std::vector<int> songIndexes, std::vector<unsigned short> scores)
{
	for (unsigned int i = 0; i < _Module.size(); i++)
		_Module[i]->UpdateScores(songIndexes, scores);
}

void Tab::Hide()
{
	for (unsigned int i = 0; i < _Module.size(); i++)
		_Module[i]->Hide();

	_TabText->SetVisible(false);

	SetVisible(false);
	_Selected->SetVisible(false);
}

void Tab::Show()
{
	_TabText->SetVisible(true);

	SetVisible(true);
}