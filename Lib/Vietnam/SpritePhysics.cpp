#include "agk.h"
#include "SpritePhysics.h"

PhysicsS::PhysicsS() : Sprite()
{
}

/*PhysicsS::PhysicsS(unsigned int assignedImageNumber, unsigned int assignedSpriteNumber, short mode)
	: Sprite(assignedImageNumber, assignedSpriteNumber)
{
	SetOn(mode);
}*/

PhysicsS::PhysicsS (unsigned int imageNumber, RFTPoint Begin, RFTPoint End)
: Sprite(imageNumber, Begin, End)
{
	//SetOn(mode);
} 

PhysicsS::PhysicsS (Text Filename, short mode)
	: Sprite(Filename)
{
	SetOn(mode);
}

/*PhysicsS::PhysicsS (unsigned int assignedImageNumber, Text Filename, bool blackIsAlpha, unsigned int assignedSpriteNumber, short mode)
	: Sprite(assignedImageNumber, Filename, blackIsAlpha, assignedSpriteNumber)
{
	SetOn(mode);
}*/

PhysicsS::PhysicsS (unsigned int parentImage, Text SubImageFilename, short mode)
	: Sprite(parentImage, SubImageFilename)
{
	SetOn(mode);
}

/*PhysicsS::PhysicsS (unsigned int assignedImageNumber, unsigned int parentImage, Text SubImageFilename, unsigned int assignedSpriteNumber, short mode)
	: Sprite(assignedImageNumber, parentImage, SubImageFilename, assignedSpriteNumber)
{
	SetOn(mode);
}*/

/*PhysicsS& PhysicsS::operator=(const PhysicsS& TempSprite)
{

}*/

PhysicsS::PhysicsS(Sprite Clone)
: Sprite(Clone)
{
	//(Sprite)*this = (Sprite)this->Clone();
	SetOn(2);
}

PhysicsS::~PhysicsS()
{
}


void PhysicsS::AddShapeBox(RFTPoint TopLeft, RFTPoint BottomRight, float angleInRads)
{
	agk::AddSpriteShapeBox(_spriteNumber, TopLeft.GetX(), TopLeft.GetY(), BottomRight.GetX(), BottomRight.GetY(), angleInRads);
}

void PhysicsS::AddShapeCircle(RFTPoint CenterOfCircle, float radius)
{
	agk::AddSpriteShapeCircle(_spriteNumber, CenterOfCircle.GetX(), CenterOfCircle.GetY(), radius);
}

void PhysicsS::AddShapePolygon(unsigned int numOfPoints, unsigned int pointIndex, RFTPoint Location)
{
	if (_ShapePolygon(numOfPoints, pointIndex))
		agk::AddSpriteShapePolygon(_spriteNumber, numOfPoints, pointIndex, Location.GetX(), Location.GetY());
}

void PhysicsS::CalculateCOM(void)
{
	agk::CalculateSpritePhysicsCOM(_spriteNumber);
}

void PhysicsS::ClearShapes(void)
{
	agk::ClearSpriteShapes(_spriteNumber);
}

PhysicsS &PhysicsS::Clone()
{
	PhysicsS *ReturnSprite = new PhysicsS();

	//ReturnSprite = this;
	ReturnSprite->_spriteNumber = agk::CloneSprite(_spriteNumber);

	return *ReturnSprite;
}

PhysicsS *PhysicsS::CopySection(unsigned int imageNumber, RFTPoint Begin, RFTPoint End, short mode)
{
	PhysicsS *NewObject = new PhysicsS(imageNumber, Begin, End);

	NewObject->SetOn(mode);

	return NewObject;
}

bool PhysicsS::GetCollision(Sprite TestSprite)
{
	if (agk::GetPhysicsCollision(_spriteNumber, TestSprite.GetSpriteNumber()) == 1)
		return true;
	else
		return false;
}

float PhysicsS::GetAngularVelocity(void)
{
	return agk::GetSpritePhysicsAngularVelocity(_spriteNumber);
}

float PhysicsS::GetCollisionWorldX(void)
{
	return agk::GetPhysicsCollisionWorldX();
}

float PhysicsS::GetCollisionWorldY(void)
{
	return agk::GetPhysicsCollisionWorldY();
}

float PhysicsS::GetCollisionX(void)
{
	return agk::GetPhysicsCollisionX();
}

float PhysicsS::GetCollisionY(void)
{
	return agk::GetPhysicsCollisionY();
}

bool PhysicsS::GetIsInCategory(unsigned short categoryNum)
{
	return _category[categoryNum];
}

bool PhysicsS::GetIsInCollisionGroup(unsigned short collisionNum)
{
	return _collision[collisionNum];
}

float PhysicsS::GetMass(void)
{
	return agk::GetSpritePhysicsMass(_spriteNumber);
}

bool PhysicsS::GetUsingPhysics(void)
{
	return _usingPhysics;
}

float PhysicsS::GetVelocityX(void)
{
	return agk::GetSpritePhysicsVelocityX(_spriteNumber);
}

float PhysicsS::GetVelocityY(void)
{
	return agk::GetSpritePhysicsVelocityY(_spriteNumber);
}

void PhysicsS::SetAngularDamping(float damp)
{
	if (_ZeroToOneFloat(damp))
		agk::SetSpritePhysicsAngularDamping(_spriteNumber, damp);
}

void PhysicsS::SetAngularImpulse(float impulse)
{
	agk::SetSpritePhysicsAngularImpulse(_spriteNumber, impulse);
}

void PhysicsS::SetAngularVelocity(float aVelocity)
{
	agk::SetSpritePhysicsAngularVelocity(_spriteNumber, aVelocity);
}

/*void PhysicsS::SetBounciness(float bounciness)
{
	if (_ZeroToOneFloat(bounciness))
		agk::SetSpritePhysicsRestitution(_spriteNumber, bounciness);
} */

void PhysicsS::SetCanRotate(bool canRotate)
{
	agk::SetSpritePhysicsCanRotate(_spriteNumber, canRotate);
}

void PhysicsS::SetCategoryBit(unsigned short categoryNum, bool inCategory)
{
	if (_ZeroToFifteen(categoryNum))
	{
		agk::SetSpriteCategoryBit(_spriteNumber, categoryNum, inCategory);
		_category[categoryNum] = inCategory;
	}
}

void PhysicsS::SetCategoryBits(unsigned int bits)
{
	if (_ZeroToMaxInt(bits, (2^16)-1))
	{
		int remainder = bits;

		for (int i = 15; i >= 0; i--)
		{
			int j = 2^i;

			if (remainder / j > 0)
			{
				_category[i] = true;
				remainder -= j;
			}
			else
				_category[i] = false;
		}

		agk::SetSpriteCategoryBits(_spriteNumber, bits);
	}
}

void PhysicsS::SetCollideBit(unsigned short collisionNum, bool inCollision)
{
	if (_ZeroToFifteen(collisionNum))
	{
		agk::SetSpriteCollideBit(_spriteNumber, collisionNum, inCollision);
		_collision[collisionNum] = inCollision;
	}
}

void PhysicsS::SetCollideByBit(unsigned int bits)
{
	if (_ZeroToMaxInt(bits, (2^16)-1))
	{

		int remainder = bits;

		for (int i = 15; i > 0; i--)
		{
			int j = 2^i;

			if (remainder / j > 0)
			{
				_collision[i] = true;
				remainder -= j;
			}
			else
				_collision[i] = false;
		}

		agk::SetSpriteCollideBits(_spriteNumber, bits);
	}
}

void PhysicsS::SetCOM(RFTPoint COM)
{
	agk::SetSpritePhysicsCOM(_spriteNumber, COM.GetX(), COM.GetY());
}

void PhysicsS::SetDamping(float damp)
{
	if (_ZeroToOneFloat(damp))
		agk::SetSpritePhysicsDamping(_spriteNumber, damp);
}

void PhysicsS::SetDelete()
{
	agk::SetSpritePhysicsDelete(_spriteNumber);
}

void PhysicsS::SetForce(Vector Force)
{
	agk::SetSpritePhysicsForce(_spriteNumber, Force.GetStartPointX(), Force.GetStartPointY(), Force.GetEndPointX(), Force.GetEndPointY());
}

void PhysicsS::SetFriction(float friction)
{
	if (_ZeroToOneFloat(friction))
		agk::SetSpritePhysicsFriction(_spriteNumber, friction);
}

/////////////////////////
// Assigns this sprite to a group for filtering collisions (physics or non physics). 
// In physics, sprites of the same positive group ID will always collide, 
// whilst those that share the same negative group ID will never collide. 
// Those with a group ID of zero (default), or differing group IDs move on to the category filter check.
//////////////////////////
void PhysicsS::SetGroup(int group)
{
	agk::SetSpriteGroup(_spriteNumber, group);
}

void PhysicsS::SetImpulse(Vector Impulse)
{
	agk::SetSpritePhysicsImpulse(_spriteNumber, Impulse.GetStartPointX(), Impulse.GetStartPointY(), Impulse.GetEndPointX(), Impulse.GetEndPointY());
}

void PhysicsS::SetIsBullet(bool isBullet)
{
	if (isBullet)
		agk::SetSpritePhysicsIsBullet(_spriteNumber, 1);
	else
		agk::SetSpritePhysicsIsBullet(_spriteNumber, 0);
}

void PhysicsS::SetIsSensor(bool isSensor)
{
	if(isSensor)
		agk::SetSpritePhysicsIsSensor(_spriteNumber, 1);
	else
		agk::SetSpritePhysicsIsSensor(_spriteNumber, 0);
}

void PhysicsS::SetMass(float massInKG)
{
	if (_UnsignedFloat(massInKG))
		agk::SetSpritePhysicsMass(_spriteNumber, massInKG);
}

void PhysicsS::SetTorque(float torque)
{
	agk::SetSpritePhysicsTorque(_spriteNumber, torque);
}

void PhysicsS::SetVelocity(float xVelocity, float yVelocity)
{
	agk::SetSpritePhysicsVelocity(_spriteNumber, xVelocity, yVelocity);
}

void PhysicsS::SetShape(short shapeType)
{
	if (_Shape(shapeType))
		agk::SetSpriteShape(_spriteNumber, shapeType);
}

void PhysicsS::SetShapeBox(RFTPoint TopLeft, RFTPoint BottomRight, float angleInRads)
{
	agk::SetSpriteShapeBox(_spriteNumber, TopLeft.GetX(), TopLeft.GetY(), BottomRight.GetX(), BottomRight.GetY(), angleInRads);
}

void PhysicsS::SetShapeCircle(RFTPoint CenterOfCircle, float radius)
{
	agk::SetSpriteShapeCircle(_spriteNumber, CenterOfCircle.GetX(), CenterOfCircle.GetY(), radius);
}

void PhysicsS::SetShapePolygon(short numOfPoints, short pointIndex, RFTPoint Location)
{
	if (_ShapePolygon(numOfPoints, pointIndex))
		agk::SetSpriteShapePolygon(_spriteNumber, numOfPoints, pointIndex, Location.GetX(), Location.GetY());
}

void PhysicsS::SetOff(void)
{
	agk::SetSpritePhysicsOff(_spriteNumber);
}

void PhysicsS::SetOn(short mode)
{
	if(_Mode(mode))
		agk::SetSpritePhysicsOn(_spriteNumber, mode);
}

bool PhysicsS::_Mode(short value)
{
	if (value > 0)
	{
		if (value <= 3)
			return true;
	}

	return false;
}

bool PhysicsS::_Shape(short shapeType)
{
	if (shapeType >= 0)
	{
		if (shapeType <= 3)
			return true;
	}

	return false;
}

bool PhysicsS::_ShapePolygon(short numOfPoints, short pointIndex)
{
	if (numOfPoints > 0)
	{
		if (pointIndex > 0)
		{
			if (numOfPoints >= pointIndex)
				return true;
		}
	}

	return false;
}

bool PhysicsS::_UnsignedFloat(float value)
{
	if (value >= 0.0f)
		return true;
	else
		return false;
}

bool PhysicsS::_ZeroToFifteen(unsigned int value)
{
	if (value < 16)
		return true;

	return false;
}

bool PhysicsS::_ZeroToMaxInt(unsigned int value, unsigned int maxValue)
{
	if (value < maxValue)
		return true;

	return false;
}

bool PhysicsS::_ZeroToOneFloat(float value)
{
	if (value >= 0.0f)
	{
		if (value <= 1.0f)
			return true;
	}

	return false;
}