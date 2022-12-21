#ifndef _DIFFICULTYTOGGLE_H_
#define _DIFFICULTYTOGGLE_H_

#include "InputVirtualButton.h"

class DifficultyToggle
{
public:
	DifficultyToggle();
	~DifficultyToggle();
	DifficultyToggle(unsigned int commonAtlasID);

	void Delete();

	void Hide();

	void Init();

	void Show();

	void Update();

private:
	unsigned short _difficulty;

	VirtualButton *_DifficultyButtons[3];
	Sprite *_DifficultySpriteUp[3];
	Sprite *_DifficultySpriteDown[3];
};

#endif