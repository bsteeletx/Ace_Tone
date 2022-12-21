#pragma once

#include "Defines.h"
#include "Image.h"
#include "Text.h"

class Notification
{
public:
	Notification();
	~Notification(void);
#if (OS != WINDOWS)
	Notification(Text DateTime, Text Message, Text Data);
	
	bool Get(void);
	Text GetData(void);
	int GetType(void);

	void Reset(void);

	void SetImage(Image Object);
	void SetText(Text Object);

private:
	//void _Create(Text DateTime, Text Message, Text Data);
#endif
};

