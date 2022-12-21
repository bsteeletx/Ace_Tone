#ifndef _MUTEBUTTON_H_
#define _MUTEBUTTON_H_

#include "InputVirtualButton.h"
#include "Sprite.h"

class MuteButton : public VirtualButton
{
public:
	MuteButton();
	MuteButton(Image CommonAtlas);
	~MuteButton();

	void Init();

	void Update();

private:
	bool _isMuted;
	Sprite *_MuteOffImage;
	Sprite *_MuteOnImage;

	void _ToggleMute();
};

#endif