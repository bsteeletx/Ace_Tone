#include "AGKCore.h"
#include "agk.h"

AGKCore::AGKCore(void)
{
}


AGKCore::~AGKCore(void)
{
}

unsigned int AGKCore::Asc(char alpha)
{
	const char single[1] = {alpha};
	return agk::Asc(single);
}

float AGKCore::ATan(float value)
{
	return agk::ATan(value);
}

Text AGKCore::Bin(int value)
{
	return Text(agk::Bin(value));
}
	
int AGKCore::Ceil(float value)
{
	return agk::Ceil(value);
}

Text AGKCore::Chr(unsigned int ascii)
{
	return Text(agk::Chr(ascii));
}

void AGKCore::ClearDepthBuffer(void)
{
	agk::ClearDepthBuffer();
}

void AGKCore::ClearScreen(void)
{
	agk::ClearScreen();
}

float AGKCore::Cos(float value)
{
	return agk::Cos(value);
}

float AGKCore::CosRad(float value)
{
	return agk::CosRad(value);
}

unsigned int AGKCore::CountStringTokens(Text Original, char delimeter)
{
	char single[1] = { delimeter };

	return agk::CountStringTokens(Original.GetCString(), single);
}

void AGKCore::DeleteAllImages()
{
	agk::DeleteAllImages();
}

void AGKCore::DeleteAllSprites()
{
	agk::DeleteAllSprites();
}

void AGKCore::DeleteAllText()
{
	agk::DeleteAllText();
}

#if OS == ANDROID
/////////////////////////////////////
// Starts the download of any expansion file that this platform and app needs, 
// currently only applicable to Android. 
// If the download has already started this has no effect. 
// You can use GetExpansionFileProgress to check on the progress of the download and GetExpanionFileState to check when it has completed. 
// After calling this command you should wait for GetExpanionFileState to return -1 (error) or 3 (complete) whilst displaying a progress bar.
//////////////////////////////////////
void AGKCore::DownloadExpansionFile()
{
	agk::DownloadExpansionVile();
}
#endif

/////////////////////////
// Draws a 2D line from one point on the screen to another with a chosen color. 
// Lines appear above all other drawing except the Print command and can be used with the GetImage function to create new images. 
// The XY coordinates are in screen coordinates so are not affected by the SetViewOffset command.
///////////////////////
void AGKCore::DrawLine(RFTPoint A, RFTPoint B, Color LineColor)
{
	agk::DrawLine(A.GetX(), A.GetY(), B.GetX(), B.GetY(), LineColor.GetRed(), LineColor.GetGreen(), LineColor.GetBlue());
}

void AGKCore::EnableClearColor(bool clearEachFrame)
{
	if (clearEachFrame)
		agk::EnableClearColor(1);
	else
		agk::EnableClearColor(0);
}

float AGKCore::FMod(float value, float modValue)
{
	return agk::FMod(value, modValue);
}

int AGKCore::Floor(float value)
{
	return agk::Floor(value);
}

////////////////////////
// Returns the name of the exe
////////////////////////
Text AGKCore::GetAppName(void)
{
	return Text(agk::GetAppName());
}

unsigned short AGKCore::GetDeviceHeight(void)
{
	return agk::GetDeviceHeight();
}

/////////////////////////
// Returns a string containing the language of the current device in the form "en", "fr", "de", etc.
//////////////////////////
Text AGKCore::GetDeviceLanguage(void)
{
	return Text(agk::GetDeviceLanguage());
}

///////////////////////////
// Returns a string containing the name of the current platform. 
// e.g. "windows" or "bada". 
// When dealing with iOS more information is returned 
// e.g. on iPad 1 "ios|iPad1,1" and on iPod 2nd gen: "ios|iPod2,1" and on iPhone 3G: "ios|iPhone1,2". 
// The first number is the major model number, 
// the second is the minor model number.
/////////////////////////
Text AGKCore::GetDeviceName()
{
	return Text(agk::GetDeviceName());
}

unsigned short AGKCore::GetDeviceWidth(void)
{
	return agk::GetDeviceWidth();
}

float AGKCore::GetDisplayAspect(void)
{
	return agk::GetDisplayAspect();
}

#if OS == ANDROID
////////////////////////////
// Checks the progress of a download started by DownloadExpanionFile, 
// returns a float value between 0 and 100 Use GetExpansionFileState to check if the download has completed.
/////////////////////////////
float AGKCore::GetExpansionFileProgress()
{
	return agk::GetExpansionFileProgress();
}

//////////////////////////
// Returns the state of any expansion file used by this platform, 
// currently only applicable to Android. 
// Returns -1 if an error occured during download, 
// 0 if the expansion file is not used on this platform, 
// 1 if it should exist but doesn't (you call DownloadExpansionFile() in this case), 
// 2 if it is currently being downloaded, 
// and 3 if everything has completed and the file exists.
///////////////////////////////////
ExpansionFileState AGKCore::GetExpansionFileState()
{
	return (ExpansionFileState)agk::GetExpansionFileState();
}
#endif

///////////////////////
// Get the time in seconds spent processing and rendering the last frame. 
// Only updated when Sync or Swap are called. 
// This is limited to a max value of 0.2 seconds to prevent internal timer based code from interpolating large time gaps. 
// To find the true frame time you can use the Timer() command.
//////////////////////
float AGKCore::GetFrameTime()
{
	return agk::GetFrameTime();
}

//////////////////////////
// Get the number of milliseconds since the app was started. 
// Calling this command will internally make a system call to get the amount of time passed, 
// therefore it's advisable to not call it too often per frame. 
// A better approach might be to store the time value and reuse it throughout the current frame.
//////////////////////////
unsigned int AGKCore::GetMilliseconds()
{
	return agk::GetMilliseconds();
}

Orientation AGKCore::GetOrientation(void)
{
	return (Orientation) agk::GetOrientation();
}

unsigned int AGKCore::GetPolygonsDrawn(void)
{
	return agk::GetPolygonsDrawn();
}

bool AGKCore::GetResumed(void)
{
	if (agk::GetResumed() == 1)
		return true;
	
	return false;
}

float AGKCore::GetScreenBoundsBottom(void)
{
	return agk::GetScreenBoundsBottom();
}

float AGKCore::GetScreenBoundsLeft(void)
{
	return agk::GetScreenBoundsLeft();
}

float AGKCore::GetScreenBoundsRight(void)
{
	return agk::GetScreenBoundsRight();
}

float AGKCore::GetScreenBoundsTop(void)
{
	return agk::GetScreenBoundsTop();
}

//////////////////////////
// Get the number of whole seconds since the app was started. Accurate to 1 second. 
// Calling this command will internally make a system call to get the amount of time passed, 
// therefore it's advisable to not call it too often per frame. 
// A better approach might be to store the time value and reuse it throughout the current frame.
//////////////////////////
unsigned int AGKCore::GetSeconds()
{
	return agk::GetSeconds();
}

Text AGKCore::GetStringToken(Text Original, char delimeter, unsigned int token)
{
	char single[1] = { delimeter };

	return Text(agk::GetStringToken(Original.GetCString(), single, token));
}

unsigned int AGKCore::GetVerticesProcessed(void)
{
	return agk::GetVerticesProcessed();
}

float AGKCore::GetViewOffsetX(void)
{
	return agk::GetViewOffsetX();
}

float AGKCore::GetViewOffsetY(void)
{
	return agk::GetViewOffsetY();
}

float AGKCore::GetViewZoom(void)
{
	return agk::GetViewZoom();
}

unsigned short AGKCore::GetVirtualHeight(void)
{
	return agk::GetVirtualHeight();
}

unsigned short AGKCore::GetVirtualWidth(void)
{
	return agk::GetVirtualWidth();
}

Text AGKCore::Hex(int value)
{
	return Text(agk::Hex(value));
}

//////////////////////
// Decodes a URL encoded string. 
// It can decode all alpahnumeric characters and most non-alphanumeric characters.
//////////////////////
Text AGKCore::HTTPDecode(Text Encoded)
{
	return Text(agk::HTTPDecode(Encoded.GetCString()));
}

////////////////////////
// Encodes a string so that it can be sent to a server via HTTP without interferring with the HTTP request. 
// For example if you wanted to send a POST variable that contained the characters & or = these would look like additional variables inside the string you want to send. 
// Using HTTPEncode on this string would turn these characters into POST safe values which are then automatically converted back to their original characters once they reach something like a PHP script. 
// This uses standard URL encoding for non-alphanumeric characters leaving alphanumeric characters alone.
//////////////////////////
Text AGKCore::HTTPEncode(Text ToEncode)
{
	return Text(agk::HTTPEncode(ToEncode.GetCString()));
}

Text AGKCore::Left(Text Original, unsigned int count)
{
	return Text(agk::Left(Original.GetCString(), count));
}

unsigned int AGKCore::Len(Text Original)
{
	return agk::Len(Original.GetCString());
}

Text AGKCore::Lower(Text Original)
{
	return Text(agk::Lower(Original.GetCString()));
}

//////////////////////////
// Displays a message box containing the given text. 
// Your app is not guaranteed to pause whilst the message is displayed.
//////////////////////////
void AGKCore::Message(Text MesssageToDisplay)
{
	agk::Message(MesssageToDisplay.GetCString());
}

Text AGKCore::Mid(Text Original, unsigned int position, int length)
{
	return Text(agk::Mid(Original.GetCString(), position, length));
}

int AGKCore::Mod(int value, int modValue)
{
	return agk::Mod(value, modValue);
}

////////////////////////////
// Prints the given value or string to the screen and adds a new line character so that the next print command will be one line down.
/////////////////////////////
void AGKCore::Print(int printValue, bool newLineAtEnd)
{
	if (newLineAtEnd)
		agk::Print(printValue);
	else
		agk::PrintC(printValue);
}

////////////////////////////
// Prints the given value or string to the screen and adds a new line character so that the next print command will be one line down.
/////////////////////////////
void AGKCore::Print(float printValue, bool newLineAtEnd)
{
	if (newLineAtEnd)
		agk::Print(printValue);
	else
		agk::PrintC(printValue);
}

////////////////////////////
// Prints the given value or string to the screen and adds a new line character so that the next print command will be one line down.
/////////////////////////////
void AGKCore::Print(Text PrintValue, bool newLineAtEnd)
{
	if (newLineAtEnd)
		agk::Print(PrintValue.GetCString());
	else
		agk::PrintC(PrintValue.GetCString());
}

int AGKCore::Random(void)
{
	return agk::Random();
}

int AGKCore::Random(unsigned int from, unsigned int to)
{
	return agk::Random(from, to);
}

int AGKCore::RandomSign(int value)
{
	return agk::RandomSign(value);
}

void AGKCore::Render(void)
{
	agk::Render();
}

void AGKCore::Render2DBack(void)
{
	agk::Render2DBack();
}

void AGKCore::Render2DFront(void)
{
	agk::Render2DFront();
}

void AGKCore::Render3D(void)
{
	agk::Render3D();
}

///////////////////////
// Resets the time returned from Timer to 0. 
// This allows the full accuracy to be regained after your app has been running for some time.
/////////////////////
void AGKCore::ResetTimer()
{
	agk::ResetTimer();
}

Text AGKCore::Right(Text Original, unsigned int count)
{
	return Text(agk::Right(Original.GetCString(), count));
}

int AGKCore::Round(float value)
{
	return agk::Round(value);
}

float AGKCore::ScreenFPS(void)
{
	return agk::ScreenFPS();
}

RFTPoint AGKCore::ScreenToWorld(RFTPoint ScreenLoc)
{
	return RFTPoint(agk::ScreenToWorldX(ScreenLoc.GetX()), agk::ScreenToWorldY(ScreenLoc.GetY()));
}

float AGKCore::ScreenToWorldX(float x)
{
	return agk::ScreenToWorldX(x);
}

float AGKCore::ScreenToWorldY(float y)
{
	return agk::ScreenToWorldY(y);
}

void AGKCore::SetBorderColor(Color BorderColor)
{
	agk::SetBorderColor(BorderColor.GetRed(), BorderColor.GetGreen(), BorderColor.GetBlue());
}

void AGKCore::SetClearColor(Color ClearColor)
{
	agk::SetClearColor(ClearColor.GetRed(), ClearColor.GetGreen(), ClearColor.GetBlue());
}

//////////////////////////////
// Sets the default font to use for text objects. 
// The AGK has a built in font that it uses for text objects, 
// this allows you to override it. 
// If you do choose to override it you must do so before creating any text objects. 
// You can set the font on a per text basis using SetTextFontImage. 
// The image should contain all white characters surrounded by a transparent alpha channel. 
// Fully transparent pixels should also contain white in their RGB components.
// The font image may either be fixed width or variable width.
// For fixed width the font image must be laid out in a grid of 16 characters across and 6 characters down, 
// starting with the ascii character 32 (space)in the top left and proceeding left to right, top to bottom, 
// ending with ascii character 127 (DEL)in the bottom right.
// The image width must be divisible by 16 and the image height must be divisible by 6. 
// For variable width the image must be an atlas texture accompained by a subimages.txt file that states the location of each character on the image.
// The AGK will look for images "32" up to and including "127" in the subimages file and any not found will default to the space character(32).
//////////////////////////////////////
void AGKCore::SetDefaultFontImage(unsigned int fontID)
{
	agk::SetTextDefaultFontImage(fontID);
}

/////////////////////////
// Sets the default filter for textures when the texture is larger than the screen space it is displayed in. 
// You can use a mode of nearest to use the nearest pixel, 
// which will appear blocky, 
// or linear to use a linear filter which will look blurry. 
// When the image matches the screen space exactly then both filters will look the same when there is a slight difference, 
// nearest tends to be sharper, 
// but may flicker as it changes pixel choice. 
// You can set this value per image using SetImageMagFilter.
/////////////////////////
void AGKCore::SetDefaultMagFilter(bool linear)
{
	if (linear)
		agk::SetDefaultMagFilter(1);
	else
		agk::SetDefaultMagFilter(0);
}

///////////////////////
// Sets the default filter for textures when the texture is smaller than the screen space it is displayed in. 
// You can use a mode of nearest to use the nearest pixel, 
// which will appear blocky, 
// or linear to use a linear filter which will look blurry. 
// When the image matches the screen space exactly then both filters will look the same when there is a slight difference, 
// nearest tends to be sharper, 
// but may flicker as it changes pixel choice. 
// You can set this value per image using SetImageMinFilter.
//////////////////////
void AGKCore::SetDefaultMinFilter(bool linear)
{
	if (linear)
		agk::SetDefaultMinFilter(1);
	else
		agk::SetDefaultMinFilter(0);
}

//////////////////////
// Sets the default texture wrapping for images where the UV coords go beyond the range 0 to 1 in the U direction.
////////////////////
void AGKCore::SetDefaultWrapU(bool repeat)
{
	if (repeat)
		agk::SetDefaultWrapU(1);
	else
		agk::SetDefaultWrapU(0);
}

//////////////////
// Sets the default texture wrapping for images where the UV coords go beyond the range 0 to 1 in the V direction.
/////////////////
void AGKCore::SetDefaultWrapV(bool repeat)
{
	if (repeat)
		agk::SetDefaultWrapV(1);
	else
		agk::SetDefaultWrapV(0);
}

void AGKCore::SetDisplayAspect(float aspect)
{
	agk::SetDisplayAspect(aspect);
}

#if OS == ANDROID
//////////////////
// Sets the version number to use in the other expansion file commands. 
// Currently only applicable to Android. 
// The version number of the expansion file is determined by the version number of the APK that was uploaded with it. 
// For example the APK may be updated to a new version number but the expansion file could still be the original version number.
//////////////////
void AGKCore::SetExpansionFileVersion(int version)
{
	agk::SetExpansionFileVersion(version);
}
#endif

///////////////////////////
// Sets the error mode for the AGK from ignore, report, or stop from AGK commands, 
// e.g. sprite ID doesn't exist in a command that accepts a sprite ID. 
// Ignoring will make the AGK attempt to carry on, 
// ignoring the entire command if necessary. 
// Reporting will make the AGK report the error to an appropriate debug console and carry on. 
// Stop will force the AGK to report the error as before and then stop by throwing an exception, 
// which must be caught or the app will terminate. 
// In the case of tier 1 the exception is caught by the interpreter and, if debugging, displayed in the IDE.
////////////////////////////
void AGKCore::SetErrorMode(ErrorMode Mode)
{
	agk::SetErrorMode(Mode);
}

////////////////
// Sets whether loaded images having mipmaps generated and used. 
// Should be called before any images are loaded. 
// May be changed before another image is loaded to make some use mipmaps and others not.
//////////////
void AGKCore::SetGenerateMipmaps(bool generateMipmaps)
{
	if (generateMipmaps)
		agk::SetGenerateMipmaps(1);
	else
		agk::SetGenerateMipmaps(0);
}

void AGKCore::SetOrientationAllowed(bool portrait, bool revPortrait, bool landscape, bool revLandscape)
{
	agk::SetOrientationAllowed((int) portrait, (int) revPortrait, (int) landscape, (int) revLandscape);
}

void AGKCore::SetRandomSeed(unsigned int value)
{
	agk::SetRandomSeed(value);
}

void AGKCore::SetResolutionMode(bool SetFullRez)
{
	agk::SetResolutionMode((int) SetFullRez);
}

//////////////////
// If two sprites occupy the same depth then the order they are drawn is undefined unless this function is set to true, 
// in which case sprites at the same depth will be drawn in the order they were created. 
// For maximum performance it is recommended that every sprite has its own depth value with this command set to false. 
// If the order they are drawn is not important, 
// for example physics sprites that won't normally overlap, 
// then you can use sprites at the same depth without setting this command to true.
///////////////////
void AGKCore::SetSortCreated(bool turnOn)
{
	if (turnOn)
		agk::SetSortCreated(1);
	else
		agk::SetSortCreated(0);
}

//////////////////////////////
// Sets whether the AGK should sort opaque sprites by depth when drawing. 
// This draws sprites at the front of the screen first, 
// which fills the depth buffer so later sprites behind can be skipped. 
// This will improve performance on fill rate limited devices where you are drawing lots of overlapping opaque sprites. 
// It is off by default but if you do not change sprite depth frequently it is recommended to turn it on. 
// This does not apply to transparent sprites which have their own sorting requirements.
////////////////////////////
void AGKCore::SetSortDepth(bool turnOn)
{
	if (turnOn)
		agk::SetSortDepth(1);
	else
		agk::SetSortDepth(0);
}

/////////////////////////
// Sets whether the AGK should sort sprites by texture when drawing to limit the number of texture changes. 
// This will improve performance on devices that do not cope well with frequent state changes, 
// but may reduce performance if textures on sprites are changed frequently. 
// It is off by default but if you do not change sprite textures, 
// or are using atlas textures it is recommended to turn it on.
///////////////////////////
void AGKCore::SetSortTextures(bool turnOn)
{
	if (turnOn)
		agk::SetSortTextures(1);
	else
		agk::SetSortTextures(0);
}

///////////////////////
// Sets whether the AGK should sort transparent sprites by depth when drawing. 
// This draws sprites at the back of the screen first to achieve the correct blending result when transparent sprites overlap. 
// It is on by default but if your transparent sprites are guaranteed to not overlap you may turn it off to increase performance
//////////////////////
void AGKCore::SetSortTransparentDepth(bool turnOn)
{
	if (turnOn)
		agk::SetSortTransparentDepth(1);
	else
		agk::SetSortTransparentDepth(0);
}

void AGKCore::SetSyncRate(float value, bool intensiveMode)
{
	if (intensiveMode)
		agk::SetSyncRate(value, 1);
	else
		agk::SetSyncRate(value, 0);
}

void AGKCore::SetScissor(RFTPoint A, RFTPoint B)
{
	agk::SetScissor(A.GetX(), A.GetY(), B.GetX(), B.GetY());
}

void AGKCore::SetTextDefaultMagFilter(bool linear)
{
	if (linear)
		agk::SetDefaultMagFilter(1);
	else
		agk::SetDefaultMagFilter(0);
}

void AGKCore::SetTextDefaultMinFilter(bool linear)
{
	if (linear)
		agk::SetDefaultMinFilter(1);
	else
		agk::SetDefaultMinFilter(0);
}

void AGKCore::SetTransitionMode(bool slowRotate)
{
	if (slowRotate)
		agk::SetTransitionMode(1);
	else
		agk::SetTransitionMode(0);
}

void AGKCore::SetVSync(bool turnOn)
{
	if (turnOn)
		agk::SetVSync(1);
	else
		agk::SetVSync(0);
}

///////////////////////////
// Offset the screen viewport relative to the world, 
// for example a view offset of 0, 20 will move the screen down by 20 pixels showing any sprite that was previously positioned just off the bottom of the screen.
// This can be useful for scrolling games where you want to move the view across a level.
// Using this command will automatically disable the four physics walls surrounding the screen.
// You can also fix sprites to the screen so that they move along with it by using FixSpriteToScreen.
// The view offset values position the top left corner of the view in the world, 
// while SetViewZoom determines how much of the world the view can see.
////////////////////////////
void AGKCore::SetViewOffset(RFTPoint Offset)
{
	agk::SetViewOffset(Offset.GetX(), Offset.GetY());
}

//////////////////////////
// Zooms the screen viewport relative to the world, 
// for example a view zoom of 2.0 will double the size of anything currently in view. 
// A value of 1.0 returns everything to normal size.
// Using this command will automatically disable the four physics walls surrounding the screen.
// You can also fix sprites to the screen so that they do not change size by using FixSpriteToScreen.
// This command can either zoom towards the view's top left corner or towards the view's center, 
// see SetViewZoomMode for details.
//////////////////////////
void AGKCore::SetViewZoom(float zoom)
{
	agk::SetViewZoom(zoom);
}

///////////////////////////
// Sets the zoom mode from top left corner or centered. 
// By default the view zooms from its top left corner, 
// maintaining the views offset in world coodinates. 
// For example a view with an offset of 20,20 will maintain its top left corner at 20,20 in world coordinates no matter what zoom value is given. 
// However, centered zoom keeps the center of the view stationary whilst scaling everything else around it, 
// making the offset value more difficult to judge. 
// In this mode the top left corner will only be at 20,20 when the zoom value is 1.0, 
// for other zoom values the top left corner will be scaled away from the offset point. 
// For example, assume a world size of 100,100 units, 
// a zoom level of 1.0, 
// and a view offset of 0,0. 
// The view will be displaying world coordinates 0,0 (its top left corner) to 100,100 (at its bottom right corner), 
// with a zoom value of 2.0 and top left zooming the view will now show world coordinates 0,0 to 50,50 in the same space making everything look bigger. 
// In centered zooming the view would instead show 25,25 to 75,75 maintaining the center of the view over the point 50,50 in world coordinates.
//////////////////////////
void AGKCore::SetViewZoomMode(bool centered)
{
	if (centered)
		agk::SetViewZoomMode(1);
	else
		agk::SetViewZoomMode(0);
}

void AGKCore::SetVirtualResolution(unsigned short width, unsigned short height)
{
	agk::SetVirtualResolution(width, height);
}

//////////////////////
// Sets the window title for those platforms that run in a window (e.g. Windows, Mac).
/////////////////////
void AGKCore::SetWindowTitle(Text Title)
{
	agk::SetWindowTitle(Title.GetCString());
}

/////////////////////
// Hashes a string using the SHA1 algorithm to produce a 40 character hexidecimal string. 
// This is a one way hash function that can be used with salting (appending a secret string) for passwords or tamper detection in parameters passed to a server.
////////////////////
Text AGKCore::Sha1(Text ToHash)
{
	return Text(agk::Sha1(ToHash.GetCString()));
}

float AGKCore::Sin(float value)
{
	return agk::Sin(value);
}

float AGKCore::SinRad(float value)
{
	return agk::SinRad(value);
}

///////////////////
// Suspend the app for a specified number of milliseconds. 
// It is not recommended that you use this command to suspend an app for more than the time of one frame (roughly 17 milliseconds).
/////////////////
void AGKCore::Sleep(unsigned short msAmount)
{
	agk::Sleep(msAmount);
}

Text AGKCore::Spaces(unsigned int length)
{
	return Text(agk::Spaces(length));
}

float AGKCore::SqRt(float value)
{
	return agk::Sqrt(value);
}

void AGKCore::StepPhysics(float time)
{
	agk::StepPhysics(time);
}

Text AGKCore::Str(float value, unsigned int decimals)
{
	return Text(agk::Str(value, decimals));
}

Text AGKCore::Str(int value)
{
	return Text(agk::Str(value));
}

void AGKCore::Swap(void)
{
	agk::Swap();
}

void AGKCore::Sync(void)
{
	agk::Sync();
}
	
float AGKCore::Tan(float value)
{
	return agk::Tan(value);
}

float AGKCore::TanRad(float value)
{
	return agk::TanRad(value);
}

////////////////////
// Get the number of seconds and fractions of seconds since the app was started. 
// Accurate to milliseconds, 
// but due to floating point inaccuracies the longer the app is running the less accurate this becomes, 
// this value will start to lose precision after approximately 2 hours of running.
// Calling this command will internally make a system call to get the amount of time passed, 
// therefore it's advisable to not call it too often per frame. 
// A better approach might be to store the time value and reuse it throughout the current frame.
////////////////////////
float AGKCore::Timer(void)
{
	return agk::Timer();
}

int AGKCore::Trunc(float value)
{
	return agk::Trunc(value);
}

void AGKCore::Update(float time)
{
	agk::Update(time);
}

void AGKCore::Update2D(float time)
{
	agk::Update2D(time);
}

void AGKCore::Update3D(float time)
{
	agk::Update3D(time);
}

void AGKCore::UpdateDeviceSize(unsigned short width, unsigned short height)
{
	agk::UpdateDeviceSize(width, height);
}

Text AGKCore::Upper(Text Original)
{
	return Text(agk::Upper(Original.GetCString()));
}


int AGKCore::Val(Text NumberString, int base)
{
	return agk::Val(NumberString.GetCString(), base);
}

float AGKCore::ValFloat(Text NumberString)
{
	return agk::ValFloat(NumberString.GetCString());
}
	
RFTPoint AGKCore::WorldToScreen(RFTPoint Coordinate)
{
	return RFTPoint(agk::WorldToScreenX(Coordinate.GetX()), agk::WorldToScreenY(Coordinate.GetY()));
}

float AGKCore::WorldToScreenX(float worldX)
{
	return agk::WorldToScreenX(worldX);
}

float AGKCore::WorldToScreenY(float worldY)
{
	return agk::WorldToScreenY(worldY);
}