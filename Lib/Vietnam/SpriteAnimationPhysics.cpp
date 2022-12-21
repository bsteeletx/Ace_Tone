#include "SpriteAnimationPhysics.h"

AnimationPhysics::AnimationPhysics()
{

}

AnimationPhysics::AnimationPhysics(PhysicsS PObject, Animation AObject)
{
	_SpriteAnimation = AObject;
	_SpritePhysics = PObject;
}

AnimationPhysics::~AnimationPhysics()
{

}