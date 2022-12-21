#ifndef _LEVELBACKGROUND_H_
#define _LEVELBACKGROUND_H_

#include "Sprite.h"

class LevelBackground : public Sprite
{
public:
	LevelBackground();
	LevelBackground(Text ImageLocation);
	~LevelBackground();

	void AddTransition(Text ImageLocation);

	void HideTransition();
	
	void Init();

	void ShowTransition();

private:
	Sprite *_Transition;
};

#endif