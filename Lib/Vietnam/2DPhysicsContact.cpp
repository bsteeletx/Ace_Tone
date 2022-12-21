#include "2DPhysicsContact.h"
#include "agk.h"

Contact::Contact(void)
{
}


Contact::~Contact(void)
{
}

unsigned int Contact::GetSpriteID1(void)
{
	return agk::GetContactSpriteID1();
}

unsigned int Contact::GetSpriteID2(void)
{
	return agk::GetContactSpriteID2();
}

RFTPoint Contact::GetWorld(void)
{
	return RFTPoint(GetWorldX(), GetWorldY());
}

float Contact::GetWorldX(void)
{
	return agk::GetContactWorldX();
}

float Contact::GetWorldY(void)
{
	return agk::GetContactWorldY();
}

bool Contact::GetFirst(void)
{
	if (agk::GetFirstContact())
		return true;

	return false;
}

bool Contact::GetNext(void)
{
	if (agk::GetNextContact())
		return true;

	return false;
}

unsigned int Contact::GetSpriteSpriteID2(void)
{
	return agk::GetSpriteContactSpriteID2();
}

RFTPoint Contact::GetSpriteWorld(void)
{
	return RFTPoint(GetSpriteWorldX(), GetSpriteWorldY());
}

float Contact::GetSpriteWorldX(void)
{
	return agk::GetSpriteContactWorldX();
}

float Contact::GetSpriteWorldY(void)
{
	return agk::GetSpriteContactWorldY();
}

bool Contact::GetSpriteFirst(Sprite Object)
{
	if (agk::GetSpriteFirstContact(Object.GetID()))
		return true;

	return false;
}

bool Contact::GetSpriteNext(void)
{
	if (agk::GetSpriteNextContact())
		return true;

	return false;
}