#ifndef _MAGICPOINTER_H_
#define _MAGICPOINTER_H_

#include "InputPointer.h"
#include "../Lib/Vietnam/Particles.h"
#include "Sound.h"

class MagicPointer : public Pointer
{
public:
	MagicPointer();
	~MagicPointer();

	void Delete();

	void Update();

private:
    RFTParticles *_Emitter;
	Sound *_SlashSound;
};

#endif