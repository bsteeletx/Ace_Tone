#ifndef _SLIDER_H_
#define _SLIDER_H_

#include "Sprite.h"

class Slider
{
public:
	Slider();
	~Slider();
	Slider(unsigned int commonAtlasID);

	void Delete();

	void Hide();

	void Init();

	void Show();

	int Update();

private:
	bool _dragging;

	Sprite *_Space;
	Sprite *_Knob;

	float _GetPercent();
};

#endif