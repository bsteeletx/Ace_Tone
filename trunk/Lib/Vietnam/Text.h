#ifndef _TEXT_H_
#define _TEXT_H_

//#include "Point.h"
#include "Color.h"
//#include "Image.h"
#include <string>

class Image;
class RFTPoint;

class Text
{
public:
	Text();
	~Text();
	Text(const char* textString, bool isVisible = false);
	Text(char singleChar, bool isVisible = false);
	//Text(unsigned int assignedTextNumber, const char* textString, bool isVisible = false);
	Text(std::string textString, bool isVisible = false);
	
	//Text& operator= (const Text& newText);
	Text& operator+= (Text addText);
	bool operator== (Text otherText);
	bool operator!= (const Text otherText);

	void Delete();
		
	void FixToScreen(bool toScreen);
	int FoundNeedle(const char needle);

	char GetChar(unsigned int index);
	float GetCharAngle(unsigned int index);
	float GetCharAngleInRad(unsigned int index);
	unsigned short GetCharColorAlpha(unsigned int index);
	unsigned short GetCharColorBlue(unsigned int index);
	unsigned short GetCharColorGreen(unsigned int index);
	unsigned short GetCharColorRed(unsigned int index);
	float GetCharX(unsigned int index);
	float GetCharY(unsigned int index);
	unsigned short GetColorAlpha(void);
	unsigned short GetColorBlue(void);
	unsigned short GetColorGreen(void);
	unsigned short GetColorRed(void);
	const char *GetCString(void);
	unsigned int GetDepth(void);
	short GetDelimiterIndex(char separator);
	bool GetExists(void);
	bool GetHitTest(RFTPoint Location);
	unsigned int GetID(void);
	unsigned int GetLength(void);
	float GetLineSpacing(void);
	unsigned int GetNextID(void);
	float GetSize(void);
	float GetSpacing(void);
	std::string GetString(void);
	float GetTotalHeight(void);
	float GetTotalWidth(void);
	bool GetVisible(void);
	float GetX();
	float GetY();

	void SetAlignment(unsigned short mode);
	void SetCharAngle(unsigned int index, float angle);
	void SetCharAngleInRad(unsigned int index, float angle);
	void SetCharColor(unsigned int index, Color CharColor);
	void SetCharColorAlpha(unsigned int index, unsigned short alpha);
	void SetCharColorBlue(unsigned int index, unsigned short blue);
	void SetCharColorGreen(unsigned int index, unsigned short green);
	void SetCharColorRed(unsigned int index, unsigned short red);
	void SetCharPosition(unsigned int index, RFTPoint Location);
	void SetCharX(unsigned int index, float x);
	void SetCharY(unsigned int index, float y);
	void SetColor(Color TextColor);
	void SetColorAlpha(unsigned short alpha);
	void SetColorBlue(unsigned short blue);
	void SetColorGreen(unsigned short green);
	void SetColorRed(unsigned short red);
	void SetDefaultExtendedFontImage(Image Object);
	void SetDepth(unsigned int depth);
	void SetExtendedFontImage(Image Object);
	void SetFontImage(Image Object);
	void SetLineSpacing(float spacing);
	void SetMaxWidth(float width);
	void SetPosition(RFTPoint Location);
	void SetPrintColor(Color PrintColor);
	void SetPrintSize(float size);
	void SetPrintSpacing(float space);
	void SetScissor(RFTPoint TopLeft, RFTPoint BottomRight);
	void SetSize(float size);
	void SetSpacing(float spacing);
	void SetString(const char* string);
	void SetString(std::string string);
	void SetVisible(bool visible);
	void SetX(float x);
	void SetY(float y);
	bool SplitAtDelimeter(Text *Part1, Text *Part2, char delimeter);

	enum Alignment
	{
		LEFT,
		CENTER,
		RIGHT
	};

protected:
	bool _canBeSeen;
	unsigned int _textNumber;
	std::string _storedString;
	
	bool _Alignment(unsigned short mode);
	bool _ColorCheck(unsigned short value);
	bool _Depth(unsigned int value);
	bool _Index(unsigned int value);
	bool _NotNegativeFloat(float value);
};
#endif