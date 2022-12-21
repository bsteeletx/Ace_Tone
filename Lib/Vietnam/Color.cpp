#include "Color.h"

Color::Color(void)
{
	_alpha = 0;
	_blue = 0;
	_green = 0;
	_red = 0;
}

Color::Color(unsigned short redValue, unsigned short greenValue, unsigned short blueValue, unsigned short alphaValue)
{
	if (_Check(redValue))
	{
		if (_Check(greenValue))
		{
			if (_Check(blueValue))
			{
				if (_Check(alphaValue))
				{
					_alpha = alphaValue;
					_blue = blueValue;
					_green = greenValue;
					_red = redValue;
				}
			}
		}
	}
}

Color::~Color(void)
{
}

unsigned short Color::GetAlpha(void)
{
	return _alpha;
}

unsigned short Color::GetBlue(void)
{
	return _blue;
}

unsigned short Color::GetGreen(void)
{
	return _green;
}

unsigned short Color::GetRed(void)
{
	return _red;
}

void Color::SetAlpha(unsigned short value)
{
	if (_Check(value))
		_alpha = value;
}

void Color::SetBlue(unsigned short value)
{
	if (_Check(value))
		_blue = value;
}

void Color::SetGreen(unsigned short value)
{
	if (_Check(value))
		_green = value;
}

void Color::SetRed(unsigned short value)
{
	if (_Check(value))
		_red = value;
}

bool Color::_Check(unsigned short value)
{
	if (value > 255)
		return false;

	return true;
}
