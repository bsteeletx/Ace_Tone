#ifndef _Song_H
#define _Song_H

#include "Sprite.h"
#include "agk.h"
#include "InputPointer.h"

class Song
{
public:
	Song();
	~Song();
	
	void Init(float);
	bool CheckForHits();
	void ClickEvent();
private:
	Sprite* _sprite;
	//4 array of objects that change game level state when selected
		//objects cascade downward
		//initialize all song objects on menu_load
		//change list based on menu_tab select event
	Pointer* _POINTER;
};
#endif