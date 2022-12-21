#include "Advert.h"
#include "agk.h"

//Creates empty advert
Advert::Advert(void)
{
}

//destroys advert
Advert::~Advert(void)
{
}

//creates advert
//horzPos: 0 = left, 1 = center, 2 = right
//vertPos: 0 = top, 1 = center, 2 = bottom
//offsetX: amount offset from X (only valid if horz = 0 or 2)
//offsetY: amount offset from Y (only valid if vert = 0 or 2)
//test: will create a fake add if set to true
Advert::Advert(int horzPos, int vertPos, Text AdMobID, Text InneractiveID, float offsetX, float offsetY, bool test)
{
	int t = 0;

	//needs to be set before creation
	_SetAdMobDetails(AdMobID);
	_SetInneractiveDetails(InneractiveID);

	if (test)
		t = 1;
	
	//if offsets are set, use the extended creation function, else use basic
	if (offsetX != 0.0f || offsetY != 0.0f)
		agk::CreateAdvertEx(0, horzPos, vertPos, t, offsetX, offsetY);
	else
		agk::CreateAdvert(0, horzPos, vertPos, t);
}

///////////////////////////////
// Clears a previously displayed ad
////////////////////////////
void Advert::Delete()
{
	agk::DeleteAdvert();
}

//Requests a new advert. Only needed to call when changing screens as new adverts will be sent automatically
void Advert::RequestRefresh(void)
{
	agk::RequestAdvertRefresh();
}

//Sets Ad Mob details--only supported by iOS and Android
void Advert::_SetAdMobDetails(Text ID)
{
	char newString[64] = {NULL};

	//ensure ID is no longer than 64 characters
	if (ID.GetLength() < 64)
	{
		strcpy(newString, ID.GetCString());
		agk::SetAdMobDetails(newString);
	}

	//TODO: should be an alert here if it is larger than that, not sure how to do it yet though
}

//Sets Inneractive Details--supported by iOS, Android, Windows and Mac
void Advert::_SetInneractiveDetails(Text Code)
{
	agk::SetInneractiveDetails(Code.GetCString());
}

//Sets location of advertisement
//horz values: 0 = left, 1 = center, 2 = right
//vert values: 0 = top, 1 = center, 2 = bottom
//offsetX values (only read when horz values are 0 or 2): offset amount from edge
//offsetY values (only read when vert values are 0 or 2): offset amount from edge
void Advert::SetLocation(unsigned short horz, unsigned short vert, float width)//, float offsetX, float offsetY)
{
	//if offsets are 0, use basic function, else use expanded version
	//AdvertLocationEx not available in this version, perhaps in future ones?
	//if (offsetX == 0.0f && offsetY == 0.0f)
		agk::SetAdvertLocation(horz, vert, width);
	//else
		//agk::SetAdvertLocationEx((int)horz, (int)vert, offsetX, offsetY, width);
}

//Does not work with AdMob
//Location is the top left corner of ad
//Width is desired width of ad
void Advert::SetPosition(RFTPoint Location, float width)
{
	agk::SetAdvertPosition(Location.GetX(), Location.GetY(), width);
}

//Does not work with AdMob
//x is the left side of the ad
//y is the top side of the ad
//width is the desired widh of ad
void Advert::SetPosition(float x, float y, float width)
{
	agk::SetAdvertPosition(x, y, width);
}

//Sets visibility of Ad
void Advert::SetVisible(bool isVisible)
{
	//change boolean to int for function
	if (isVisible)
		agk::SetAdvertVisible(1);
	else
		agk::SetAdvertVisible(0);
}