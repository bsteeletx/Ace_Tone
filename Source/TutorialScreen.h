#ifndef _TUTORIALSCREEN_H_
#define _TUTORIALSCREEN_H_

#include "Sprite.h"

class TutorialScreen : public Sprite
{
public:
	TutorialScreen();
	TutorialScreen(Text ImageLocation, unsigned int commonAtlasID);
	~TutorialScreen();

	void Hide();

	void Init();

	void Show();

private:
	Text *_Title;
};

#endif