#ifndef _FILE_H_
#define _FILE_H_


//#include "Text.h"
#include <string>

class Text;

class File
{
public:
	File();
	~File(void);
	File(bool read, Text Filename);

	File &operator= (const File &NewFile);

	Text ChooseRaw(Text ValidExtensions);
	void Close();
	
	void Delete(Text FileName);
	void DeleteFolder(Text FolderName);

	int GetID(void);
	Text GetFirst(void);
	Text GetFirstFolder(void);
	Text GetFolder(void);
	Text GetNext(void);
	Text GetNextFolder(void);
	Text GetPath(void);
	unsigned int GetSize(void);	

	void MakeFolder(Text Name);

	void ReOpen();
	
	bool SetFolder(Text Folder);

protected:
	unsigned int _fileID;
	bool _openToRead;
	std::string _nameOfFile;

	bool _GetExists(Text Filename);
	bool _IsOpen(void);
	void _Open(bool read, Text Filename);
};
#endif