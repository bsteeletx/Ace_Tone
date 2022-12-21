#pragma once

#include "Image.h"

class Capture : Image
{
public:
	Capture();
	~Capture();

	unsigned short Get(); 

	bool IsCapturing(); 

	bool ShowScreen();
};