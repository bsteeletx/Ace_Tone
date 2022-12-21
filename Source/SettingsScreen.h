#ifndef _SETTINGSSCREEN_H_
#define _SETTINGSSCREEN_H_

#include "Sprite.h"
#include "RestartButton.h"
#include "MuteButton.h"


class SettingsScreen : public Sprite
{
public:
	SettingsScreen();
	SettingsScreen(unsigned int commonAtlasID);
	~SettingsScreen();

	void Delete();

	void Hide();

	void Init();

	void Show();

	bool Update();

private:
	Read *_TextDoc;
	Text *_SettingsText;
	MuteButton *_MuteButton;
	RestartButton *_RestartButton;
};

#endif