#ifndef _LIVESINDICATOR_H_
#define _LIVESINDICATOR_H_

#include "Sprite.h"
//May need animated sprites for strings

class LivesIndicator
{
public:
	LivesIndicator();
	~LivesIndicator();
	LivesIndicator(unsigned int commonAtlasID);

	//gain life?
	void Delete();

	void Hide();

	void Init();

	bool LoseLife();

	void Reset();

private:
	Sprite *_Strings[6];
	//Sprite *_Guitar;
};

#endif