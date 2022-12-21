#ifndef _RESTARTBUTTON_H_
#define _RESTARTBUTTON_H_

#include "InputVirtualButton.h"

class RestartButton : public VirtualButton
{
public:
	RestartButton();
	RestartButton(unsigned int commonAtlasID);
	~RestartButton();

	void Init();

	bool Update();

private:
	Sprite *_ButtonImage;
};

#endif