#ifndef _MUSICALNOTES_H_
#define _MUSICALNOTES_H_

#include "SpritePhysics.h"
#include "Globals.h"

class Notes : public PhysicsS
{
public:
	Notes();
	Notes(NoteValues NV, Sprite Clone);
	~Notes();

	Notes* CopySection(RFTPoint Begin, RFTPoint End);

	void Delete();

	void Explode();

	bool GetExploded();
	NoteValues GetNoteValue();

	void Init(unsigned int noteParentID);

	void Update();

private:
	bool _exploded;
	unsigned int _parentImage;

	NoteValues _ThisNote;
	PhysicsS *_SplitNotes[4];

	Notes(unsigned int imageNumber, RFTPoint Begin, RFTPoint End);

};

#endif