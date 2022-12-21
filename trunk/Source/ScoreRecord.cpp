#include "ScoreRecord.h"

ScoreRecord::ScoreRecord()
: Sprite()
{

}

ScoreRecord::ScoreRecord(unsigned int commonAtlasID)
: Sprite(commonAtlasID, "Record.png")
{
}

ScoreRecord::~ScoreRecord()
{

}

void ScoreRecord::Init(RFTPoint Location)
{
	SetVisible(false);
	SetSize(5.0f);
	SetPosition(Location);
}

void ScoreRecord::Hide()
{
	Sprite::SetVisible(false);
}

void ScoreRecord::Show()
{
	Sprite::SetVisible(true);
}