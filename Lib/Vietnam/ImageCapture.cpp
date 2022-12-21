#include "ImageCapture.h"
#include "agk.h"

Capture::Capture()
: Image()
{

}

Capture::~Capture()
{

}

/************************
** Returns the ID of a newly captured image created using ShowImageCaptureScreen. 
** If this returns 0 then the user cancelled the process or you have not yet started it with ShowImageCaptureScreen. 
** Once you have called this command to retrieve the image ID it will return 0 until ShowImageCaptureScreen is called again.
*///////////////////////
unsigned short Capture::Get()
{
	return agk::GetCapturedImage();
}

/************************
** Returns true if AGK is currently displaying a camera feed and waiting for the user to capture an image. 
** When this returns 0 the user has either cancelled or captured an image, check GetCapturedImage to see what the result was.
*//////////////////////////
bool Capture::IsCapturing()
{
	//change 1/0 to bool
	return (bool)agk::IsCapturingImage();
}

/***********************
** Presents the user with an option to take a photo with the device camera, if available. 
** If the device does not have a camera, or otherwise cannot be used, this will return false and your app will continue as normal. 
** This does not immediately capture the image, 
** depending on the platform your app may continue running in the background whilst the user is taking a photo, 
** or it may pause execution whilst the photo is taken. 
** In any case you must assume your app continues running but is no longer visible, 
** use IsCapturingImage to check when the user returns from the image capture process, 
** and GetCapturedImage to discover the result of the process.
*///////////////////////
bool Capture::ShowScreen()
{
	return (bool)agk::ShowImageCaptureScreen();
}