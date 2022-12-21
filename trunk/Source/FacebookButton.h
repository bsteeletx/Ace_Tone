#ifndef _FACEBOOKBUTTON_H_
#define _FACEBOOKBUTTON_H_

//#include "InputVirtualButton.h"
#include "Sprite.h"
#include "Facebook.h"

class FacebookButton :
	public Sprite
{
public:
	FacebookButton();
	~FacebookButton();
	FacebookButton(RFTPoint Location, float size, unsigned int atlasID);

	//void Delete();

	void Hide();

	void Init();

	void Show();

	void Update(RFTPoint MouseHitLoc); //= Point(-1.0f, 0.0f));

private:
	Facebook *_FBCommands;
	//Sprite *_FBImage;

	void _PostOnWall();
};

#endif