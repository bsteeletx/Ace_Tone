#include "Menu_TitleBar.h"
#include "AGKCore.h"

TitleBar::TitleBar()
{}

TitleBar::TitleBar(Text Filename)
: Sprite(Filename)
{
	//_Logo = new Sprite(Color(0, 0, 0));
}

TitleBar::~TitleBar()
{
}

void TitleBar::Init()
{
	AGKCore Convert;

	SetSize(100.0f);
	SetDepth(10);
	//SetPosition(0.0f, 0.0f);

	//_Logo->SetSize(10.0f, 7.5f);
	//_Logo->SetPosition(Point(45.0f, 1.25f));
}

/*float TitleBar::Height()
{
	return _titlesprite->GetHeight();
} */

/*void TitleBar::Delete()
{
	Sprite::Delete();
	_Logo->Delete();
} */
