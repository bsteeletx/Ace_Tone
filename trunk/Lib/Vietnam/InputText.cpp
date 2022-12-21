#include "InputText.h"
#include "agk.h"

InputText::InputText()
: Input()
{

}

InputText::~InputText()
{

}

Text InputText::Get()
{
	return Text(agk::GetTextInput());
}

bool InputText::GetCancelled(void)
{
	if (agk::GetTextInputCancelled())
		return true;

	return false;
}

bool InputText::GetCompleted(void)
{
	if (agk::GetTextInputCompleted())
		return true;

	return false;
}

unsigned int InputText::GetLastChar(void)
{
	return agk::GetLastChar();
}

TextInputState InputText::GetState(void)
{
	return (TextInputState)agk::GetTextInputState();
}

void InputText::SetCursorBlinkTime(float value)
{
	agk::SetCursorBlinkTime(value);
}

void InputText::SetMaxCharacters(unsigned int value)
{
	agk::SetTextInputMaxChars(value);
}

void InputText::Start(Text Initial)
{
	if (Initial != "")
		agk::StartTextInput(Initial.GetCString());
	else
		agk::StartTextInput();
}

void InputText::Stop(void)
{
	agk::StopTextInput();
}