#ifndef _FILEREAD_H
#define _FILEREAD_H

#include "File.h"

class Read : public File
{
public:
	Read();
	Read(Text Filename);
	~Read();

	unsigned short Byte();
	
	float Float();
	
	int Integer();
	bool IsEOF();

	Text Line();
	
	Text String();
};
#endif