#pragma once

#include "Text.h"

class Benchmarking
{
public:
	Benchmarking();
	~Benchmarking();

	float GetDrawingSetupTime(void);
	float GetDrawingTime();
	unsigned short GetLoadedImages();
	unsigned short GetManagedSpriteCount();
	unsigned short  GetManagedSpriteDrawCalls();
	unsigned short GetManagedSpriteDrawnCount();
	unsigned short GetManagedSpriteSortedCount();
	//void GetParticleDrawnPointCount(); --Deprecated
	unsigned short GetParticleDrawnQuadCount();
	float GetPhysicsTime();
	unsigned int GetPixelsDrawn();
	Text GetUnassignedImageFileName(unsigned int unassignedImageIndex);
	unsigned short GetUnassignedImages();
	float GetUpdateTime();
};