#ifndef _SETTINGSBUTTON_H_
#define _SETTINGSBUTTON_H_

#include "InputVirtualButton.h"

class SettingsButton : public VirtualButton
{
public:
	SettingsButton();
	SettingsButton(unsigned int commonAtlasID);
	~SettingsButton();

	unsigned int GetLastUpdateTime();

	void Init();

	bool Update(unsigned int currentTime);

private:
	unsigned int _lastUpdate;

	Sprite *_ButtonImage;
};

#endif