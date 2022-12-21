#ifndef _INPUTTEXT_H_
#define _INPUTTEXT_H_

#include "Input.h"

class InputText : public Input
{
public:
	InputText();
	~InputText();

	Text Get(); 
	bool GetCancelled(); 
	bool GetCompleted();
	unsigned int GetLastChar(); 
	TextInputState GetState();

	void SetCursorBlinkTime(float value);
	void SetMaxCharacters(unsigned int value); 
	void Start(Text InitialText = ""); 
	void Stop(); 
};
#endif