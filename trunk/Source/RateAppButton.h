#ifndef _RATEAPPBUTTON_H_
#define _RATEAPPBUTTON_H_

//#include "InputVirtualButton.h"
#include "Sprite.h"

class RateAppButton :
	public Sprite
{
public:
	RateAppButton();
	~RateAppButton();
	RateAppButton(RFTPoint Location, float size, unsigned int commonAtlasID);

	//void Delete();

	void Hide();

	void Init();

	void Show();

	void Update();

private:
	//Sprite *_ButtonImage;
};

#endif