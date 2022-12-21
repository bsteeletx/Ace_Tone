#include "2DPhysicsRayCast.h"
#include "3DObject.h"
#include "agk.h"

RayCast::RayCast(Object Casting, Vector Direction, float radius, bool useSlide)
{
	if (radius == 0.0f)
	{
		if(agk::ObjectRayCast(Casting.GetID(), Direction.GetStartPointX(), Direction.GetStartPointY(), Direction.GetStartPointZ(), Direction.GetEndPointX(), Direction.GetEndPointY(), Direction.GetEndPointZ()) == 1)
		{
			if (agk::GetObjectRayCastNumHits())
				_rayCastID = agk::GetObjectRayCastHitID(0);
		}
	}
	else if (!useSlide)
	{
		if(agk::ObjectSphereCast(Casting.GetID(), Direction.GetStartPointX(), Direction.GetStartPointY(), Direction.GetStartPointZ(), Direction.GetEndPointX(), Direction.GetEndPointY(), Direction.GetEndPointZ(), radius) == 1)
		{
			if (agk::GetObjectRayCastNumHits())
				_rayCastID = agk::GetObjectRayCastHitID(0);
		}
	}
	else
	{
		if(agk::ObjectSphereSlide(Casting.GetID(), Direction.GetStartPointX(), Direction.GetStartPointY(), Direction.GetStartPointZ(), Direction.GetEndPointX(), Direction.GetEndPointY(), Direction.GetEndPointZ(), radius) > 0)
		{
			if (agk::GetObjectRayCastNumHits())
				_rayCastID = agk::GetObjectRayCastHitID(0);
		}
	}
}

RayCast::RayCast(Vector Direction, RayCastMode value, int groupInfo)
{
	_rayCastID = 0;

	switch (value)
	{
	case PHYSICS:
		_anyHits = (bool)agk::PhysicsRayCast(Direction.GetStartPointX(), Direction.GetStartPointY(), Direction.GetEndPointX(), Direction.GetEndPointY());
		break;
	case PHYSICS_CATEGORY:
		_anyHits = (bool)agk::PhysicsRayCastCategory(groupInfo, Direction.GetStartPointX(), Direction.GetStartPointY(), Direction.GetEndPointX(), Direction.GetEndPointY());
		break;
	case PHYSICS_GROUP:
		_anyHits = (bool)agk::PhysicsRayCastGroup(groupInfo, Direction.GetStartPointX(), Direction.GetStartPointY(), Direction.GetEndPointX(), Direction.GetEndPointY());
		break;
	case SPRITE:
		_anyHits = (bool)agk::SpriteRayCast(Direction.GetStartPointX(), Direction.GetStartPointY(), Direction.GetEndPointX(), Direction.GetEndPointY());
		break;
	case SPRITE_CATEGORY:
		_anyHits = (bool)agk::SpriteRayCastCategory(groupInfo, Direction.GetStartPointX(), Direction.GetStartPointY(), Direction.GetEndPointX(), Direction.GetEndPointY());
		break;
	case SPRITE_GROUP:
		_anyHits = (bool)agk::SpriteRayCastGroup(groupInfo, Direction.GetStartPointX(), Direction.GetStartPointY(), Direction.GetEndPointX(), Direction.GetEndPointY());
		break;
	case SPRITE_SINGLE:
		_anyHits = (bool)agk::SpriteRayCastSingle(groupInfo, Direction.GetStartPointX(), Direction.GetStartPointY(), Direction.GetEndPointX(), Direction.GetEndPointY());
		break;
	}		
}

RayCast::~RayCast(void)
{
}

float RayCast::GetFraction(void)
{
	return agk::GetRayCastFraction();
}

RFTPoint RayCast::GetNormal(void)
{
	return RFTPoint(GetNormalX(), GetNormalY());
}

float RayCast::GetNormalX(void)
{
	return agk::GetRayCastNormalX();
}

float RayCast::GetNormalY(void)
{
	return agk::GetRayCastNormalY();
}

/*Point RayCast::GetObjectBounce(void)
{
	return Point(GetObjectBounceX(), GetObjectBounceY(), GetObjectBounceZ());
}

float RayCast::GetObjectBounceX(void)
{
	return agk::GetObjectRayCastBounceX(_rayCastID);
}

float RayCast::GetObjectBounceY(void)
{
	return agk::GetObjectRayCastBounceY(_rayCastID);
}

float RayCast::GetObjectBounceZ(void)
{
	return agk::GetObjectRayCastBounceZ(_rayCastID);
}

float RayCast::GetObjectDistance(void)
{
	return agk::GetObjectRayCastDistance(_rayCastID);
}
	
unsigned int RayCast::GetObjectHitID(void)
{
	return agk::GetObjectRayCastHitID(_rayCastID);
}

Point RayCast::GetObjectNormal(void)
{
	return Point(GetObjectNormalX(), GetObjectNormalY(), GetObjectNormalZ());
}

float RayCast::GetObjectNormalX(void)
{
	return agk::GetObjectRayCastNormalX(_rayCastID);
}

float RayCast::GetObjectNormalY(void)
{
	return agk::GetObjectRayCastNormalY(_rayCastID);
}

float RayCast::GetObjectNormalZ(void)
{
	return agk::GetObjectRayCastNormalZ(_rayCastID);
}

Point RayCast::GetObjectPosition(void)
{
	return Point(GetObjectX(), GetObjectY(), GetObjectZ());
}

unsigned short RayCast::GetObjectNumHits(void)
{
	return agk::GetObjectRayCastNumHits();
}

Point RayCast::GetObjectSlide(void)
{
	return Point(GetObjectSlideX(), GetObjectSlideY(), GetObjectSlideZ());
}

float RayCast::GetObjectSlideX(void)
{
	return agk::GetObjectRayCastSlideX(_rayCastID);
}

float RayCast::GetObjectSlideY(void)
{
	return agk::GetObjectRayCastSlideY(_rayCastID);
}

float RayCast::GetObjectSlideZ(void)
{
	return agk::GetObjectRayCastSlideZ(_rayCastID);
}

float RayCast::GetObjectX(void)
{
	return agk::GetObjectRayCastX(_rayCastID);
}

float RayCast::GetObjectY(void)
{
	return agk::GetObjectRayCastX(_rayCastID);
}

float RayCast::GetObjectZ(void)
{
	return agk::GetObjectRayCastZ(_rayCastID);
}				 */

RFTPoint RayCast::GetPosition(void)
{
	return RFTPoint(GetX(), GetY());
}

unsigned int RayCast::GetSpriteID(void)
{
	return agk::GetRayCastSpriteID();
}

float RayCast::GetX(void)
{
	return agk::GetRayCastX();
}

float RayCast::GetY(void)
{
	return agk::GetRayCastY();
}