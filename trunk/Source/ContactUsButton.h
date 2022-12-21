#ifndef _CONTACTUSBUTTON_H_
#define _CONTACTUSBUTTON_H_

//#include "InputVirtualButton.h"
#include "Sprite.h"

class ContactUsButton :
	public Sprite
{
public:
	ContactUsButton();
	~ContactUsButton();
	ContactUsButton(RFTPoint Location, float size, unsigned int commonAtlasID);

	//void Delete();

	void Hide();

	void Init();

	void Show();

	void Update();

private:
	//Sprite *_ButtonImage;
};

#endif