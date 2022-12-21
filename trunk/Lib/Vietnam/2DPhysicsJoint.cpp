#include "2DPhysicsJoint.h"
#include "agk.h"

Joint::Joint(void)
{
	_jointID = 0;
}

Joint::~Joint(void)
{
	//if (GetExists())
	//	agk::DeleteJoint(_jointID);
}

void Joint::Delete()
{
	agk::DeleteJoint(_jointID);
}

bool Joint::GetExists(void)
{
	if (agk::GetJointExists(_jointID) == 1)
		return true;

	return false;
}

unsigned int Joint::GetJointID(void)
{
	return _jointID;
}

float Joint::GetReactionForceX(void)
{
	return agk::GetJointReactionForceX(_jointID);
}

float Joint::GetReactionForceY(void)
{
	return agk::GetJointReactionForceY(_jointID);
}

float Joint::GetReactionTorque(void)
{
	return agk::GetJointReactionTorque(_jointID);
}

void Joint::SetLimitOff(void)
{
	agk::SetJointLimitOff(_jointID);
}

void Joint::SetLimitOn(float lowerBounds, float upperBounds)
{
	agk::SetJointLimitOn(_jointID, lowerBounds, upperBounds);
}

void Joint::SetMotorOff(void)
{
	agk::SetJointMotorOff(_jointID);
}

void Joint::SetMotorOn(float speed, float maxForce)
{
	agk::SetJointMotorOn(_jointID, speed, maxForce);
}

DistanceJoint::DistanceJoint(void)
{
	_jointID = 0;
}

DistanceJoint::~DistanceJoint(void)
{
	if (GetExists())
		agk::DeleteJoint(_jointID);
}

DistanceJoint::DistanceJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, RFTPoint AnchorForSprite1, RFTPoint AnchorForSprite2, bool canCollide)
{
	if (canCollide)
		agk::CreateDistanceJoint(assignedIndex, Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), AnchorForSprite1.GetX(), AnchorForSprite1.GetY(), AnchorForSprite2.GetX(), AnchorForSprite2.GetY(), 1);
	else
		agk::CreateDistanceJoint(assignedIndex, Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), AnchorForSprite1.GetX(), AnchorForSprite1.GetY(), AnchorForSprite2.GetX(), AnchorForSprite2.GetY(), 0);

	_jointID = assignedIndex;
}

DistanceJoint::DistanceJoint(Sprite Object1, Sprite Object2, RFTPoint AnchorForSprite1, RFTPoint AnchorForSprite2, bool canCollide)
{
	if (canCollide)
		_jointID = agk::CreateDistanceJoint(Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), AnchorForSprite1.GetX(), AnchorForSprite1.GetY(), AnchorForSprite2.GetX(), AnchorForSprite2.GetY(), 1);
	else
		_jointID = agk::CreateDistanceJoint(Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), AnchorForSprite1.GetX(), AnchorForSprite1.GetY(), AnchorForSprite2.GetX(), AnchorForSprite2.GetY(), 0);
}

GearJoint::GearJoint(void)
{
	_jointID = 0;
}

GearJoint::~GearJoint(void)
{
	if (GetExists())
		agk::DeleteJoint(_jointID);
}

GearJoint::GearJoint(unsigned int assignedIndex, Joint Object1, Joint Object2, float ratio)
{
	agk::CreateGearJoint(assignedIndex, Object1.GetJointID(), Object2.GetJointID(), ratio);

	_jointID = assignedIndex;
}

GearJoint::GearJoint(Joint Object1, Joint Object2, float ratio)
{
	_jointID = agk::CreateGearJoint(Object1.GetJointID(), Object2.GetJointID(), ratio);
}

LineJoint::LineJoint(void)
{
	_jointID = 0;
}

LineJoint::~LineJoint(void)
{
	if (GetExists())
		agk::DeleteJoint(_jointID);
}

LineJoint::LineJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, RFTPoint Anchor, RFTPoint Axis, bool canCollide)
{
	if (canCollide)
		agk::CreateLineJoint(assignedIndex, Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), Anchor.GetX(), Anchor.GetY(), Axis.GetX(), Axis.GetY(), 1);
	else
		agk::CreateLineJoint(assignedIndex, Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), Anchor.GetX(), Anchor.GetY(), Axis.GetX(), Axis.GetY(), 0);

	_jointID = assignedIndex;
}

LineJoint::LineJoint(Sprite Object1, Sprite Object2, RFTPoint Anchor, RFTPoint Axis, bool canCollide)
{
	if (canCollide)
		agk::CreateLineJoint(Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), Anchor.GetX(), Anchor.GetY(), Axis.GetX(), Axis.GetY(), 1);
	else
		agk::CreateLineJoint(Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), Anchor.GetX(), Anchor.GetY(), Axis.GetX(), Axis.GetY(), 1);
}

MouseJoint::MouseJoint(void)
{
	_jointID = 0;
}

MouseJoint::~MouseJoint(void)
{
	if (GetExists())
		agk::DeleteJoint(_jointID);
}

MouseJoint::MouseJoint(unsigned int assignedIndex, Sprite Object, RFTPoint Anchor, float maxForce)
{
	agk::CreateMouseJoint(assignedIndex, Object.GetSpriteNumber(), Anchor.GetX(), Anchor.GetY(), maxForce);
	_jointID = assignedIndex;
}

MouseJoint::MouseJoint(Sprite Object, RFTPoint Anchor, float maxForce)
{
	_jointID = agk::CreateMouseJoint(Object.GetSpriteNumber(), Anchor.GetX(), Anchor.GetY(), maxForce);
}

void MouseJoint::SetTarget(RFTPoint Location)
{
	agk::SetJointMouseTarget(_jointID, Location.GetX(), Location.GetY());
}

PrismaticJoint::PrismaticJoint(void)
{
	_jointID = 0;
}

PrismaticJoint::~PrismaticJoint(void)
{
	if (GetExists())
		agk::DeleteJoint(_jointID);
}

PrismaticJoint::PrismaticJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, RFTPoint Anchor, RFTPoint Axis, bool canCollide)
{
	if (canCollide)
		agk::CreatePrismaticJoint(assignedIndex, Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), Anchor.GetX(), Anchor.GetY(), Axis.GetX(), Axis.GetY(), 1);
	else
		agk::CreatePrismaticJoint(assignedIndex, Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), Anchor.GetX(), Anchor.GetY(), Axis.GetX(), Axis.GetY(), 0);

	_jointID = assignedIndex;
}

PrismaticJoint::PrismaticJoint(Sprite Object1, Sprite Object2, RFTPoint Anchor, RFTPoint Axis, bool canCollide)
{
	if (canCollide)
		_jointID = agk::CreatePrismaticJoint(Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), Anchor.GetX(), Anchor.GetY(), Axis.GetX(), Axis.GetY(), 1);
	else
		_jointID = agk::CreatePrismaticJoint(Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), Anchor.GetX(), Anchor.GetY(), Axis.GetX(), Axis.GetY(), 0);
}

PulleyJoint::PulleyJoint(void)
{
	_jointID = 0;
}

PulleyJoint::~PulleyJoint(void)
{
	if (GetExists())
		agk::DeleteJoint(_jointID);
}

PulleyJoint::PulleyJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, RFTPoint Ground1, RFTPoint Ground2, RFTPoint Anchor1, RFTPoint Anchor2, float ratio, bool canCollide)
{
	if (canCollide)
		agk::CreatePulleyJoint(assignedIndex, Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), Ground1.GetX(), Ground1.GetY(), Ground2.GetX(), Ground2.GetY(), Anchor1.GetX(), Anchor1.GetY(), Anchor2.GetX(), Anchor2.GetY(), ratio, 1);
	else
		agk::CreatePulleyJoint(assignedIndex, Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), Ground1.GetX(), Ground1.GetY(), Ground2.GetX(), Ground2.GetY(), Anchor1.GetX(), Anchor1.GetY(), Anchor2.GetX(), Anchor2.GetY(), ratio, 0);

	_jointID = assignedIndex;
}

PulleyJoint::PulleyJoint(Sprite Object1, Sprite Object2, RFTPoint Ground1, RFTPoint Ground2, RFTPoint Anchor1, RFTPoint Anchor2, float ratio, bool canCollide)
{
	if (canCollide)
		agk::CreatePulleyJoint2(Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), ratio, 1);
	else
		agk::CreatePulleyJoint2(Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), ratio, 0);

	_jointID = finish (Ground1, Ground2, Anchor1, Anchor2);
}

unsigned int PulleyJoint::finish(RFTPoint Ground1, RFTPoint Ground2, RFTPoint Anchor1, RFTPoint Anchor2)
{
	return agk::FinishPulleyJoint(Ground1.GetX(), Ground1.GetY(), Ground2.GetX(), Ground2.GetY(), Anchor1.GetX(), Anchor1.GetY(), Anchor2.GetX(), Anchor2.GetY());
}

RevoluteJoint::RevoluteJoint(void)
{
	_jointID = 0;
}

RevoluteJoint::~RevoluteJoint(void)
{
	if (GetExists())
		agk::DeleteJoint(_jointID);
}

RevoluteJoint::RevoluteJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, RFTPoint Anchor, bool canCollide)
{
	_jointID = assignedIndex;
	if (canCollide)
		agk::CreateRevoluteJoint(assignedIndex, Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), Anchor.GetX(), Anchor.GetY(), 1);
	else
		agk::CreateRevoluteJoint(assignedIndex, Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), Anchor.GetX(), Anchor.GetY(), 0);
}

RevoluteJoint::RevoluteJoint(Sprite Object1, Sprite Object2, RFTPoint Anchor, bool canCollide)
{
	if (canCollide)
		agk::CreateRevoluteJoint(Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), Anchor.GetX(), Anchor.GetY(), 1);
	else
		agk::CreateRevoluteJoint(Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), Anchor.GetX(), Anchor.GetY(), 0);
}

WeldJoint::WeldJoint(void)
{
	_jointID = 0;
}

WeldJoint::~WeldJoint(void)
{
	if (GetExists())
		agk::DeleteJoint(_jointID);
}

WeldJoint::WeldJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, RFTPoint Anchor, bool canCollide)
{
	_jointID = assignedIndex;

	if (canCollide)
		agk::CreateWeldJoint(assignedIndex, Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), Anchor.GetX(), Anchor.GetY(), 1);
	else
		agk::CreateWeldJoint(assignedIndex, Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), Anchor.GetX(), Anchor.GetY(), 0);
}

WeldJoint::WeldJoint(Sprite Object1, Sprite Object2, RFTPoint Anchor, bool canCollide)
{
	if (canCollide)
		_jointID = agk::CreateWeldJoint(Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), Anchor.GetX(), Anchor.GetY(), 1);
	else
		_jointID = agk::CreateWeldJoint(Object1.GetSpriteNumber(), Object2.GetSpriteNumber(), Anchor.GetX(), Anchor.GetY(), 0);
}