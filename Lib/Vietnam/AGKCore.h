#ifndef _AGKCORE_H_
#define _AGKCORE_H_

#include "Point.h"
#include "Color.h"
#include "Text.h"
#include "Defines.h"

class AGKCore
{
public:
	AGKCore(void);
	~AGKCore(void);

	//////////Display
	void ClearDepthBuffer(void);
	void ClearScreen(void);

	void DeleteAllImages();
	void DeleteAllSprites();
	void DeleteAllText();

	void EnableClearColor(bool clearEachFrame);
	void EnableClearDepth(bool clearEachFrame);

	unsigned short GetDeviceHeight(void);
	unsigned short GetDeviceWidth(void);
	float GetDisplayAspect(void);
	Orientation GetOrientation(void);
	unsigned int GetPolygonsDrawn(void);
	bool GetResumed(void);
	float GetScreenBoundsBottom(void);
	float GetScreenBoundsLeft(void);
	float GetScreenBoundsRight(void);
	float GetScreenBoundsTop(void);
	unsigned int GetVerticesProcessed(void);
	float GetViewOffsetX(void);
	float GetViewOffsetY(void);
	float GetViewZoom(void);
	unsigned short GetVirtualHeight(void);
	unsigned short GetVirtualWidth(void);

	void Print(int printValue, bool newLineAtEnd = true);
	void Print(float printValue, bool newLineAtEnd = true);
	void Print(Text PrintValue, bool newLineAtEnd = true);

	void Render(void);
	void Render2DBack(void);
	void Render2DFront(void);
	void Render3D(void);

	float ScreenFPS(void);
	RFTPoint ScreenToWorld(RFTPoint ScreenLoc);
	float ScreenToWorldX(float screenX);
	float ScreenToWorldY(float screenY);
	void SetBorderColor(Color BorderColor);
	void SetClearColor(Color ClearColor);
	void SetDisplayAspect(float aspect);
	void SetOrientationAllowed(bool portrait, bool revPortrait, bool landscape, bool revLandscape);
	void SetResolutionMode(bool setFullRez);
	void SetScissor(RFTPoint A, RFTPoint B); 
	void SetSyncRate(float value, bool intensiveMode); 
	void SetTransitionMode(bool slowRotate); 
	void SetVSync(bool turnOn); 
	void SetViewOffset(RFTPoint Offset); 
	void SetViewZoom(float zoom); 
	void SetViewZoomMode(bool centered);
	void SetVirtualResolution(unsigned short width, unsigned short height); 
	void Swap(void);
	void Sync(void);

	void UpdateDeviceSize(unsigned short width, unsigned short height);

	RFTPoint WorldToScreen(RFTPoint Coordinate);
	float WorldToScreenX(float worldX);
	float WorldToScreenY(float worldY);

	/////////////Strings
	unsigned int Asc(char alpha);

	Text Bin(int value);

	Text Chr(unsigned int ascii);
	unsigned int CountStringTokens(Text Original, char delimeter);

	Text GetStringToken(Text Original, char delimeter, unsigned int token);

	Text Hex(int value);

	Text Left(Text Original, unsigned int count);
	unsigned int Len(Text Test);
	Text Lower(Text Original);

	Text Mid(Text Original, unsigned int position, int length);

	Text Right(Text Original, unsigned int count);

	void SetDefaultFontImage(unsigned int fontID);
	void SetTextDefaultMagFilter(bool linear);
	void SetTextDefaultMinFilter(bool linear);
	Text Spaces(unsigned int spaceCount);
	Text Str(float value, unsigned int decimals);
	Text Str(int value);

	Text Upper(Text Original);

	int Val(Text NumberString, int base = 10);
	float ValFloat(Text NumberString);
	
	/////////////////////////////General
	void StepPhysics(float time);

	void Update(float time = 0.0f);
	void Update2D(float time = 0.0f);
	void Update3D(float time = 0.0f);

	/////////////////////////////Misc
#if OS == ANDROID
	void DownloadExpansionFile(); 
#endif
	
	Text GetAppName(void); 
	Text GetDeviceLanguage(void);
	Text GetDeviceName(); 
#if OS == ANDROID
	float GetExpansionFileProgress(); 
	ExpansionFileState GetExpansionFileState(); 
#endif
	float GetFrameTime();
	unsigned int GetMilliseconds(); 
	unsigned int GetSeconds(); 
	
	Text HTTPDecode(Text Encoded); 
	Text HTTPEncode(Text ToEncode);

	void Message(Text MesssageToDisplay); 
	
	void ResetTimer(); 

	void SetDefaultMagFilter(bool linear); 
	void SetDefaultMinFilter(bool linear); 
	void SetDefaultWrapU(bool repeat);
	void SetDefaultWrapV(bool repeat); 
#if OS == ANDROID
	void SetExpansionFileVersion(int version); 
#endif
	void SetErrorMode(ErrorMode Mode);
	void SetGenerateMipmaps(bool generateMipmaps); 
	void SetSortCreated(bool turnOn); 
	void SetSortDepth(bool turnOn); 
	void SetSortTextures(bool turnOn); 
	void SetSortTransparentDepth(bool turnOn); 
	void SetWindowTitle(Text Title); 
	Text Sha1(Text ToHash); 
	void Sleep(unsigned short msAmount); 
	
	float Timer(void); 

	////////////////////////////Maths
	float ACos(float value);
	float ACosRad(float value);
	float ASin(float value);
	float ASinRad(float value);
	float ATan(float value);
	float ATan2(float y, float x);
	float ATan2Rad(float y, float x);
	float ATanFull(float x, float y);
	float ATanFullRad(float x, float y);
	float ATanRad(float value);
	float Abs(float value);

	int Ceil(float value);
	float Cos(float value);
	float CosRad(float value);

	float FMod(float value, float modValue);
	int Floor(float value);

	int Mod(int value, int modValue);

	int Random(void);
	int Random(unsigned int from, unsigned int to);
	int RandomSign(int value);
	int Round(float value);

	void SetRandomSeed(unsigned int value);
	float Sin(float value);
	float SinRad(float value);
	float SqRt(float value);

	float Tan(float value);
	float TanRad(float value);
	int Trunc(float value);

	///////////////////////Drawing
	void DrawLine(RFTPoint A, RFTPoint B, Color LineColor);
};

#endif