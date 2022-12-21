#ifndef _CHORDDISPLAYBOX_H_
#define _CHORDDISPLAYBOX_H_

#include "Sprite.h"
#include "Text.h"

class ChordDisplayBox
{
public:
	ChordDisplayBox();
	ChordDisplayBox(Text ChordName);
	~ChordDisplayBox();

	void Delete();
	void DisplayNextChord(unsigned int currentTime);

	Text GetName();

	void Hide();

	void Init();

	void Reset();

	void Update(unsigned int currentTime);

private:
	std::vector<Text *> _ChordNames;
	//Sprite *_Background;
	unsigned short _currentChord;
	bool _flashing;
	unsigned int _correctChordTime;
};

#endif