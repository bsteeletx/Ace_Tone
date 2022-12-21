#include "FileRead.h"
#include "Text.h"
#include "agk.h"

Read::Read()
: File()
{

}

Read::Read(Text Filename)
: File(true, Filename)
{

}

Read::~Read()
{

}

/***************
** Returns true if file has reached the end of its data stream, 0 otherwise
*/////////////
bool Read::IsEOF()
{
	return (bool)agk::FileEOF(_fileID);
}

/*********************
** Reads a 1 byte unsigned integer (0-255)
*///////////////////////
unsigned short Read::Byte()
{
	return agk::ReadByte(_fileID);
}

/******************
** Reads a 4 byte float from the given file
*/////////////////
float Read::Float()
{
	return agk::ReadFloat(_fileID);
}

/**********************
** Reads a 4 byte integer from the given file
*/////////////////////
int Read::Integer()
{
	return agk::ReadInteger(_fileID);
}

/***************************
** Reads a CR(\n) terminated string from the given file
*//////////////////////////
Text Read::Line()
{
	//AGK says I have to delete the string after using it--hopefully closing out the brace does that?
	std::string temp = agk::ReadLine(_fileID);
	Text Temp = Text(temp);

	return Temp;
}

/**********************************
** Reads a null terminated string from the given file
*////////////////////////////////
Text Read::String()
{
	//AGK says I have to delete the string after using it--hopefully closing out the brace does that?
	std::string temp = agk::ReadString(_fileID);
	Text Temp = Text(temp);

	return Temp;
}