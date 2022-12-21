#ifndef _SPRITE_H_
#define _SPRITE_H_
#include "Image.h"
#include "Color.h"
#include "FileRead.h"
#include "Text.h"

class Sprite: public Image
{
public:
	~Sprite(void);
	Sprite(void);
	Sprite (Color SpriteColor);
	//Sprite (Text Filename, unsigned int assignedImageNumber, unsigned int assignedSpriteNumber);
	Sprite (Text Filename); 
	Sprite (unsigned int parentImage, Text SubImageFilename);
	Sprite (Read FileToInit, Text PathToParent);
				
	Sprite& operator= (const Sprite &OtherSprite);
	Sprite& operator<< (const Image& Object);

	//////////////////Properties
	//unsigned int clone(void);
	//unsigned int clone(unsigned int assignedSpriteNumber);
	Sprite& Clone(void);
	//unsigned int Clone();
	Sprite* CopySection(RFTPoint Begin, RFTPoint End);
	bool collidedWith(Sprite TestSprite);
	bool collidedWith(unsigned int testSpriteNumber);

	void Delete();
	void Draw();

	void FixToScreen(bool screen = 1);

	bool GetActive(void);
	float GetAngle(void);
	float GetAngleInRad(void);
	short GetColorAlpha(void);	
	short GetColorBlue(void);
	short GetColorGreen(void);
	short GetColorRed(void);	
	short GetDepth(void);
	bool GetExists(void);
	int GetGroup(void);
	float GetHeight(void);
	bool GetHit(RFTPoint HitLocation);
	int GetHitCategory(int categories, RFTPoint HitLocation);
	int GetHitGroup(RFTPoint HitLocation);
	unsigned int GetImageID(void);
	RFTPoint GetOffset(void);
	int GetPixelFromX(float x); 
	int GetPixelFromY(float y); 
	RFTPoint GetPosition(void);
	RFTPoint GetPositionByOffset(void);
	RFTPoint GetPositionFromPixel(RFTPoint PixelLocation);
	RFTPoint GetPositionFromWorld(RFTPoint Point1, RFTPoint Point2);
	unsigned int GetSpriteNumber(void);
	bool GetVisible(void);
	float GetWidth(void);
	float GetWorldX(float x, float y);
	float GetWorldY(float x, float y);
	RFTPoint getWorldPosition(RFTPoint Point1, RFTPoint Point2);
	//float GetXByOffset(void);
	float GetXFromPixel(int x);
	float GetXFromWorld(RFTPoint ToConvert);
	//float GetYByOffset(void);
	float GetYFromPixel(int y);
	float GetYFromWorld(RFTPoint ToConvert);

	void Move(RFTPoint Speed);
	void MoveX(float x);
	void MoveY(float y);

	void ResetUV(void);

	void SetActive(bool isActive);
	void SetAngle(float angle); 
	void SetAngleInRad(float rad);
	void SetColor(Color SpriteColor);
	void SetColorAlpha(short alpha); 	
	void SetColorBlue(short blue); 
	void SetColorGreen(short green); 
	void SetColorRed(short red);	
	void SetDepth(short depth); 
	void SetFlip(bool horizontal, bool vertical);
	void setGroup(int group);
	void SetImage(Image newImage, bool reshape = false);
	void SetOffset(RFTPoint Offset);
	virtual void SetPosition(float x, float y);
	virtual void SetPosition(RFTPoint Locaiton);
	//void SetPositionByOffset(float x, float y);
	void SetPositionByOffset(RFTPoint Location);
	void SetScale(float x, float y);
	void SetScaleByOffset(RFTPoint Offset);
	void SetScissor(RFTPoint TopLeft, RFTPoint BottomRight);
	void SetSize(float width = -1.0f, float height = -1.0f);
	void SetSnap(bool snap = true);
	void SetSpriteNumber(unsigned int number);
	void SetTransparencySetting(short setting);
	void SetUV(RFTPoint UV1, RFTPoint UV2, RFTPoint UV3, RFTPoint UV4);
	void SetUVBorder(float border = 0.5f);
	void SetUVOffset(float u, float v);
	void SetUVScale(float u, float v);
	virtual void SetVisible(bool visible);
	void SetX(float x);
	void SetXByOffset(float x);
	void SetY(float y);
	void SetYByOffset(float y);

	//////////////////////////Collision
	bool GetCollision(Sprite TestSprite); 
	bool GetCollision(unsigned int testSpriteNumber);
	int GetCollisionGroup(void);
	float GetDistanceFrom(Sprite TestSprite);
	float GetDistancePoint1X(void);
	float GetDistancePoint1Y(void);
	float GetDistancePoint2X(void);
	float GetDistancePoint2Y(void);
	bool GetInBox(RFTPoint TopLeft, RFTPoint BottomRight);
	bool GetInCircle(RFTPoint CenterOfCircle, float radius);

	void SetCollisionGroup(int groupID);

protected:
	unsigned int _spriteNumber;
	Color _SpriteColor;
	
	float _GetOffsetX(void);
	float _GetOffsetY(void);
	float _GetX(void);
	float _GetY(void);

	Sprite(unsigned int imageID, RFTPoint Begin, RFTPoint End);
	
	
private:
	void _Create(unsigned int assignedSpriteNumber = 0);

	bool _Depth(short value);
	bool _SpriteNumber(unsigned int number);
	bool _TransparencySetting(short setting);
	bool _UVBorder(float border);
};
#endif