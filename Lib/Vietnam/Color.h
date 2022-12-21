#pragma once

class Color
{
public:
	Color(void);
	Color(unsigned short redValue, unsigned short greenValue, unsigned short blueValue, unsigned short alphaValue = 255);
	~Color(void);

	unsigned short GetAlpha(void);
	unsigned short GetBlue(void);
	unsigned short GetGreen(void);
	unsigned short GetRed(void);
		
	void SetAlpha(unsigned short value);
	void SetBlue(unsigned short value);
	void SetGreen(unsigned short value);
	void SetRed(unsigned short value);

private:
	unsigned short _alpha;
	unsigned short _blue;
	unsigned short _green;
	unsigned short _red;

	bool _Check(unsigned short value);
};
