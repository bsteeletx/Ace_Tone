#include "Sprite.h"
#include "agk.h"

Sprite::~Sprite(void)
{
	//if (GetExists())
		//agk::DeleteSprite(_spriteNumber);
}

Sprite::Sprite(void)
{
	_spriteNumber = 0;
}

Sprite::Sprite(Color SpriteColor)
{
	_spriteNumber = agk::CreateSprite(0);
	SetColor(SpriteColor);
}

Sprite::Sprite(Text Filename)
	: Image(Filename)
{
	_Create();
}

/*Sprite::Sprite(Text Filename, bool blackIsAlpha, unsigned int assignedSpriteNumber)
	: Image(Filename, blackIsAlpha)
{
	_Create(assignedSpriteNumber);
} */

/*Sprite::Sprite(unsigned int assignedImageNumber, Text Filename, bool blackIsAlpha, unsigned int assignedSpriteNumber)
	: Image(assignedImageNumber, Filename, blackIsAlpha)
{
	_Create(assignedSpriteNumber);
}*/

Sprite::Sprite(unsigned int parentImage, Text SubImageFilename)
	: Image(parentImage, SubImageFilename)
{
	_Create();
}

/*Sprite::Sprite(unsigned int assignedImageNumber, unsigned int parentImage, Text SubImageFilename, unsigned int assignedSpriteNumber)
	: Image(assignedImageNumber, parentImage, SubImageFilename)
{
	_Create(assignedSpriteNumber);
}*/

Sprite::Sprite(Read FileToInit, Text PathToParent)
	: Image(FileToInit, PathToParent)
{
	_Create();

	FileToInit.ReOpen();

	while(!FileToInit.IsEOF())
	{
		Text Line = FileToInit.Line();
		Text Start;
		Text End;

		Line.SplitAtDelimeter(&Start, &End, ':');

		if (Start == Text("Size"))
		{
			SetSize(agk::ValFloat(End.GetCString()));
			break;
		}
	}

	FileToInit.Close();
}

Sprite::Sprite(unsigned int imageID, RFTPoint Begin, RFTPoint End)
: Image(imageID, Begin, End)
{
	_Create();
}

Sprite& Sprite::operator= (const Sprite &OtherSprite)
{	
	if (this != &OtherSprite)
	{
		this->_spriteNumber = OtherSprite._spriteNumber;
	}

	return *this;
} 

Sprite& Sprite::operator<< (const Image& Object)
{
	Image TempImage(Object);

	if (GetExists())
		agk::DeleteSprite(_spriteNumber);

	_spriteNumber = agk::CreateSprite(TempImage.GetID());
	
	return *this;
}

Sprite* Sprite::CopySection(RFTPoint Begin, RFTPoint End)
{
	Sprite *NewSprite = new Sprite(this->_imageNumber, Begin, End);

	return NewSprite;
}

void Sprite::Delete()
{
	agk::DeleteSprite(_spriteNumber);
}

///////////////////////
// Immediately draws the sprite to the backbuffer at its current position, size, and rotation. 
// This is useful if you want to setup a scene for GetImage to capture. 
// Remember to use ClearScreen to clear any of your own drawing before calling Sync or Render for the actual frame otherwise your drawing may appear twice in the final render.
///////////////////////
void Sprite::Draw()
{
	agk::DrawSprite(_spriteNumber);
}

void Sprite::FixToScreen(bool screen)
{
	if (screen)
		agk::FixSpriteToScreen(_spriteNumber, 1);
	else
		agk::FixSpriteToScreen(_spriteNumber, 0);
}

bool Sprite::GetActive(void)
{
	if (agk::GetSpriteActive(_spriteNumber) == 1)
		return true;
	else
		return false;
}

short Sprite::GetColorAlpha(void)
{
	return (short) agk::GetSpriteColorAlpha(_spriteNumber);
}

float Sprite::GetAngle(void)
{
	return agk::GetSpriteAngle(_spriteNumber);
}

float Sprite::GetAngleInRad(void)
{
	return agk::GetSpriteAngleRad(_spriteNumber);
}

short Sprite::GetColorBlue(void)
{
	return (short) agk::GetSpriteColorBlue(_spriteNumber);
}

RFTPoint Sprite::GetPosition(void)
{
	return RFTPoint(_GetX(), _GetY());
}

bool Sprite::GetCollision(Sprite TestSprite)
{
	if (agk::GetSpriteCollision(_spriteNumber, TestSprite.GetSpriteNumber()) == 1)
		return true;
	else
		return false;
}

bool Sprite::GetCollision(unsigned int testSpriteNumber)
{
	if (agk::GetSpriteCollision(_spriteNumber, testSpriteNumber) == 1)
		return true;
	else
		return false;
}

int Sprite::GetCollisionGroup(void)
{
	return agk::GetSpriteGroup(_spriteNumber);
}

void Sprite::SetCollisionGroup(int group)
{
	agk::SetSpriteGroup(_spriteNumber, group);
}

short Sprite::GetDepth(void)
{
	return (short) agk::GetSpriteDepth(_spriteNumber);
}

float Sprite::GetDistanceFrom(Sprite TestSprite)
{
	return agk::GetSpriteDistance(_spriteNumber, TestSprite.GetSpriteNumber());
}

float Sprite::GetDistancePoint1X(void)
{
	return agk::GetSpriteDistancePoint1X();
}

float Sprite::GetDistancePoint1Y(void)
{
	return agk::GetSpriteDistancePoint1Y();
}

float Sprite::GetDistancePoint2X(void)
{
	return agk::GetSpriteDistancePoint2X();
}

float Sprite::GetDistancePoint2Y(void)
{
	return agk::GetSpriteDistancePoint2Y();
}

bool Sprite::GetExists(void)
{
	if (agk::GetSpriteExists(_spriteNumber) == 1)
		return true;
	else
		return false;
}

short Sprite::GetColorGreen(void)
{
	return (short) agk::GetSpriteColorGreen(_spriteNumber);
}

int Sprite::GetGroup(void)
{
	return agk::GetSpriteGroup(_spriteNumber);
}

int Sprite::GetHitCategory(int categoryTest, RFTPoint Location)
{
	return agk::GetSpriteHitCategory(categoryTest, Location.GetX(), Location.GetY());
}

int Sprite::GetHitGroup(RFTPoint Location)
{
	return agk::GetSpriteHitGroup(GetGroup(), Location.GetX(), Location.GetY());
}

float Sprite::GetHeight(void)
{
	return agk::GetSpriteHeight(_spriteNumber);
}

bool Sprite::GetHit(RFTPoint Location)
{
	if (agk::GetSpriteHitTest(_spriteNumber, Location.GetX(), Location.GetY()) == 1)
		return true;
	else
		return false;
}

unsigned int Sprite::GetImageID()
{
	return agk::GetSpriteImageID(_spriteNumber);
}

bool Sprite::GetInBox(RFTPoint TopLeft, RFTPoint BottomRight)
{
	if (agk::GetSpriteInBox(_spriteNumber, TopLeft.GetX(), TopLeft.GetY(), BottomRight.GetX(), BottomRight.GetY()) == 1)
		return true;
	else
		return false;
}

bool Sprite::GetInCircle(RFTPoint CenterOfCircle, float radius)
{
	if (agk::GetSpriteInCircle(_spriteNumber, CenterOfCircle.GetX(), CenterOfCircle.GetY(), radius) == 1)
		return true;
	else
		return false;
}

RFTPoint Sprite::GetPositionByOffset(void)
{
	return RFTPoint(_GetOffsetX(), _GetOffsetY());
}

float Sprite::_GetOffsetX(void)
{
	return agk::GetSpriteXByOffset(_spriteNumber);
}

float Sprite::_GetOffsetY(void)
{
	return agk::GetSpriteYByOffset(_spriteNumber);
}

int Sprite::GetPixelFromX(float x)
{
	return agk::GetSpritePixelFromX(_spriteNumber, x);
}

int Sprite::GetPixelFromY(float y)
{
	return agk::GetSpritePixelFromY(_spriteNumber, y);
}

short Sprite::GetColorRed(void)
{
	return (short) agk::GetSpriteColorRed(_spriteNumber);
}

unsigned int Sprite::GetSpriteNumber(void)
{
	return _spriteNumber;
}

bool Sprite::GetVisible(void)
{
	if (agk::GetSpriteVisible(_spriteNumber) == 1)
		return true;
	else
		return false;
}

float Sprite::GetWidth(void)
{
	return agk::GetSpriteWidth(_spriteNumber);
}

float Sprite::_GetX(void)
{
	return agk::GetSpriteX(_spriteNumber);
}

float Sprite::GetXFromPixel(int x)
{
	return agk::GetSpriteXFromPixel(_spriteNumber, x);
}

float Sprite::_GetY(void)
{
	return agk::GetSpriteY(_spriteNumber);
}

float Sprite::GetYFromPixel(int y)
{
	return agk::GetSpriteYFromPixel(_spriteNumber, y);
}

void Sprite::Move(RFTPoint Speed)
{
	MoveX(Speed.GetX());
	MoveY(Speed.GetY());
}

void Sprite::MoveX(float x)
{
	agk::SetSpriteX(_spriteNumber, _GetX() + x);
}

void Sprite::MoveY(float y)
{
	agk::SetSpriteY(_spriteNumber, _GetY() + y);
}

void Sprite::ResetUV(void)
{
	agk::ResetSpriteUV(_spriteNumber);
}

void Sprite::SetActive(bool isActive)
{
	agk::SetSpriteActive(_spriteNumber, isActive);
}

void Sprite::SetColorAlpha(short alpha)
{
	_SpriteColor.SetAlpha(alpha);
	agk::SetSpriteColorAlpha(_spriteNumber, _SpriteColor.GetAlpha());
}

void Sprite::SetAngle(float angle)
{
	agk::SetSpriteAngle(_spriteNumber, angle);
}

void Sprite::SetAngleInRad(float rad)
{
	agk::SetSpriteAngleRad(_spriteNumber, rad);
}

void Sprite::SetColorBlue(short blue)
{
	_SpriteColor.SetBlue(blue);
	agk::SetSpriteColorBlue(_spriteNumber, _SpriteColor.GetBlue());
}

void Sprite::SetColor(Color Values)
{

	agk::SetSpriteColor(_spriteNumber, Values.GetRed(), Values.GetGreen(), Values.GetBlue(), Values.GetAlpha());
}

void Sprite::SetDepth(short depth)
{
	if (_Depth(depth))
		agk::SetSpriteDepth(_spriteNumber, depth);
}

void Sprite::SetFlip(bool horizontal, bool vertical)
{
	agk::SetSpriteFlip(_spriteNumber, horizontal, vertical);
}

void Sprite::SetColorGreen(short green)
{
	if (_ColorChannel(green))
		agk::SetSpriteColorGreen(_spriteNumber, green);
}

void Sprite::SetImage(Image newImage, bool reshape)
{
	if (reshape)
		agk::SetSpriteImage(_spriteNumber, newImage.GetID(), 1);
	else
		agk::SetSpriteImage(_spriteNumber, newImage.GetID());
}

void Sprite::SetOffset(RFTPoint Offset)
{
	agk::SetSpriteOffset(_spriteNumber, Offset.GetX(), Offset.GetY());
} 

void Sprite::SetPosition(float x, float y)
{
	SetPosition(RFTPoint(x, y));
}

void Sprite::SetPosition(RFTPoint Location)
{
	agk::SetSpritePosition(_spriteNumber, Location.GetX(), Location.GetY());
}

/*void Sprite::SetPositionByOffSet(float x, float y)
{
	OffSetAmount = Point(x, y);
	SetPositionByOffSet(OffSetAmount);
} */

void Sprite::SetPositionByOffset(RFTPoint Location)
{
	agk::SetSpritePositionByOffset(_spriteNumber, Location.GetX(), Location.GetY());
}

void Sprite::SetColorRed(short red)
{
	if (_ColorChannel(red))
		agk::SetSpriteColorRed(_spriteNumber, red);
}

void Sprite::SetScale(float x, float y)
{
	agk::SetSpriteScale(_spriteNumber, x, y);
}

void Sprite::SetScaleByOffset(RFTPoint Offset)
{
	agk::SetSpriteScaleByOffset(_spriteNumber, Offset.GetX(), Offset.GetY());
}

void Sprite::SetScissor(RFTPoint TopLeft, RFTPoint BottomRight)
{
	agk::SetSpriteScissor(_spriteNumber, TopLeft.GetX(), TopLeft.GetY(), BottomRight.GetX(), BottomRight.GetY());
}

void Sprite::SetSize(float width, float height)
{
	agk::SetSpriteSize(_spriteNumber, width, height);
}

void Sprite::SetSnap(bool snap)
{
	agk::SetSpriteSnap(_spriteNumber, snap);
}

void Sprite::SetSpriteNumber(unsigned int number)
{
	if (_spriteNumber == 0)
		_spriteNumber = number;
}

void Sprite::SetTransparencySetting(short Setting)
{
	if (_TransparencySetting(Setting))
		agk::SetSpriteTransparency(_spriteNumber, Setting);
}

void Sprite::SetUV(RFTPoint UV1, RFTPoint UV2, RFTPoint UV3, RFTPoint UV4)
{
	agk::SetSpriteUV(_spriteNumber, UV1.GetX(), UV1.GetY(), UV2.GetX(), UV2.GetY(), UV3.GetX(), UV3.GetY(), UV4.GetX(), UV4.GetY());
}

void Sprite::SetUVBorder(float border)
{
	if (_UVBorder(border))
		agk::SetSpriteUVBorder(_spriteNumber, border);
}

void Sprite::SetUVOffset(float u, float v)
{
	agk::SetSpriteUVOffset(_spriteNumber, u, v);
}

void Sprite::SetUVScale(float u, float v)
{
	agk::SetSpriteUVScale(_spriteNumber, u, v);
}

void Sprite::SetVisible(bool visible)
{
	agk::SetSpriteVisible(_spriteNumber, visible);
}

void Sprite::SetX(float x)
{
	agk::SetSpriteX(_spriteNumber, x);
}

void Sprite::SetXByOffset(float x)
{
	agk::SetSpriteOffset(_spriteNumber, x, GetPositionByOffset().GetY());
}

void Sprite::SetY(float y)
{
	agk::SetSpriteY(_spriteNumber, y);
}

void Sprite::SetYByOffset(float y)
{
	agk::SetSpriteOffset(_spriteNumber, GetPositionByOffset().GetX(), y);
}

/*void Sprite::toggleVisiblity(void)
{
	if (this->GetVisible() == 0)
		this->SetVisible(true);
	else
		this->SetVisible(false);
}*/

Sprite &Sprite::Clone(void)
{
	Sprite *ReturnSprite = new Sprite();
	
	//ReturnSprite = this;
	ReturnSprite->_spriteNumber = agk::CloneSprite(this->_spriteNumber);

	return *ReturnSprite;
} 

/*unsigned int Sprite::Clone()
{
	return agk::CloneSprite(_spriteNumber);
} */

/*unsigned int Sprite::clone(unsigned int spriteToClone)
{
	return agk::CloneSprite(spriteToClone);
}*/

void Sprite::_Create(unsigned int assignedSpriteNumber)
{
	if (!assignedSpriteNumber)
		_spriteNumber = agk::CreateSprite(GetID());
	else
	{
		_spriteNumber = assignedSpriteNumber;
		agk::CreateSprite(_spriteNumber, GetID());
	}
}

bool Sprite::_Depth(short value)
{
	if (value >= 0)
	{
		if (value <= 10000)
			return true;
	}

	return false;
}

bool Sprite::_SpriteNumber(unsigned int number)
{
	if (number != 0)
		return true;

	return false;
}

bool Sprite::_TransparencySetting(short Setting)
{
	if (Setting >= 0)
	{
		if (Setting <= 2)
			return true;
	}

	return false;
}

bool Sprite::_UVBorder(float border)
{
	if (border >= 0.0f)
	{
		if (border <= 1.0f)
			return true;
	}

	return false;
}