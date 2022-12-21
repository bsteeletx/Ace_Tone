#include "Slider.h"
#include "InputPointer.h"

Slider::Slider()
{
}


Slider::~Slider()
{
}

Slider::Slider(unsigned int commonAtlasID)
{
	_Space = new Sprite(Color(0, 0, 0));
	_Knob = new Sprite(Color(128, 128, 128));//change to common Atlas

	_Space->SetVisible(false);
	_Knob->SetVisible(false);

	_dragging = false;
}

void Slider::Delete()
{
	_Space->Delete();
	_Knob->Delete();
}

void Slider::Hide()
{
	_Space->SetVisible(false);
	_Knob->SetVisible(false);
}

void Slider::Init()
{
	_Space->SetSize(25.0f, 1.0f);
	_Space->SetPosition(35.0f, 25.0f);
	_Space->SetDepth(4);
	_Knob->SetSize(2.5f);
	_Knob->SetOffset(RFTPoint(1.25, 1.25));
	_Knob->SetPositionByOffset(RFTPoint(47.5f, 25.0f));
	_Knob->SetDepth(2);
}

void Slider::Show()
{
	_Space->SetVisible(true);
	_Knob->SetVisible(true);
}

int Slider::Update()
{
	Pointer Mouse;
	RFTPoint TapLoc = RFTPoint();

	if (Mouse.GetState())
		TapLoc = Mouse.GetPosition();
	else if (Mouse.GetReleased() && _dragging)
	{
		TapLoc = Mouse.GetPosition();
		_dragging = false;
	}
	else
		return (int)100*_GetPercent();

	if (_dragging)
	{
		_Knob->SetPositionByOffset(RFTPoint(TapLoc.GetX(), _Knob->GetPositionByOffset().GetY()));
		//_dragging = false;
	}
	else if (_Knob->GetHit(TapLoc))
	{
		_dragging = true;
		_Knob->SetPositionByOffset(RFTPoint(TapLoc.GetX(), _Knob->GetPositionByOffset().GetY()));
	}
	else if (_Space->GetHit(TapLoc))
	{
		float diff = (TapLoc.GetX() - _Knob->GetPositionByOffset().GetX()) / 2.0f;
		_Knob->SetPositionByOffset(RFTPoint(_Knob->GetPositionByOffset().GetX() + diff, _Knob->GetPositionByOffset().GetY()));
	}

	return (int)100*_GetPercent();
}

float Slider::_GetPercent()
{
	float xPos = _Knob->GetPositionByOffset().GetX();

	xPos -= _Space->GetPosition().GetX();

	return xPos / _Space->GetWidth();
}