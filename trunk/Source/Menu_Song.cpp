#include "Menu_Song.h"
#include "AGKCore.h"
#include "HTTP.h"

#define PREVIEW_BUTTON_OFFSET RFTPoint(1.0f, 2.5f)
#define BUY_IT_BUTTON_OFFSET RFTPoint(87.5f, 3.5f)
#define SONG_NAME_OFFSET RFTPoint(7.5f, 2.0f)
#define ARTIST_NAME_OFFSET RFTPoint(7.5f, 6.0f)
#define RECORD0_OFFSET RFTPoint(75.0f, 2.0f)

MenuSong::MenuSong(int x, float yOffset, int mod, int tab, unsigned int commonAtlasID)
: Sprite(Color(242, 242, 242))
{
	this->SongNum = x;
	this->modnum = mod;
	this->tabnum = tab;
	this->SongName = new Text("", true);
	this->SongName->SetVisible(false);
	this->Artist = new Text("", true);
	this->Artist->SetVisible(false);
	_yOffset = yOffset;
	_BuyIt = new Sprite();
	_iTunesPurchaseURL = new Text("");

	for (int i = 0; i < 3; i++)
	{
		_RecordScore[i] = new Sprite();
		//_RecordScore[i]->SetVisible(false);
	}

	_preview = new Sprite();
	_PreviewSong = new Music();

	_commonAtlasID = commonAtlasID;
}

MenuSong::~MenuSong()
{
}

bool MenuSong::ClickedPreview()
{
	return _clickedPreview;
}

void MenuSong::Init()
{
	AGKCore Convert;
	//placeholder color scheme, alternating black and white to distinguish
	//Color* c;
	//if(this->SongNum %2 == 0)
		//c = new Color(140,140,140,255);
	//else
		//c = new Color(195,195,195,195);

	//this->_sprite = new  Sprite(*c);
	SetVisible(false); //initialize all sprites to be invisible until tab is clicked
	SetSize(100.0, 12.9f); //should change these values to be global so it can be edited if need be
	SetDepth(30);

	current_pos = ((GetHeight() + 0.1f)*SongNum + _yOffset);// + ((this->modnum) * 43.0f)); //calclate where sprite should be based on songnum and modnum
	//need more global way of retrieving these numbers so it is easy to change. also list is going to change size and this will mess up
	SetPosition(0, this->current_pos);
	
	//creating preview button
	/*Color* c2 = new Color(0, 0, 0);
	this->_preview = new Sprite(*c2);*/
	_preview = new Sprite(_commonAtlasID, "PreviewPlay_button.png");
	this->_preview->SetVisible(false);
	this->_preview->SetSize(5.0f);
	this->_preview->SetPosition(PREVIEW_BUTTON_OFFSET.GetX(), GetPosition().GetY() + PREVIEW_BUTTON_OFFSET.GetY());
	this->_preview->SetDepth(11);

	_BuyIt = new Sprite(_commonAtlasID, "itunes_button.png");
	_BuyIt->SetVisible(false);
	_BuyIt->SetSize(-1.0f, 5.0f);
	_BuyIt->SetPosition(RFTPoint(BUY_IT_BUTTON_OFFSET.GetX(), GetPosition().GetY() + BUY_IT_BUTTON_OFFSET.GetY()));
	_BuyIt->SetDepth(11);

	//Song Text
	Text LocalFileName = "Text/Text_";
	Text SongFooter = "";
	Text iTunesHeader = "iTunes";
	Text PreviewText = "Preview";
	LocalFileName += Convert.GetDeviceLanguage();
	LocalFileName += ".txt";
	Read *Data = new Read(LocalFileName);
	Text DataLine = "";
	Text Header = "";
	Text Index = Text ("");
	Text CorrectHeader = "Song";
	SongFooter += Convert.Str(this->tabnum);
	SongFooter += Convert.Str(this->modnum);
	SongFooter += Convert.Str(this->SongNum);
	CorrectHeader += SongFooter;
	iTunesHeader += SongFooter;
	PreviewText += SongFooter;

	while (!Data->IsEOF())
	{
		DataLine = Data->Line();
		DataLine.SplitAtDelimeter(&Header, &Index, ':');

		if (CorrectHeader == Header)
			this->SongName->SetString(Index.GetCString());
		else if (iTunesHeader == Header)
			_iTunesPurchaseURL->SetString(Index.GetCString());
		else if (PreviewText == Header)
			_PreviewSong = new Music(Index);

		DataLine.Delete();
	}

	this->SongName->SetAlignment(LEFT_ALIGNED);
	this->SongName->SetSize(3.5);
	this->SongName->SetPosition(RFTPoint(SONG_NAME_OFFSET.GetX(), GetPosition().GetY() + SONG_NAME_OFFSET.GetY()));
	this->SongName->SetDepth(11);
	SongName->SetColor(Color(0, 0, 0));

	Read *Data2 = new Read(LocalFileName);
	DataLine = "";
	Header = "";
	Index = Text ("");
	CorrectHeader = "Artist";
	CorrectHeader += Convert.Str(this->tabnum);
	CorrectHeader += Convert.Str(this->modnum);
	CorrectHeader += Convert.Str(this->SongNum);

	while (!Data2->IsEOF())
	{
		DataLine = Data2->Line();
		DataLine.SplitAtDelimeter(&Header, &Index, ':');

		if (CorrectHeader == Header)
			this->Artist->SetString(Index.GetCString());

		DataLine.Delete();
	}

	this->Artist->SetAlignment(LEFT_ALIGNED);
	this->Artist->SetSize(3.5);
	this->Artist->SetPosition(RFTPoint(ARTIST_NAME_OFFSET.GetX(), GetPosition().GetY() + ARTIST_NAME_OFFSET.GetY()));
	this->Artist->SetDepth(11);
	Artist->SetColor(Color(0, 0, 0));

	//Scores
	for (int i = 0; i < 3; i++)
	{
		_RecordScore[i] = new Sprite(_commonAtlasID, "Record.png");
		_RecordScore[i]->SetPosition(RECORD0_OFFSET.GetX() + (i*5.0f), GetPosition().GetY() + RECORD0_OFFSET.GetY());
		_RecordScore[i]->SetSize(5.0f);
		_RecordScore[i]->SetVisible(false);
		_RecordScore[i]->SetDepth(11);
	}
}

int MenuSong::GetSongNum()
{
	return (tabnum * 100) + (modnum * 10) + SongNum + 1;
}

void MenuSong::Hide()
{
	SetVisible(false);
	this->SongName->SetVisible(false);
	this->Artist->SetVisible(false);
	this->_preview->SetVisible(false);
	_BuyIt->SetVisible(false);

	for (int i = 0; i < 3; i++)
		_RecordScore[i]->SetVisible(false);
}

void MenuSong::Reveal()
{
	SetVisible(true);
	this->SongName->SetVisible(true);
	this->Artist->SetVisible(true);
	this->_preview->SetVisible(true);
	_BuyIt->SetVisible(true);

	/*for (int i = 0; i < 3; i++)
		_RecordScore[i]->SetVisible(true);*/
}

/*float MenuSong::Height()
{
	return this->_sprite->GetHeight();
} */

/*float MenuSong::Y()
{
	return this->_sprite->GetPosition().GetY();
} */

void MenuSong::Update(float y)
{
	SetPosition(0, this->current_pos - y);
	this->SongName->SetPosition(RFTPoint(SONG_NAME_OFFSET.GetX(), GetPosition().GetY() + SONG_NAME_OFFSET.GetY()));
	this->Artist->SetPosition(RFTPoint(ARTIST_NAME_OFFSET.GetX(), GetPosition().GetY() + ARTIST_NAME_OFFSET.GetY()));
	this->_preview->SetPosition(PREVIEW_BUTTON_OFFSET.GetX(), GetPosition().GetY() + PREVIEW_BUTTON_OFFSET.GetY());
	_BuyIt->SetPosition(BUY_IT_BUTTON_OFFSET.GetX(), GetPosition().GetY() + BUY_IT_BUTTON_OFFSET.GetY());
	
	for (int i = 0; i < 3; i++)
		_RecordScore[i]->SetPosition(RFTPoint(RECORD0_OFFSET.GetX()+(i*5.0f), GetPosition().GetY() + RECORD0_OFFSET.GetY()));

	//if preview button hit, play song
	//_PreviewSong->Stop(); //will stop any music playing
	//_PreviewSong->Play(false);
}

bool MenuSong::UpdateMouseClick(RFTPoint MouseLoc)
{
	if (_preview->GetHit(MouseLoc))
	{
		_clickedPreview = true;
		if (!_PreviewSong->GetPlaying())
		{
			_PreviewSong->Stop();
			_PreviewSong->Play(false);
		}

		return false;
	}
	if (_BuyIt->GetHit(MouseLoc))
	{
		HTTP InternetAccess = HTTP();

		if (!InternetAccess.GetInternetState())
			return false;

		InternetAccess.OpenBrowser(*_iTunesPurchaseURL);

		return false;
	}
	if (GetHit(MouseLoc))
	{
		_clickedPreview = false;
		return true;
	}

	_clickedPreview = false;
	return false;
}

void MenuSong::UpdateScore(unsigned short score)
{
	for (int i = 0; i < score - 1; i++)
		_RecordScore[i]->SetVisible(true);
}

void MenuSong::Stop()
{
	this->current_pos = GetPosition().GetY();
}

float MenuSong::GetPos()
{
	return this->current_pos;
}