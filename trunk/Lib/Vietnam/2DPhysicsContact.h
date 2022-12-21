#pragma once

#include "Point.h"
#include "Sprite.h"

class Contact
{
public:
	Contact();
	~Contact();

	unsigned int GetSpriteID1(void);
	unsigned int GetSpriteID2(void);
	RFTPoint GetWorld(void);
	float GetWorldX(void);
	float GetWorldY(void);
	bool GetFirst(void);
	bool GetNext(void);
	unsigned int GetSpriteSpriteID2(void);
	RFTPoint GetSpriteWorld(void);
	float GetSpriteWorldX(void);
	float GetSpriteWorldY(void);
	bool GetSpriteFirst(Sprite Object);
	bool GetSpriteNext(void);
};