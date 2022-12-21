#ifndef _INPUTJOYSTICK_H_
#define _INPUTJOYSTICK_H_

#include "Point.h"
#include "Image.h"
#include "Input.h"

class Joystick : public Input
{
public:
	Joystick();
	~Joystick(void);
		
	bool GetButtonPressed(unsigned short buttonID);
	bool GetButtonReleased(unsigned short buttonID);
	bool GetButtonState(unsigned short buttonID);
	RFTPoint GetPos();

	void SetDeadZone(float deadZoneValue);
	void SetScreenPosition(RFTPoint Position, float size);
	
private:
	float _GetX();
	float _GetY();

	void _SetScreenPosition(float x, float y, float size);
};
#endif