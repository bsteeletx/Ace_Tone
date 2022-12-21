#pragma once

#include "Text.h"

class Error
{
public:
	Error(void);
	~Error(void);

	Text GetLast(void);
	bool GetOccurred(void);

	void Log(Text Error);
	
	void SetMode(unsigned short mode);
};

