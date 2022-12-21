#ifndef _SPRITEANIMATIONPHYSICS_H_
#define _SPRITEANIMATIONPHYSICS_H_

#include "SpriteAnimation.h"
#include "SpritePhysics.h"

class AnimationPhysics
{
	AnimationPhysics();
	AnimationPhysics(PhysicsS PObject, Animation AObject);
	~AnimationPhysics();

private:
	Animation _SpriteAnimation;
	PhysicsS _SpritePhysics;
};

#endif