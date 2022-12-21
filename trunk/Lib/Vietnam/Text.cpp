#include "agk.h"
#include "AGKCore.h"
#include "Text.h"
#include "Image.h"

Text::Text(void)
{
	_textNumber = 0;
	_canBeSeen = false;
}

Text::~Text(void)
{
//	if (GetExists())
//		agk::DeleteText(_textNumber);
}

Text::Text(std::string textString, bool isVisible)
{
	//for (unsigned int i = 0; i < textString.size(); i++)
	//	newString[i] = textString[i];
	_canBeSeen = isVisible;

	if (isVisible)
	{
		_textNumber = agk::CreateText(textString.c_str());
		_canBeSeen = true;
	}

	_storedString = textString;
	
	if (_canBeSeen)
		SetVisible(isVisible);
}

Text::Text(char singleChar, bool isVisible)
{
	AGKCore Converter;

	_canBeSeen = isVisible;

	_storedString = Converter.Chr((unsigned int)singleChar).GetCString();

	if (isVisible)
	{
		_textNumber = agk::CreateText(_storedString.c_str());
		_canBeSeen = true;
	}
}

Text::Text(const char* textString, bool isVisible)
{
	_canBeSeen = isVisible;

	if (isVisible)
	{
		_textNumber = agk::CreateText(textString);
		_canBeSeen = true;
	}

	_storedString = textString;
	
	if (isVisible)
		SetVisible(isVisible);
}

/*Text::Text(unsigned int assignedTextNumber, const char* textString)
{
	agk::CreateText(assignedTextNumber, textString);
	_textNumber = assignedTextNumber;

	SetVisible(false);
}*/

/*Text& Text::operator= (const Text& newText)
{
	Text ReturnText(newText);
	
	if (this != &newText)
	{
		if (_canBeSeen)
		{
			if (GetExists())
				agk::DeleteText(_textNumber);
			else
				_textNumber = ReturnText._textNumber;
		}
		
		SetString(ReturnText.GetString());
	}

	return *this;
}*/

bool Text::operator!= (const Text otherText)
{
	return (_storedString != otherText._storedString);
}

Text& Text::operator+= (Text newText)
{
	std::string returnString;
	Text AddedText(newText);	

	returnString = this->GetString();
	returnString.append(newText.GetString());

	SetString(returnString);

	return *this;
}

bool Text::operator== (Text otherText)
{
	if (_storedString == otherText.GetString())
		return true;

	return false;
}

void Text::Delete()
{
	if (_canBeSeen)
		agk::DeleteText(_textNumber);
}

void Text::FixToScreen(bool toScreen)
{
	if (toScreen)
		agk::FixTextToScreen(_textNumber, 1);
	else
		agk::FixTextToScreen(_textNumber, 0);
}

int Text::FoundNeedle(const char needle)
{
	return (int) _storedString.find(needle);
}

char Text::GetChar(unsigned int index)
{
	if (_Index(index))
	{
		char textString[64];
		strcpy(textString, GetCString());
		return textString[index];
	}

	return '`';
}

float Text::GetCharAngle(unsigned int index)
{
	if (_Index(index))
		return agk::GetTextCharAngle(_textNumber, index);

	return 0.0f;
}

float Text::GetCharAngleInRad(unsigned int index)
{
	if (_Index(index))
		return agk::GetTextCharAngleRad(_textNumber, index);

	return 0.0f;
}

unsigned short Text::GetCharColorAlpha(unsigned int index)
{
	if (_Index(index))
		return (unsigned short) agk::GetTextCharColorAlpha(_textNumber, index);

	return 0;
}

unsigned short Text::GetCharColorBlue(unsigned int index)
{
	if (_Index(index))
		return (unsigned short) agk::GetTextCharColorBlue(_textNumber, index);

	return 0;
}

unsigned short Text::GetCharColorGreen(unsigned int index)
{
	if (_Index(index))
		return (unsigned short) agk::GetTextCharColorGreen(_textNumber, index);

	return 0;
}

unsigned short Text::GetCharColorRed(unsigned int index)
{
	if (_Index(index))
		return (unsigned short) agk::GetTextCharColorRed(_textNumber, index);

	return 0;
}

float Text::GetCharX(unsigned int index)
{
	if (_Index(index))
		return agk::GetTextCharX(_textNumber, index);

	return 0.0f;
}

float Text::GetCharY(unsigned int index)
{
	if (_Index(index))
		return agk::GetTextCharY(_textNumber, index);

	return 0.0f;
}

unsigned short Text::GetColorAlpha(void)
{
	return (unsigned short) agk::GetTextColorAlpha(_textNumber);
}

unsigned short Text::GetColorBlue(void)
{
	return (unsigned short) agk::GetTextColorBlue(_textNumber);
}

unsigned short Text::GetColorGreen(void)
{
	return (unsigned short) agk::GetTextColorGreen(_textNumber);
}

unsigned short Text::GetColorRed(void)
{
	return (unsigned short) agk::GetTextColorRed(_textNumber);
}

const char *Text::GetCString(void)
{
	return _storedString.c_str();
}

short Text::GetDelimiterIndex(char separator)
{
	for (unsigned int i = 0; i < GetLength(); i++)
	{
		if (_storedString[i] == separator)
			return i;
	}

	return -1;
}

unsigned int Text::GetDepth(void)
{
	return agk::GetTextDepth(_textNumber);
}

bool Text::GetExists(void)
{
	if (agk::GetTextExists(_textNumber) == 1)
		return true;

	return false;
}

bool Text::GetHitTest(RFTPoint Location)
{
	if (agk::GetTextHitTest(_textNumber,Location.GetX(), Location.GetY()) == 1)
		return true;
	
	return false;
}

unsigned int Text::GetID(void)
{
	return _textNumber;
}

unsigned int Text::GetLength(void)
{
	return _storedString.length();
}

unsigned int Text::GetNextID(void)
{
	int i = 1;

	while (agk::GetTextExists(i) == 1)
		i++;

	return i;
}

float Text::GetLineSpacing(void)
{
	return agk::GetTextLineSpacing(_textNumber);
}

float Text::GetSize(void)
{
	return agk::GetTextSize(_textNumber);
}

float Text::GetSpacing(void)
{
	return agk::GetTextSpacing(_textNumber);
}

std::string Text::GetString(void)
{
	return _storedString;
}

float Text::GetTotalHeight(void)
{
	return agk::GetTextTotalHeight(_textNumber);
}

float Text::GetTotalWidth(void)
{
	return agk::GetTextTotalWidth(_textNumber);
}

bool Text::GetVisible(void)
{
	if (agk::GetTextVisible(_textNumber) == 1)
		return true;

	return false;
}

float Text::GetX(void)
{
	return agk::GetTextX(_textNumber);
}

float Text::GetY(void)
{
	return agk::GetTextY(_textNumber);
}

void Text::SetAlignment(unsigned short mode)
{
	if (_Alignment(mode))
		agk::SetTextAlignment(_textNumber, mode);
}

void Text::SetCharAngle(unsigned int index, float angle)
{
	if (_Index(index))
		agk::SetTextCharAngle(_textNumber, index, angle);
}

void Text::SetCharAngleInRad(unsigned int index, float angle)
{
	if (_Index(index))
		agk::SetTextCharAngleRad(_textNumber, index, angle);
}

void Text::SetCharColor(unsigned int index, Color Value)
{
	agk::SetTextCharColor(_textNumber, index, Value.GetRed(), Value.GetGreen(), Value.GetBlue(), Value.GetAlpha());
}

void Text::SetCharColorAlpha(unsigned int index, unsigned short alpha)
{
	if (_Index(index))
	{
		if (_ColorCheck(alpha))
			agk::SetTextCharColorAlpha(_textNumber, index, alpha);
	}
}

void Text::SetCharColorBlue(unsigned int index, unsigned short blue)
{
	if (_Index(index))
	{
		if (_ColorCheck(blue))
			agk::SetTextCharColorBlue(_textNumber, index, blue);
	}
}

void Text::SetCharColorGreen(unsigned int index, unsigned short green)
{
	if (_Index(index))
	{
		if (_ColorCheck(green))
			agk::SetTextCharColorGreen(_textNumber, index, green);
	}
}

void Text::SetCharColorRed(unsigned index, unsigned short red)
{
	if (_Index(index))
	{
		if (_ColorCheck(red))
			agk::SetTextCharColorRed(_textNumber, index, red);
	}
}

void Text::SetCharX(unsigned index, float x)
{
	if (_Index(index))
		agk::SetTextCharX(_textNumber, index, x);
}

void Text::SetCharY(unsigned index, float y)
{
	if (_Index(index))
		agk::SetTextCharY(_textNumber, index, y);
}

void Text::SetColor(Color Value)
{
	agk::SetTextColor(_textNumber, Value.GetRed(), Value.GetGreen(), Value.GetBlue(), Value.GetAlpha());
}

void Text::SetColorAlpha(unsigned short alpha)
{
	if (_ColorCheck(alpha))
		agk::SetTextColorAlpha(_textNumber, alpha);
}

void Text::SetColorBlue(unsigned short blue)
{
	if (_ColorCheck(blue))
		agk::SetTextColorAlpha(_textNumber, blue);
}

void Text::SetColorGreen(unsigned short green)
{
	if (_ColorCheck(green))
		agk::SetTextColorAlpha(_textNumber, green);
}

void Text::SetColorRed(unsigned short red)
{
	if (_ColorCheck(red))
		agk::SetTextColorAlpha(_textNumber, red);
}

void Text::SetDepth(unsigned int depth)
{
	if (_Depth(depth))
		agk::SetTextDepth(_textNumber, depth);
}

void Text::SetExtendedFontImage(Image Object)
{
	agk::SetTextExtendedFontImage(_textNumber, Object.GetID());
}

void Text::SetFontImage(Image Object)
{
	agk::SetTextFontImage(_textNumber, Object.GetID());
}

void Text::SetLineSpacing(float spacing)
{
	if (_NotNegativeFloat(spacing))
		agk::SetTextLineSpacing(_textNumber, spacing);
}

void Text::SetMaxWidth(float width)
{
	if (_NotNegativeFloat(width))
		agk::SetTextMaxWidth(_textNumber, width);
}

void Text::SetPosition(RFTPoint Location)
{
	agk::SetTextPosition(_textNumber, Location.GetX(), Location.GetY());
}

void Text::SetPrintColor(Color Value)
{
	agk::SetPrintColor(Value.GetRed(), Value.GetGreen(), Value.GetBlue(), Value.GetAlpha());
}

void Text::SetPrintSize(float size)
{
	if (_NotNegativeFloat(size))
		agk::SetPrintSize(size);
}

void Text::SetPrintSpacing(float space)
{
	if (_NotNegativeFloat(space))
		agk::SetPrintSpacing(space);
}

void Text::SetScissor(RFTPoint TopLeft, RFTPoint BottomRight)
{
	agk::SetTextScissor(_textNumber, TopLeft.GetX(), TopLeft.GetY(), BottomRight.GetX(), BottomRight.GetY());
}

void Text::SetSize(float size)
{
	if (_NotNegativeFloat(size))
		agk::SetTextSize(_textNumber, size);
}

void Text::SetSpacing(float spacing)
{
	if (_NotNegativeFloat(spacing))
	{
		if (_canBeSeen)
			agk::SetTextSpacing(_textNumber, spacing);
	}
}

void Text::SetString(const char* string)
{
	_storedString = string;

	if (_canBeSeen)
		agk::SetTextString(_textNumber, string);
}

void Text::SetString(std::string newString)
{
	_storedString = newString;

	if (_canBeSeen)
		agk::SetTextString(_textNumber, newString.c_str());
}

void Text::SetVisible(bool visible)
{
	if (visible)
		agk::SetTextVisible(_textNumber, 1);
	else
		agk::SetTextVisible(_textNumber, 0);
}

void Text::SetX(float x)
{
	agk::SetTextX(_textNumber, x);
}

void Text::SetY(float y)
{
	agk::SetTextY(_textNumber, y);
}

bool Text::SplitAtDelimeter(Text *Part1, Text *Part2, char delimeter)
{
	AGKCore Converter;
	short leftIndex = GetDelimiterIndex(delimeter);
	short rightIndex = Converter.Len(*this) - leftIndex -	1;
	//short j = 0;

	if (leftIndex == -1)
		return false;



	Part1->SetString(Converter.Left(*this, leftIndex).GetCString());
	Part2->SetString(Converter.Right(*this, rightIndex).GetCString());
	/*for (int i = 0; i < index; i++)
		Part1->_storedString[i] = _storedString[i];

	Part1->_storedString[index] = '\0';

	for (unsigned int i = index + 1; i < GetLength(); i++)
		Part2->_storedString[j++] = _storedString[i];

	Part2->_storedString[j] = '\0';
	*/

	return true;
}

bool Text::_Alignment(unsigned short mode)
{
	if (mode < 3)
		return true;
	
	return false;
}

bool Text::_ColorCheck(unsigned short value)
{
	if (value > 255)
		return false;

	return true;
} 

bool Text::_Depth(unsigned int number)
{
	if (number > 10000)
		return false;

	return true;
}

bool Text::_Index(unsigned int value)
{
    if (value < GetLength())
			return true;

	return false;
}

bool Text::_NotNegativeFloat(float value)
{
	if (value >= 0.0f)
		return true;

	return false;
}