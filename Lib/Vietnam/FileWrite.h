#ifndef _FILE_WRITE_H_
#define _FILE_WRITE_H_

#include "File.h"

class Write : public File
{
public:
	Write();
	Write(Text Filename);
	~Write();

	void Byte(unsigned short value);
	
	void Delete(Text FileName);
	
	void Float(float value);
	
	void Integer(int value);
	
	void Line(Text Line);
	
#if OS == WINDOWS
	void SetRawPath(Text Path);
#endif
	void String(Text String);

};
#endif