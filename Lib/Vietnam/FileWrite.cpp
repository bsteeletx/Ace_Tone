#include "FileWrite.h"
#include "Text.h"
#include "agk.h"

Write::Write()
: File()
{

}

Write::Write(Text Filename)
: File(false, Filename)
{

}

Write::~Write()
{

}

/////////////////////////////////
// Writes a 1 byte unsigned integer (0-255) to the given file
// Not Human Readable
//////////////////////////////////
void Write::Byte(unsigned short value)
{
	//not allowed to be greater than 255
	if (value < 256)
		agk::WriteByte(_fileID, value);
}

///////////////////////////////
// Deletes a given file from the write folder. 
// File paths must be relative, not absolute, you cannot delete files from the application folder or from elsewhere on the disk.
///////////////////////////////
void Write::Delete(Text Filename)
{
	if (_GetExists(Filename))
		agk::DeleteFile(Filename.GetCString());
}

/////////////////////////////////
// Writes a 4 byte float to the given file
// Not Human Readable
////////////////////////////////
void Write::Float(float value)
{
	agk::WriteFloat(_fileID, value);
}

/////////////////////////////////
// Writes a 4 byte integer to the given file
// Not Human Readable
////////////////////////////////
void Write::Integer(int value)
{
	agk::WriteInteger(_fileID, value);
}

///////////////////////////////////
// Writes a CR(\n) terminated string to the given file
///////////////////////////////////
void Write::Line(Text Value)
{
	agk::WriteLine(_fileID, Value.GetCString());
}

#if OS == WINDOWS
///////////////////////////////////
// Sets the folder where files created by AGK will be stored.
/////////////////////////////////
void Write::SetRawPath(Text Path)
{
	agk::SetRawWritePath(Path.GetCString());
}
#endif

///////////////////////////////////
// Writes a null terminated string to the given file
// not meant for human readable files and should only be used for files that will later be read with ReadString
////////////////////////////////
void Write::String(Text Value)
{
	agk::WriteString(_fileID, Value.GetCString());
}