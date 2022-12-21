#ifndef _GAMECENTERBUTTON_H_
#define _GAMECENTERBUTTON_H_

//#include "InputVirtualButton.h"
#include "Sprite.h"
#include "GameCenter.h"

class GameCenterButton :
	public Sprite
{
public:
	GameCenterButton();
	~GameCenterButton();
	GameCenterButton(RFTPoint Location, float size, unsigned int commonAtlasID);

	//void Delete();

	void Hide();

	void Init();

	void Show();

	void Update();

private:
	//Sprite *_ButtonImage;
	GameCenter *_GCCommands;
};

#endif