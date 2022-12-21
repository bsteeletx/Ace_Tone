#ifndef _2DPHYSICSJOINT_H_
#define _2DPHYSICSJOINT_H_

#include "Sprite.h"
//#include "Point.h"

class Joint
{
public:
	Joint();
	~Joint(void);

	void Delete();

	bool GetExists(void);
	unsigned int GetJointID(void);
	float GetReactionForceX(void);
	float GetReactionForceY(void);
	float GetReactionTorque(void);

	void SetLimitOff(void);
	void SetLimitOn(float lowerBounds, float upperBounds);
	void SetMotorOff(void);
	void SetMotorOn(float speed, float maxForce);

protected:
	unsigned int _jointID;
};

class DistanceJoint : public Joint
{
public:
	DistanceJoint();
	~DistanceJoint();
	DistanceJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, RFTPoint AnchorForSprite1, RFTPoint AnchorForSprite2, bool canCollide);
	DistanceJoint(Sprite Object1, Sprite Object2, RFTPoint AnchorForSprite1, RFTPoint AnchorForSprite2, bool canCollide);
};

class GearJoint : public Joint
{
public:
	GearJoint();
	~GearJoint(void);
	GearJoint(unsigned int assignedIndex, Joint Object1, Joint Object2, float ratio);
	GearJoint(Joint Object1, Joint Object2, float ratio);
};

class LineJoint : public Joint
{
public:
	LineJoint();
	~LineJoint();
	LineJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, RFTPoint Anchor, RFTPoint Axis, bool canCollide);
	LineJoint(Sprite Object1, Sprite Object2, RFTPoint Anchor, RFTPoint Axis, bool canCollide);
};

class MouseJoint : public Joint
{
public:
	MouseJoint();
	~MouseJoint();
	MouseJoint(unsigned int assignedIndex, Sprite Object, RFTPoint Anchor, float maxForce);
	MouseJoint(Sprite Object, RFTPoint Anchor, float maxForce);

	void SetTarget(RFTPoint Location);
};

class PrismaticJoint : public Joint
{
public:
	PrismaticJoint();
	~PrismaticJoint();
	PrismaticJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, RFTPoint Anchor, RFTPoint Axis, bool canCollide);
	PrismaticJoint(Sprite Object1, Sprite Object2, RFTPoint Anchor, RFTPoint Axis, bool canCollide);
};

class PulleyJoint : public Joint
{
public:
	PulleyJoint();
	~PulleyJoint();
	PulleyJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, RFTPoint Ground1, RFTPoint Ground2, RFTPoint Anchor1, RFTPoint Anchor2, float ratio, bool canCollide);
	PulleyJoint(Sprite Object1, Sprite Object2, RFTPoint Ground1, RFTPoint Ground2, RFTPoint Anchor1, RFTPoint Anchor2, float ratio, bool canCollide);

private:
	unsigned int finish(RFTPoint Ground1, RFTPoint Ground2, RFTPoint Anchor1, RFTPoint Anchor2);
};

class RevoluteJoint : public Joint
{
	RevoluteJoint();
	~RevoluteJoint();
	RevoluteJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, RFTPoint Anchor, bool canCollide);
	RevoluteJoint(Sprite Object1, Sprite Object2, RFTPoint Anchor, bool canCollide);
};

class WeldJoint : public Joint
{
	WeldJoint();
	~WeldJoint();
	WeldJoint(unsigned int assignedIndex, Sprite Object1, Sprite Object2, RFTPoint Anchor, bool canCollide);
	WeldJoint(Sprite Object1, Sprite Object2, RFTPoint Anchor, bool canCollide);
};

#endif