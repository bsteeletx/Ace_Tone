#include "SpriteEmitter.h"
#include "AGKCore.h"
#include "Rectangle.h"

SpriteEmitter::SpriteEmitter()
{
	for (int i = 0; i < NUMBER_OF_NOTES - 1; i++)
		_NoteTemplates[i] = new Sprite();
}

SpriteEmitter::SpriteEmitter(unsigned int commonAtlasID)
{
	_noteParentID = commonAtlasID;
	
	_NoteTemplates[0] = new Sprite(commonAtlasID, "A.png");
	_NoteTemplates[1] = new Sprite(commonAtlasID, "A#.png");
	_NoteTemplates[2] = new Sprite(commonAtlasID, "Bf.png");
	_NoteTemplates[3] = new Sprite(commonAtlasID, "B.png");
	_NoteTemplates[4] = new Sprite(commonAtlasID, "B#.png");
	_NoteTemplates[5] = new Sprite(commonAtlasID, "Cf.png");
	_NoteTemplates[6] = new Sprite(commonAtlasID, "C.png");
	_NoteTemplates[7] = new Sprite(commonAtlasID, "C#.png");
	_NoteTemplates[8] = new Sprite(commonAtlasID, "Df.png");
	_NoteTemplates[9] = new Sprite(commonAtlasID, "D.png");
	_NoteTemplates[10] = new Sprite(commonAtlasID, "D#.png");
	_NoteTemplates[11] = new Sprite(commonAtlasID, "Ef.png");
	_NoteTemplates[12] = new Sprite(commonAtlasID, "E.png");
	_NoteTemplates[13] = new Sprite(commonAtlasID, "E#.png");
	_NoteTemplates[14] = new Sprite(commonAtlasID, "Ff.png");
	_NoteTemplates[15] = new Sprite(commonAtlasID, "F.png");
	_NoteTemplates[16] = new Sprite(commonAtlasID, "F#.png");
	_NoteTemplates[17] = new Sprite(commonAtlasID, "Gf.png");
	_NoteTemplates[18] = new Sprite(commonAtlasID, "G.png");
	_NoteTemplates[19] = new Sprite(commonAtlasID, "G#.png");
	_NoteTemplates[20] = new Sprite(commonAtlasID, "Af.png");
	_NoteTemplates[21] = new Sprite(commonAtlasID, "Eighth Note.png");
	_NoteTemplates[22] = new Sprite(commonAtlasID, "Eighth Rest.png");
	_NoteTemplates[23] = new Sprite(commonAtlasID, "Quarter Note.png");
	_NoteTemplates[24] = new Sprite(commonAtlasID, "Quarter Rest.png");
	_NoteTemplates[25] = new Sprite(commonAtlasID, "Half Note.png");
	_NoteTemplates[26] = new Sprite(commonAtlasID, "Half Rest.png");
}

SpriteEmitter::~SpriteEmitter()
{}

////////////////////////////////
// Checks to see if any sprites were hit by the pointing device
/////////////////////////////
bool SpriteEmitter::CheckForHits(RFTPoint HitLocation)
{
	bool hits = false;

	for (unsigned int i = 0; i < _Notes.size(); i++)
	{
		RFTPoint TopLeft = _Notes[i]->GetPosition();
		RFTPoint BottomRight = RFTPoint(TopLeft.GetX() + _Notes[i]->GetWidth(), TopLeft.GetY() + _Notes[i]->GetHeight());
		RectangleBounds BoundingBox = RectangleBounds(TopLeft, BottomRight);

		if (BoundingBox.ContainsPoint(HitLocation))
		{
			_Hit.push_back(_Notes[i]);
			//_swipeLocations.push_back(BoundingBox.GetCrossings());
			hits = true;
		} 
	}

	//_LastSwipe = Swipe;

	return hits;
}

/////////////////////////////
// Deletes everything out of memory
//////////////////////////////
void SpriteEmitter::Delete()
{
	for (int i = 0; i < NUMBER_OF_NOTES - 1; i++)
		_NoteTemplates[i]->Delete();
	
	for (int i = 0; i < _Notes.size(); i++)
		_Notes[i]->Delete();
	
	_Notes.clear();
	
	for (int i = 0; i < _Hit.size(); i++)
	{
		if (_Hit[i]->GetSpriteNumber() != 0)
			_Hit[i]->Delete();
	}

	_Hit.clear();
	
	_lastUpdateTime = 0;
}

//////////////////////////
// Deletes all Hits as they should be part of splits now
//////////////////////////
void SpriteEmitter::DeleteHits()
{
	_Hit.clear();
}

////////////////////////////////////
// Returns the number of hits from last swipe
//////////////////////////////////
unsigned int SpriteEmitter::GetHitCount()
{
	return _Hit.size();
}

/////////////////////////////////////
// Returns the value of the note that was hit
//////////////////////////////////////
NoteValues SpriteEmitter::GetHitValue(unsigned int hitID)
{
	NoteValues HitNote = _Hit[hitID]->GetNoteValue();
	
	_Hit[hitID]->Explode();
	
	return HitNote;
}

////////////////////////////////
// Returns last Time Sprite Emitter Update
////////////////////////////////
unsigned int SpriteEmitter::GetLastUpdateTime()
{
	return _lastUpdateTime;
}

void SpriteEmitter::Init(float notePercentages[NUMBER_OF_NOTES])
{
	for (int i = 0; i < NUMBER_OF_NOTES; i++)
	{
		_NoteTemplates[i]->SetSize(10.0f);
		_NoteTemplates[i]->SetOffset(RFTPoint(5.0f, 5.0f));
		_NoteTemplates[i]->SetPosition(RFTPoint(45.0f, 100.0f));
		_NoteTemplates[i]->SetVisible(false);
		_NoteTemplates[i]->SetDepth(100);

		_notePercentages[i] = notePercentages[i];
	}

	_isPaused = false;
}

void SpriteEmitter::Pause()
{
	for (int i = 0; i < _Notes.size(); i++)
		_Notes[i]->SetOff();

	_isPaused = true;
}

void SpriteEmitter::Reset()
{
	for (int i = 0; i < _Notes.size(); i++)
		_Notes[i]->Delete();

	_Notes.clear();
	_isPaused = false;
}

void SpriteEmitter::Resume()
{
	for (int i = 0; i < _Notes.size(); i++)
		_Notes[i]->SetOn();

	_isPaused = false;
}

/////////////////////////////
// Removes Sprites off Screen, Create New Sprites
////////////////////////////
void SpriteEmitter::Update(unsigned int currentTime)
{
	_Delete();
	_Spawn();

	_lastUpdateTime = currentTime;
}

/////////////////////////////
// remove Sprites Off Screen--has to be done backwards because _Notes will re-order after each erase
////////////////////////////
void SpriteEmitter::_Delete()
{
	std::vector<int> toErase;
	std::vector<int> partialsToErase;

	//find out which ones are offscreen
	for (unsigned int i = 0; i < _Notes.size(); i++)
	{
		RFTPoint Position = _Notes[i]->GetPosition();

		if (Position.GetX() > 100.0f || Position.GetX() < -50.0f)
		{
			_Notes[i]->Delete();
			toErase.push_back(i);
		}
		else if (Position.GetY() > 150.0f)
		{
			_Notes[i]->Delete();
			toErase.push_back(i);
		}
	}

	//erase off vector
	while (toErase.size() > 0)
	{
		int eraser = toErase.back();
		toErase.pop_back();

		_Notes.erase(_Notes.begin() + eraser); 
	}
}

//////////////////////////////////////////
// Deletes a specific PhysicsS Sprite
///////////////////////////////////////
void SpriteEmitter::_Delete(PhysicsS *SpriteToDelete)
{
	for (unsigned int i = 0; i < _Notes.size(); i++)
	{
		if (_Notes[i] == SpriteToDelete)
		{
			_Notes[i]->Delete();
			_Notes.erase(_Notes.begin() + i);
		}
	}
}

////////////////////////////////
// Returns crossings of sprite
//////////////////////////////
Crossings SpriteEmitter::_GetCrossing(unsigned short crossData)
{
	switch (crossData)
	{
	case 3: return TOPANDLEFT;
	case 5: return HORIZONTAL_THROUGH;
	case 6: return TOPANDRIGHT;
	case 9: return BOTTOMANDLEFT;
	case 10: return VERTICAL_THROUGH;
	case 12: return BOTTOMANDRIGHT;
	default: return NO_CROSSINGS;
	}
}

///////////////////////////////////
// Returns Note from floating random value
////////////////////////////////////
NoteValues SpriteEmitter::_GetNote(float randomNumber)
{
	float total = 0.0f;

	for (int i = 0; i < NUMBER_OF_NOTES; i++)
	{
		total += _notePercentages[i];

		if (randomNumber < total)
			return (NoteValues)(i + 1);
	}

	return NOTEERROR;
}

////////////////////////////
// Gives a random impulse to a sprite
///////////////////////////
void SpriteEmitter::_Impulse(PhysicsS *NewSprite)
{
	AGKCore Maths;
	Vector Impulse;
	RFTPoint LeftVectorDirection;
	RFTPoint RightVectorDirection;
	RFTPoint LeftImpulsePosition = RFTPoint(47.5f, 105.0f);
	RFTPoint RightImpulsePosition = RFTPoint(52.5f, 105.0f);
	int direction = Maths.Random(0, 64);
	direction = Maths.RandomSign(direction);

	if (direction > 0)
	{
		LeftVectorDirection = RFTPoint(direction, -225);
		RightVectorDirection = RFTPoint(0, -225);
	}
	else if (direction < 0)
	{
		LeftVectorDirection = RFTPoint(0, -225);
		RightVectorDirection = RFTPoint(direction, -225);
	}
	else
	{
		LeftVectorDirection = RFTPoint(0, -225);
		RightVectorDirection = RFTPoint(0, -225);
	}

	Impulse = Vector(LeftImpulsePosition, LeftVectorDirection);
	NewSprite->SetImpulse(Impulse);
	Impulse = Vector(RightImpulsePosition, RightVectorDirection);
	NewSprite->SetImpulse(Impulse);
}

////////////////////////////
// Spawns new PhysicsS Sprites and gives them an Impulse
//////////////////////////
void SpriteEmitter::_Spawn()
{
	AGKCore Maths;
	NoteValues note = NOTEERROR;

	if (_isPaused)
		return;
	//////////////////Choose a random sprite to spawn in
	/*note = Maths.Random(0, NUMBER_OF_NOTES - 1); 
	
	//if flats, use flats or naturals
	if (!_useFlats && _NoteIsFlat(note + 1))
		return;
	//if sharps, use sharps or naturals
	else if (!_useSharps && _NoteIsSharp(note + 1))
		return;
	//if neither sharps or flats, use naturals
	else if (!_useFlats && !_useSharps && !_NoteIsNatural(note + 1))
		return;
*/

	float randomNum = 100.0f * (float)(Maths.Random()) / 65535.0f; //0 -65535

	note = _GetNote(randomNum);

	Sprite SClone = _NoteTemplates[note-1]->Clone();
	Notes *PClone = new Notes((NoteValues)(note), SClone);

	PClone->Init(_noteParentID);

	_Notes.push_back(PClone);

	_Notes.back()->SetVisible(true);
	_Notes.back()->SetActive(true);
	_Notes.back()->SetCollideBit(1, false); //all sprites are set to category 1 for collision

	_Impulse(_Notes.back());
}

bool SpriteEmitter::_NoteIsFlat(unsigned short testNote)
{
	switch (testNote)
	{
	case BFLAT: return true;
	case CFLAT: return true;
	case DFLAT: return true;
	case EFLAT: return true;
	case FFLAT: return true;
	case GFLAT: return true;
	case AFLAT: return true;
	default: return false;
	}
}

bool SpriteEmitter::_NoteIsNatural(unsigned short testNote)
{
	switch (testNote)
	{
	case A: return true;
	case B: return true;
	case C: return true;
	case D: return true;
	case E: return true;
	case F: return true;
	case G: return true;
	default: return false;
	}
}

bool SpriteEmitter::_NoteIsSharp(unsigned short testNote)
{
	switch (testNote)
	{
	case ASHARP: return true;
	case BSHARP: return true;
	case CSHARP: return true;
	case DSHARP: return true;
	case ESHARP: return true;
	case FSHARP: return true;
	case GSHARP: return true;
	default: return false;
	}
}