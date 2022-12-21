#ifndef _SPRITEEMITTER_H_
#define _SPRITEEMITTER_H_

#include "SpritePhysics.h"
#include "MusicalNotes.h"
#include <vector>

class SpriteEmitter
{
public:
	SpriteEmitter();
	SpriteEmitter(unsigned int commonAtlasID);
	~SpriteEmitter();

	bool CheckForHits(RFTPoint HitLocation);

	void Delete();
	void DeleteHits();
	
	unsigned int GetHitCount();
	NoteValues GetHitValue(unsigned int hitNumber);
	unsigned int GetLastUpdateTime();

	void Init(float notePercentages[NUMBER_OF_NOTES]);

	void Pause();

	void Reset();
	void Resume();

	void Update(unsigned int currentTime);

private:
	Sprite *_NoteTemplates[NUMBER_OF_NOTES];
	std::vector<Notes *> _Notes;
	std::vector<Notes *> _Hit;
	//Vector *_LastSwipe;
	//std::vector<unsigned short> _swipeLocations;

	unsigned int _lastUpdateTime;
	bool _isPaused;
	unsigned int _noteParentID;
	//bool _useFlats;
	//bool _useSharps;
	float _notePercentages[NUMBER_OF_NOTES];

	void _Delete();
	void _Delete(PhysicsS *SpriteToDelete);

	Crossings _GetCrossing(unsigned short crossingValue);
	NoteValues _GetNote(float randomPercent);

	void _Impulse(PhysicsS *NewSprite);
	
	bool _NoteIsFlat(unsigned short testNote);
	bool _NoteIsNatural(unsigned short testNote);
	bool _NoteIsSharp(unsigned short testNote);
	
	void _Spawn();
};

#endif