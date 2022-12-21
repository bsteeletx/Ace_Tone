#ifndef _SCORERECORD_H_
#define _SCORERECORD_H_

#include "Sprite.h"

class ScoreRecord : public Sprite
{
public:
	ScoreRecord();
	ScoreRecord(unsigned int commonAtlasID);
	~ScoreRecord();

	void Hide();

	void Init(RFTPoint Location);

	void Show();
};

#endif