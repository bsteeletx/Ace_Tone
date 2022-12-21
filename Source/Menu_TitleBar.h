#ifndef _TITLEBAR_H
#define _TITLEBAR_H

#include "Sprite.h"
#include "Color.h"

class TitleBar : public Sprite
{
public:
	TitleBar();
	~TitleBar();
	TitleBar(Text Filename);
	
	void Init();
	//float Height();
	//void Delete();
private:
	//Sprite* _titlesprite;
	//Sprite *_Logo;
};
#endif