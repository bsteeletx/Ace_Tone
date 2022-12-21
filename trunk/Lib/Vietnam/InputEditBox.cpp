#include "InputEditBox.h"
#include "agk.h"

EditBox::EditBox()
{
	_boxID = agk::CreateEditBox();
}

EditBox::~EditBox()
{
//	if (GetExists())
//		agk::DeleteEditBox(_boxID);
}

EditBox::EditBox(unsigned int boxNumber)
{
	_boxID = boxNumber;
	agk::CreateEditBox(_boxID);
}

void EditBox::Delete()
{
	agk::DeleteEditBox(_boxID);
}

void EditBox::FixToScreen(bool toScreen)
{
	if (toScreen)
		agk::FixEditBoxToScreen(_boxID, 1);
	else
		agk::FixEditBoxToScreen(_boxID, 0);
}

bool EditBox::GetActive(void)
{
	if (agk::GetEditBoxActive(_boxID) == 1)
		return true;

	return false;
}

bool EditBox::GetChanged(void)
{
	if (agk::GetEditBoxChanged(_boxID) == 1)
		return true;

	return false;
}

bool EditBox::GetExists(void)
{
	if (agk::GetEditBoxExists(_boxID) == 1)
		return true;

	return false;
}

bool EditBox::GetHasFocus(void)
{
	if (agk::GetEditBoxHasFocus(_boxID) == 1)
		return true;

	return false;
}

float EditBox::GetHeight(void)
{
	return agk::GetEditBoxHeight(_boxID);
}

unsigned int EditBox::GetLines(void)
{
	return agk::GetEditBoxLines(_boxID);
}

Text EditBox::GetText(void)
{
	Text ReturnText(agk::GetEditBoxText(_boxID));
	
	return ReturnText;
}

bool EditBox::GetVisible(void)
{
	if (agk::GetEditBoxVisible(_boxID) == 1)
		return true;

	return false;
}

float EditBox::GetWidth(void)
{
	return agk::GetEditBoxWidth(_boxID);
}

float EditBox::GetX(void)
{
	return agk::GetEditBoxX(_boxID);
}

float EditBox::GetY(void)
{
	return agk::GetEditBoxY(_boxID);
}

void EditBox::SetActive(bool active)
{
	if (active)
		agk::SetEditBoxActive(_boxID, 1);
	else
		agk::SetEditBoxActive(_boxID, 0);
}

void EditBox::SetBackgroundColor(Color Values)
{
	agk::SetEditBoxBackgroundColor(_boxID, Values.GetRed(), Values.GetGreen(), Values.GetBlue(), Values.GetAlpha());
}

void EditBox::SetBackgroundImage(Image Object)
{
	agk::SetEditBoxBackgroundImage(_boxID, Object.GetID());
}

void EditBox::SetBorderColor(Color Values)
{
	agk::SetEditBoxBorderColor(_boxID, Values.GetRed(), Values.GetGreen(), Values.GetBlue(), Values.GetAlpha());
}

void EditBox::SetBorderImage(Image Object)
{
	agk::SetEditBoxBorderImage(_boxID, Object.GetID());
}

void EditBox::SetBorderSize(float size)
{
	if (size >= 0.0f)
		agk::SetEditBoxBorderSize(_boxID, size);
}

void EditBox::SetCursorBlinkTime(float speedInSeconds)
{
	if (speedInSeconds > 0.0f)
		agk::SetEditBoxCursorBlinkTime(_boxID, speedInSeconds);
}

void EditBox::SetCursorColor(Color Values)
{
	agk::SetEditBoxCursorColor(_boxID, Values.GetRed(), Values.GetGreen(), Values.GetBlue());
}

void EditBox::SetCursorWidth(float width)
{
	if (width > 0.0f)
		agk::SetEditBoxCursorWidth(_boxID, width);
}

void EditBox::SetDepth(unsigned int depth)
{
	if (depth <= 10000)
		agk::SetEditBoxDepth(_boxID, depth);
}

/* Not Working Yet
///////////////////////////
// Sets the extended font image to use for this edit box, 
// must have been previously loaded with LoadImage(). 
// Use 0 to return the edit box to its default extended font. 
// If you do not set this image the edit box will not accept extended characters such as £ é á etc.
//////////////////////////
void EditBox::SetExtendedFontImage(unsigned short fontID)
{
	agk::SetEditBoxExtendedFontImage(_boxID, fontID);
}*/

void EditBox::SetFocus(bool focus)
{
	if (focus)
		agk::SetEditBoxFocus(_boxID, 1);
	else
		agk::SetEditBoxFocus(_boxID, 0);
}

void EditBox::SetFontImage(Image Object)
{
	agk::SetEditBoxFontImage(_boxID, Object.GetID());
}

void EditBox::SetMaxChars(unsigned int max)
{
	agk::SetEditBoxMaxChars(_boxID, max);
}

void EditBox::SetMaxLines(unsigned int max)
{
	agk::SetEditBoxMaxLines(_boxID, max);
}

void EditBox::SetPosition(RFTPoint Location)
{
	agk::SetEditBoxPosition(_boxID, Location.GetX(), Location.GetY());
}

void EditBox::SetScissor(RFTPoint TopLeft, RFTPoint BottomRight)
{
	agk::SetEditBoxScissor(_boxID, TopLeft.GetX(), TopLeft.GetY(), BottomRight.GetX(), BottomRight.GetY());
}

void EditBox::SetSize(float width, float height)
{
	if (width > 0.0f)
	{
		if (height > 0.0f)
			agk::SetEditBoxSize(_boxID, width, height);
	}
}

void EditBox::SetText(Text Input)
{
	agk::SetEditBoxText(_boxID, Input.GetCString());
}

void EditBox::SetTextColor(Text Input)
{
	agk::SetEditBoxTextColor(_boxID, Input.GetColorRed(), Input.GetColorGreen(), Input.GetColorBlue());
}

void EditBox::SetTextSize(Text Input)
{
	agk::SetEditBoxTextSize(_boxID, Input.GetSize());
}

#if OS != WINDOWS
/////////////////////////////
// Sets whether the edit box will use an alternate text input method if the edit box would be hidden by a virtual keyboard. 
// This only applies to mobile platforms like iOS and Android and the alternate input method is usually a smaller edit box placed just above the keyboard. 
// The edit box will still update in real time as if it is being typed into directly, 
// but since it is covered by the keyboard the user will not see it. 
// By default this is turned on. 
// If you wish you can turn it off and move the edit box into view when GetEditBoxHasFocus returns true, 
// be sure to move it back again when GetEditBoxHasFocus returns false.
//////////////////////////
void EditBox::SetUseAlternateInput(bool useAltInput)
{
	if (useAltInput)
		agk::SetEditBoxUseAlternateInput(_boxID, 1);
	else
		agk::SetEditBoxUseAlternateInput(_boxID, 0);
}
#endif

void EditBox::SetVisible(bool visible)
{
	if (visible)
		agk::SetEditBoxVisible(_boxID, 1);
	else
		agk::SetEditBoxVisible(_boxID, 0);
}

void EditBox::SetWrapText(bool wrapText)
{
	if (wrapText)
		agk::SetEditBoxMultiLine(_boxID, 1);
	else
		agk::SetEditBoxMultiLine(_boxID, 0);
}