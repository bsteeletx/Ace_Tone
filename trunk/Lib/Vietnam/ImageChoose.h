#pragma once

#include "Image.h"

class Choose : Image
{
public:
	Choose();
	~Choose();

private:	
	unsigned short _Get();

	bool _IsChoosing();

	bool _ShowScreen();
};