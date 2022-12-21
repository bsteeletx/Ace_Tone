#ifndef _FILEZIP_H_
#define _FILEZIP_H_

#include "File.h"

class Zip : public File
{
public:
	Zip();
	Zip(Text Filename);
	Zip(Text ZipFilePathAndName, Text ExtractLocation);
	~Zip();

	void AddEntry(Text FilePathAndFileName, Text PathForZip);
	void Close();
	
private:

	void _Create(Text Filename); 
	
	void _Extract(Text ZipFilePathAndName, Text ExtractLocation);
};
#endif