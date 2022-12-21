#include "Image.h"
#include "agk.h"
#include "Text.h"

std::vector<Text> Image::_ParentImages;
std::vector<unsigned int> Image::_parentImageNumbers;
std::vector<Text> Image::_NonParentFileNames;
std::vector<unsigned int> Image::_nonParentImageNumbers;

Image::~Image(void)
{
	//if (GetExists())
		//agk::DeleteImage(_imageNumber);
}

Image::Image()
{
	_imageNumber = 0;
}

Image::Image(unsigned int copyImageNumber)
{
	_imageNumber = agk::LoadImage(agk::GetImageFilename(copyImageNumber));
}

/*Image::Image(unsigned int assignedImageNumber, Text Filename)
{
	if (agk::GetFileExists(Filename.GetCString()))
		agk::LoadImage(assignedImageNumber, Filename.GetCString());
} */

Image::Image(Text filename)
{
	if (_Filename(filename))
		_Load(filename, false);
}

/*Image::Image(unsigned int assignedImageNumber, Text filename, bool blackIsAlpha)
{
	if (_ImageNumber(assignedImageNumber))
	{
		if (_Filename(filename))
			_Load(assignedImageNumber, filename, blackIsAlpha);
	}
} */

Image::Image(unsigned int parentImage, Text subImageFilename)
{
	if (_Filename(subImageFilename))
		_LoadSub(parentImage, subImageFilename);
}

/*Image::Image(unsigned int assignedImageNumber, unsigned int parentImage, Text subImageFilename)
{
	if (_Filename(subImageFilename))
		_LoadSub(parentImage, subImageFilename);
} */

Image& Image::operator= (const Image& newImage)
{
	_imageNumber = newImage._imageNumber;

	return *this;
}

Image::Image(unsigned int imageNumber, RFTPoint Begin, RFTPoint End)
{
	_imageNumber = agk::CopyImage(imageNumber, (int) Begin.GetX(), (int) Begin.GetY(), (int) End.GetX(), (int) End.GetY());
}

Image::Image(Text codedText, unsigned short codeForgiveness)
{
	_imageNumber = agk::EncodeQRCode(codedText.GetCString(), codeForgiveness); 
}

Image::Image(Read FileToInit, Text PathToParent)
{
	Text ParentImage = PathToParent;
	Text Filename("");
	bool alreadyLoaded = false;

	while(!FileToInit.IsEOF())
	{
		Text Line = FileToInit.Line();
		Text Start;
		Text End;

		Line.SplitAtDelimeter(&Start, &End, ':');

		if (Start == Text("PathFile"))
			Filename = End;
		
		if (Filename != Text(""))
			break;
	}

	//no parent image, bad doggy! no treat for you!
	if (ParentImage == Text(""))
	{
		for (unsigned int i = 0; i < _NonParentFileNames.size(); i++)
		{
			if (_NonParentFileNames[i] == Filename)
			{
				_imageNumber = _nonParentImageNumbers[i];
				return;
			}
		}
		
		_imageNumber = agk::LoadImage(Filename.GetCString());
		_nonParentImageNumbers.push_back(_imageNumber);
		_NonParentFileNames.push_back(Filename);
	}
	else
	{
		//check to see if we've already loaded the parent image in memory
		for (unsigned int i = 0; i < _ParentImages.size(); i++)
		{
			//checking each individual element
			if (_ParentImages[i] == ParentImage)
			{
				_imageNumber = agk::LoadSubImage(_parentImageNumbers[i], Filename.GetCString());
				alreadyLoaded = true;
				_nonParentImageNumbers.push_back(_imageNumber);
				_NonParentFileNames.push_back(Filename);
				break; //found it, so break out of for
			}

		}

		if (!alreadyLoaded)
		{
			//load the parental image into the static variables
			_ParentImages.push_back(ParentImage);
			_parentImageNumbers.push_back(agk::LoadImage(ParentImage.GetCString()));
			//then load the subimage
			_imageNumber = agk::LoadSubImage(_parentImageNumbers.back(), Filename.GetCString());
			_nonParentImageNumbers.push_back(_imageNumber);
			_NonParentFileNames.push_back(Filename);
		}
	}
	FileToInit.Close();
}

Image::Image(Memblock Generator)
{
	agk::CreateImageFromMemblock(Generator.GetID());
}

Image::Image(RFTPoint TopLeft, float width, float height)
{
	_Get(TopLeft, width, height);
}

Text Image::DecodeQR(void)
{
	return agk::DecodeQRCode(_imageNumber);
}


void Image::Delete()
{
	agk::DeleteImage(_imageNumber);
}

bool Image::GetExists(void)
{
	if (agk::GetImageExists(_imageNumber))
		return true;
	else
		return false;
}

Text Image::GetFilename(void)
{
	return agk::GetImageFilename(_imageNumber);
}

float Image::GetHeight(void)
{
	return agk::GetImageHeight(_imageNumber);
}

unsigned int Image::GetID(void)
{
	return _imageNumber;
}

float Image::GetWidth(void)
{
	return agk::GetImageWidth(_imageNumber);
}

void Image::Print(float percentSize)
{
	agk::PrintImage(_imageNumber, percentSize);
}

void Image::Save(Text savedFilename)
{
	if (_Filename(savedFilename))
		agk::SaveImage(_imageNumber, savedFilename.GetCString());
}

void Image::SetMagFilter(bool linear)
{
	if (linear)
		agk::SetImageMagFilter(_imageNumber, 1);
	else
		agk::SetImageMagFilter(_imageNumber, 0);
}

///////////////////////////////////
// Copies a color channel from one image to another. 
// You can specify the source and destination channels using the values ColorChannel enum to represent red,green,blue,alpha respectively.
// This is a slow command and should not be called every frame.
// The offset value allows you to offset the source image on te destination image so a small source image can be used to mask any part of a large image.
// Any part of the large image outside the size of the small image will be left unchanged.
// negative offset values are supported to shift the source image off the top left of the destination image.
////////////////////////////////////
void Image::SetMask(unsigned int sourceImageID, ColorChannel DestinationChannel, ColorChannel SourceChannel, RFTPoint Offset)
{
	agk::SetImageMask(_imageNumber, sourceImageID, DestinationChannel, SourceChannel, Offset.GetX(), Offset.GetY());
}

void Image::SetMinFilter(bool linear)
{
	if (linear)
		agk::SetImageMinFilter(_imageNumber, 1);
	else
		agk::SetImageMinFilter(_imageNumber, 0);
}

/////////////////////////////
// By default image pixel data is compressed and saved in RAM so that future image manipulation commands have direct access to the pixel data. 
// If you do not use the image manipulation commands like CopyImage, SetImageMask, etc, or use them infrequently then you can turn this off to fall back to a slower method of getting the pixel data (from the GPU) and save some memory instead.
/////////////////////////////
void Image::SetSavePixels(bool turnOn)
{
	if (turnOn)
		agk::SetImageSavePixels(1);
	else
		agk::SetImageSavePixels(0);
}

////////Not Working Yet
/*
/////////////////////////////////
// Turns a particular color completely transparent in the chosen image. 
// This is a slow command and should not be called every frame.
////////////////////////////////
void Image::SetTransparentColor(Color TransparentColor)
{
	agk::SetImageTransparentColor(_imageNumber, TransparentColor.GetRed(), TransparentColor.GetGreen(), TransparentColor.GetBlue());
} */

void Image::SetWrapU(bool repeat)
{
	if (repeat)
		agk::SetImageWrapU(_imageNumber, 1);
	else
		agk::SetImageWrapU(_imageNumber, 0);
}

void Image::SetWrapV(bool repeat)
{
	if (repeat)
		agk::SetImageWrapV(_imageNumber, 1);
	else
		agk::SetImageWrapV(_imageNumber, 0);
}

void Image::_Load(Text filename, bool blackIsAlpha)
{
	_imageNumber = agk::LoadImage(filename.GetCString(), blackIsAlpha);
}

void Image::_Load(unsigned int assignedImageNumber, Text filename, bool blackIsAlpha)
{
	agk::LoadImage(assignedImageNumber, filename.GetCString(), blackIsAlpha);
	_imageNumber = assignedImageNumber;
}

void Image::_LoadSub(unsigned int parentImage, Text subImageFilename)
{
	_imageNumber = agk::LoadSubImage(parentImage, subImageFilename.GetCString());
}

void Image::_LoadSub(unsigned int assignedImageNumber, unsigned int parentImage, Text subImageFilename)
{
	agk::LoadSubImage(assignedImageNumber, parentImage, subImageFilename.GetCString());
	_imageNumber = assignedImageNumber;
}

bool Image::_ColorChannel(short value)
{
	if (value > 0)
	{
		if (value < 5)
			return true;
	}

	return false;
}

bool Image::_Filename(Text filename)
{
	char tempFilename[8] = {NULL};
	short lengthOfString = filename.GetLength() - 1;

	for (int i = 3; i > -1; i--)
		tempFilename[3-i] = filename.GetChar(lengthOfString - i);

	if (strcmp(tempFilename, ".jpg") == 0) //equal
		return true;
	if (strcmp(tempFilename, ".png") == 0) //equal
		return true;

	return false;
}

/////////////////////////////////////
// Grabs a portion of the backbuffer and creates a new image from it. 
// The position and size values must be in screen coordinates. 
// Returns the ID of the new image, 
// this must be deleted when you are done with it. 
// To use this command effectively you must know how AGK draws to the back buffer. 
// When Sync is called AGK updates the positions of all objects with Update, 
// then draws them all to the back buffer with Render, 
// without clearing it, 
// then displays the back buffer to the screen with Swap. 
// It then clears the back buffer and returns to your code, 
// so if you were to call GetImage immediately after Sync you would get a blank image filled with the current clear color. 
// Therefore if you want to grab an image of the current scene fully drawn you must call Render then GetImage then ClearScreen to clear the back buffer so Sync doesn't redraw everything over a fully drawn depth buffer. 
// If you are already using Update, Render, and Swap yourself instead of Sync, 
// then call GetImage between Render and Swap.
// This also allows you to do things such as drawing lines to the back buffer, 
// getting an image of the result and then clearing it so it doesn't effect what is displayed to the screen.
// Calling GetImage is a slow command and it is not recommended that it be called every frame.
// Note that the image produced by this command is not guaranteed to have the same width and height as those given to the command, 
// this is because the image is created from a portion of the screen which has a different size on different devices.
// For example, with a virtual resolution of 480x360, 
// you would get an image of the full screen by calling this command with a width of 480 and a height of 360, 
// but on an iPod this would produce an image of 480x360 pixels, 
// whilst on an iPad it would be around 1024x768 pixels.
// This should not effect how you use the image as applying it to a sprite and setting the sprite size to the same 480x360 will make the sprite fill the screen in both cases.
// It simply means that on the iPad you have a higher quality image to play with.
// This also applies to the line drawing commands, 
// drawing a line from 0, 0 to 100, 100 and then getting an image from 0, 0 to 100, 100 will produce a diagonal line image on all devices, 
// but high resolution screen devices will produce an image of higher quality containing more pixels.
// Use GetImageWidth and GetImageHeight if you need to know the actual size of the image produced in pixels.
// When drawing transparent sprites and using GetImage on them AGK has to undo the blending of the sprite with the background color to retrieve an image that can be used again in future transparent sprites.
// As such you should not call SetClearColor unless you intend to call ClearScreen immediately after it.
////////////////////////////////////
void Image::_Get(RFTPoint TopLeft, float width, float height)
{
	_imageNumber = agk::GetImage(TopLeft.GetX(), TopLeft.GetY(), width, height);
}

bool Image::_ImageNumber(unsigned int number)
{
	if (number > 0)
	{
		if (agk::GetImageExists(number))
			return true;
	}

	return false;
}