#include "FileZip.h"
#include "Text.h"
#include "agk.h"

Zip::Zip()
: File()
{

}

Zip::Zip(Text Filename)
: File()
{
	_Create(Filename);
}

Zip::Zip(Text ZipFilePathAndName, Text ExtractLocation)
: File()
{
	//check to make sure file exists
	if (_GetExists(ZipFilePathAndName))
		_Extract(ZipFilePathAndName, ExtractLocation);
}

Zip::~Zip()
{

}

///////////////////////////////
// Adds a local file into the zip file. 
// The path variable is the path to the local file,
// the zipPath variable is the path that will be used inside the zip file, 
// this is the only way to add folders to the zip file (by adding a file with a zipPath such as "folder1/myfile.txt").
// The local file path is relative to the current directory set using SetCurrentDir unless you start the path with a forward slash, 
// in which case the path will be relative to the root of the write directory on the current platform.
////////////////////////////////
void Zip::AddEntry(Text PathPlusFilename, Text PathForZip)
{
	//check to make sure file exists
	if (_GetExists(PathPlusFilename))
		//add to archive
		agk::AddZipEntry(_fileID, PathPlusFilename.GetCString(), PathForZip.GetCString());
}

////////////////////////////////
// Closes a zip file opened with CreateZip. 
// This finalizes the zip and allows it to be opened for extraction.
////////////////////////////////
void Zip::Close()
{
	agk::CloseZip(_fileID);
}

////////////////////////////////
// Creates a zip file at the specified location and opens it ready for files to be added. 
// Files cannot be read or extracted from a zip file using this command. 
// Use ExtractZip to retrieve files from it.
// The file path is relative to the current directory set using SetCurrentDir unless you start the path with a forward slash, 
// in which case the path will be relative to the root of the write directory on the current platform.
///////////////////////////////
void Zip::_Create(Text Filename)
{
	_fileID = agk::CreateZip(Filename.GetCString());
}

////////////////////////////////
// Extracts a zip file to a specified directory. 
// Any folders created inside the zip file will be created in the extraction process.
// The local file path is relative to the current directory set using SetCurrentDir unless you start the path with a forward slash, 
// in which case the path will be relative to the root of the write directory on the current platform.
/////////////////////////////////
void Zip::_Extract(Text ZipFilenamePath, Text ExtractPath)
{
	//check to make sure file exists
	if (_GetExists(ZipFilenamePath))
		agk::ExtractZip(ZipFilenamePath.GetCString(), ExtractPath.GetCString());
}