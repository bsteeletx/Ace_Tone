#ifndef _SUCCESSSCREEN_H_
#define _SUCCESSSCREEN_H_

#include "Sprite.h"
#include "FacebookButton.h"
#include "Twitter.h"
#include "InputVirtualButton.h"

class SuccessScreen : public Sprite
{
public:
	SuccessScreen();
	SuccessScreen(unsigned int commonAtlasID);
	~SuccessScreen();

	void Delete();

	void Hide();
	
	void Init();

	void Show();

	int Update(RFTPoint MouseHitLoc);

private:
	Read *_TextDoc;
	Text *_SuccessText;
	Text *_MainMenuText;
	Text *_NextSongText;
	Twitter *_TwitterCommands;
	FacebookButton *_FBButton;
	Sprite *_FacebookLike;
	Sprite *_TwitterButton;
	Sprite *_MainMenuButton;
	Sprite *_NextSongButton;
	unsigned int _commonAtlasID;
};

#endif