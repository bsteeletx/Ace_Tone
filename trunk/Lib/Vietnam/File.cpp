#include "File.h"
#include "Text.h"
#include "agk.h"

File::File()
{
	_fileID = 0;
	_openToRead = true;
}

File::~File()
{
}

File::File(bool read, Text Filename)
{
	if (_GetExists(Filename) == 1)
	{
		_Open(read, Filename);
		_nameOfFile = Filename.GetString();
	}
}

File& File::operator= (const File &NewFile)
{
	File ReturnFile(NewFile);
	
	if (this != &NewFile)
	{
		if (_fileID)
			Close();
		
		this->_fileID = NewFile._fileID;
		this->_openToRead = NewFile._openToRead;
		this->_nameOfFile = NewFile._nameOfFile;
	}

	return *this;
}

//////////////////////////////////////////////////
// Presents the user with an option to choose a file stored on their current platform (Windows/Mac only), 
// for example a photo or sound file. 
// If the user cancels the operation an empty string will be returned, 
// otherwise the file will be copied to the apps current directory and the filename returned so that it can be used by your app.
// You may specify an optional extension filter to limit the types of files the user will see when browsing.
// For example using an extension filter of "*.wav" would limit the user to choosing.wav files.
// For multiple extensions separate them with a semicolon like so "*.wav;*.mp3;*.png".
// the returned string must be deleted when you are finished with it, 
// even if it is an empty string.
// A null string will not be returned.
//////////////////////////////////////////////////////
Text File::ChooseRaw(Text ValidExtensions)
{
	return Text(agk::ChooseRawFile(ValidExtensions.GetCString()));
}

void File::Close(void)
{
	agk::CloseFile(_fileID);
}

void File::Delete(Text Filename)
{
	agk::DeleteFile(Filename.GetCString());
}
///////////////////////////////////////////////////
// Deletes a folder at the current path. 
// This is determined by the command SetFolder or SetCurrentDir. 
// The folder must be empty for this command to succeed.
////////////////////////////////////////////////////
void File::DeleteFolder(Text FolderName)
{
	agk::DeleteFolder(FolderName.GetCString());
}

int File::GetID(void)
{
	return _fileID;
}

///////////////////////////////////////
// Returns the name of the first file found in the current folder, 
// which is set using SetFolder.
// You can call GetNextFile to continue down the list of files in the current folder.
// Returns an empty string if there are no files in the current folder.
/////////////////////////////////////////
Text File::GetFirst(void)
{
	return Text(agk::GetFirstFile());
}

//////////////////////////////////////////
// Returns the name of the first folder found in the current folder, 
// which is set using SetFolder. 
// You can call GetNextFolder to continue down the list of folders in the current folder. 
// Returns an empty string if there are no folders in the current folder. 
// Does not include . or .. 
// Note that there is a known limitation on Android that any folders within the "assets" folder cannot be found using this command. 
// You may be able to work around this by using MakeFolder to create the same folder structure in the write folder which AGK can then use to find files in the assets folder with GetFirstFile.
/////////////////////////////////////////
Text File::GetFirstFolder(void)
{
	return Text(agk::GetFirstFolder());
}

//////////////////////////////////////////
// Returns the current folder previously set with SetFolder. 
// The returned path will always have a slash as the final character excpet when in the root folder in which case an empty string will be returned.
/////////////////////////////////////////
Text File::GetFolder(void)
{
	return Text(agk::GetFolder());
}

////////////////////////////////////////////
// Returns the name of the next file found in the current folder, 
// which is set using SetFolder. 
// GetFirstFile must have been called first for this to work, 
// any call to SetFolder or OpenToWrite will require starting again with GetFirstFile.
// Returns an empty string if there are no more files in the current folder.
/////////////////////////////////////////////
Text File::GetNext(void)
{
	return Text(agk::GetNextFile());
}

//////////////////////////////////////////////
// Returns the name of the next folder found in the current folder, which is set using SetFolder. 
// GetFirstFolder must have been called first for this to work, 
// any call to SetCurrentDir or OpenToWrite will require starting again with GetFirstFolder.
// Returns an empty string if there are no more folders in the current folder.
// Does not include.or ..
///////////////////////////////////////////////
Text File::GetNextFolder(void)
{
	return Text(agk::GetNextFolder());
}

//////////////////////////////////////////
// Returns the directory that contains the application executable on the current plaform that the app is running on,
// OR the directory that new files will be written to on the current plaform that the app is running on
////////////////////////////////////////////
Text File::GetPath(void)
{
	if (_openToRead)
		return Text(agk::GetReadPath());

	return Text(agk::GetWritePath());
}

///////////////////////////////////
// Returns the size in bytes of the opened file.
///////////////////////////////////
unsigned int File::GetSize(void)
{
	return agk::GetFileSize(_fileID);
}

///////////////////////////////////
// Creates a folder at the current path. 
// This is determined by the command SetFolder or SetCurrentDir.
// AGK Command retuns an integer,
// but documentation does not say what the integer is for
///////////////////////////////////
void File::MakeFolder(Text Name)
{
	agk::MakeFolder(Name.GetCString());
}

//////////////////////////////////
// Reopens a file
// checks to see if it's still open first
/////////////////////////////////
void File::ReOpen()
{
	if (!_IsOpen())
		_Open(_openToRead, _nameOfFile);
}

///////////////////////////////////
// Only two folders are accessible to your AGK app; 
// the read folder and the write folder. 
// The read folder is the location of your executable and includes the media folder. 
// The write folder (which also has read permission), 
// is located in a platform safe location and is different depending on the device. 
// On Windows, for example, 
// the default write location is C:\users\username\Documents\AGK\appName. 
// These are your root folders. 
// Any files created/written using OpenToWrite will be saved into the write folder. 
// For simplicity, 
// AGK merges these two read and write folders into a single command set. 
// What this means is that when you attempt to open or load a file, 
// AGK will first look in the write folder before looking in the read folder. 
// Windows has the unique command SetRawWritePath that allows you to overwrite this behavior, 
// but is not recommended as it is not compatible with any other platform and Windows users may even require administrator privileges. 
// When setting the folder, 
// its behavior is what you'd expect from the CD command in the Windows console; 
// It works from the current directory. 
// For instance, 
// if the current root read folder is C:\games\myApp\ then SetFolder("images") will put you in C:\games\myApp\images. 
// Calling the command a second time SetFolder("backgrounds") will place you at C:\games\myApp\images\backgrounds\. 
// There are two ways to return to the root path. 
// The first is to call SetFolder("") using an empty string. 
// The other is to preceed your path with a forward slash, 
// SetFolder("/stuff"). 
// This also applies to loading your files with other commands as well. 
// Assume you're still located in the images\backgrounds folders and you want to load bk.png located in the root folder. 
// You can simply say LoadImage("/bk.png"). 
// Setting the path to a folder that does not exist will create that folder in the write path. 
// By default, 
// AGK calls SetFolder("media") as the first thing it does. 
// This command returns 1 on success or 0 if you use an invalid path such as SetFolder("C:\"). 
// Note: It is important to remember when setting paths to always use forward slashes instead of backslash. 
// AGK will convert them into the appropriate file separator for the given platform.
///////////////////////////////////////
bool File::SetFolder(Text Folder)
{
	return (bool)agk::SetFolder(Folder.GetCString());
}



bool File::_IsOpen(void)
{
	if (agk::FileIsOpen(_fileID) == 1)
		return true;

	return false;
}

void File::_Open(bool read, Text Filename)
{
	if (read)
		_fileID = agk::OpenToRead(Filename.GetCString());
	else
		_fileID = agk::OpenToWrite(Filename.GetCString());

	_openToRead = read;
}


bool File::_GetExists(Text Filename)
{
	if (agk::GetFileExists(Filename.GetCString()) == 1)
		return true;

	return false;
}