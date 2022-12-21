#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "Point.h"
#include "Color.h"
#include "FileRead.h"
#include "Memblock.h"
#include <vector>

class Text;
class Memblock;
class Color;
class Read;

class Image
{
public:
	//constructors/deconstructors
	~Image(void);
	Image(void);
	//Image (unsigned int assignedImageNumber, Text Filename);
	Image (unsigned int copyImageNumber);
	Image (RFTPoint Begin, RFTPoint End);
	Image (Text EncodedText, unsigned short codeForgiveness);
	Image (Text Filename); 
	//Image (unsigned int assignedImageNumber, Text Filename, bool blackIsAlpha = false);
	Image(unsigned int parentImage, Text SubImageFilename);
	//Image (unsigned int assignedImageumber, unsigned int parentImage, Text SubImageFilename);
	Image (Read FileToInit, Text PathToParent);
	Image (Memblock Generator);
	Image(RFTPoint TopLeft, float width, float height);
	Image (unsigned int imageNumber, RFTPoint Begin, RFTPoint End);
	
	//operators
	Image& operator= (const Image& newImage);
	
	//////////////////////General

	void Delete();
	
	bool GetExists(void);
	Text GetFilename(void);
	float GetHeight(void);
	unsigned int GetID(void);
	float GetWidth(void);

	void Print(float percentSize); 

	void Save(Text savedFilename); 
	void SetMagFilter(bool linear);
	void SetMask(unsigned int sourceImageID, ColorChannel DestinationChannel, ColorChannel SourceChannel, RFTPoint Offset); 
	void SetMinFilter(bool linear);
	void SetSavePixels(bool turnOn);
	//void SetTransparentColor(Color TransparentColor); //Not working yet
	void SetWrapU(bool repeat);
	void SetWrapV(bool repeat);

	/////////////////////QR
	Text DecodeQR(); 
		
private:
	void _Get(RFTPoint TopLeft, float width, float height);

	bool _ImageNumber(unsigned int number);
	
	void _Load(Text Filename, bool blackIsAlpha = false);
	void _Load(unsigned int assignedImageNumber, Text Filename, bool blackIsAlpha = false);
	void _LoadSub(unsigned int parentImage, Text SubImageFilename);
	void _LoadSub(unsigned int assignedImageNumber, unsigned int parentImage, Text subImageFilename);

	//bool _ParentNumber(unsigned int number);
	static std::vector<Text> _ParentImages;
	static std::vector<Text> _NonParentFileNames;
	static std::vector<unsigned int> _parentImageNumbers;
	static std::vector<unsigned int> _nonParentImageNumbers;

protected:
	bool _ColorChannel(short value);
	bool _Filename(Text filename);
	unsigned int _imageNumber;
};
#endif