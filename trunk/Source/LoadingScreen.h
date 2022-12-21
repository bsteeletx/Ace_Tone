#ifndef _LOADINGSCREEN_H_
#define _LOADINGSCREEN_H_

#include "Sprite.h"
#include "LoadingIcon.h"

class LoadingScreen :
	public Sprite
{
public:
	LoadingScreen();
	~LoadingScreen();
	LoadingScreen(Text BackgroundLocation, Text IconLocation);

	void Delete();

	void Hide();

	void Update();

private:
	LoadingIcon *_LoadingIcon;
};

#endif