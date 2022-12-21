#ifndef _FAILSCREEN_H_
#define _FAILSCREEN_H_

#include "Sprite.h"
#include "RestartButton.h"

class FailScreen : public Sprite
{
public:
	FailScreen();
	FailScreen(unsigned int commonAtlasID);
	~FailScreen();

	void Delete();

	void Hide();

	void Init();

	void Show();

	bool Update();

private:
	Read *_TextDoc;
	Text *_FailText;
	RestartButton *_RestartButton;
};

#endif