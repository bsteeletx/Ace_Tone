#include "Input.h"
#include "agk.h"

std::vector<bool*> Input::_buttonID;
std::vector<bool*> Input::_joystickID;
std::vector<bool*> Input::_touchIndex;

Input::Input(void)
{
	
}


Input::~Input(void)
{
}

void Input::CompleteRawJoystickDetection(void)
{
	agk::CompleteRawJoystickDetection();
}

bool Input::GetAccelerometerExists(void)
{
	if (agk::GetAccelerometerExists() == 1)
		return true;

	return false;
}

bool Input::GetCameraExists(void)
{
	if (agk::GetCameraExists() == 1)
		return true;

	return false;
}

bool Input::GetCompassExists(void)
{
	if (agk::GetCompassExists() == 1)
		return true;
	
	return false;
}

float Input::GetDirectionAngle(void)
{
	return agk::GetDirectionAngle();
}

float Input::GetDirectionSpeed(void)
{
	return agk::GetDirectionSpeed();
}

float Input::GetDirectionX(void)
{
	return agk::GetDirectionX();
}

float Input::GetDirectionY(void)
{
	return agk::GetDirectionY();
}
	
bool Input::GetGeolocationExists(void)
{
	if (agk::GetGeolocationExists())
		return true;

	return false;
}

bool Input::GetGyrometerExists(void)
{
	if (agk::GetGyrometerExists())
		return true;

	return false;
}

bool Input::GetInclinometerExists()
{
	if (agk::GetInclinometerExists())
		return true;

	return false;
}
	
bool Input::GetJoystickExists(void)
{
	if (agk::GetJoystickExists())
		return true;

	return false;
}

bool Input::GetKeyboardExists(void)
{
	if (agk::GetKeyboardExists())
		return true;

	return false;
}

bool Input::GetLightSensorExists(void)
{
	if (agk::GetLightSensorExists())
		return true;

	return false;
}
	
bool Input::GetMouseExists(void)
{
	if (agk::GetMouseExists())
		return true;
	
	return false;
}

bool Input::GetMultiTouchExists()
{
	if (agk::GetMultiTouchExists())
		return true;

	return false;
}

unsigned short Input::GetNextButtonID()
{
	bool *button = new bool(true);
		
	_buttonID.push_back(button);
	
	return _buttonID.size();
}

bool Input::GetNFCExists()
{
	if (agk::GetNFCExists())
		return true;

	return false;
}
	
bool Input::GetOrientationSensorExists(void)
{
	if (agk::GetOrientationSensorExists())
		return true;

	return false;
}

RFTPoint Input::GetRawAccel(void)
{
	return RFTPoint(agk::GetRawAccelX(), agk::GetRawAccelY(), agk::GetRawAccelZ());
}

float Input::GetRawAccelX(void)
{
	return agk::GetRawAccelX();
}

float Input::GetRawAccelY(void)
{
	return agk::GetRawAccelY();
}

float Input::GetRawAccelZ(void)
{
	return agk::GetRawAccelZ();
}

float Input::GetRawCompassNorth(bool isMagNorth)
{
	return agk::GetRawCompassNorth((int) isMagNorth);
}

unsigned int Input::GetRawFirstNFCDevice(void)
{
	return agk::GetRawFirstNFCDevice();
}

unsigned int Input::GetRawFirstTouchEvent(bool includeUnknown)
{
	return agk::GetRawFirstTouchEvent(includeUnknown);
}

Text Input::GetRawGeoCity(void)
{
	return Text(agk::GetRawGeoCity());
}

Text Input::GetRawGeoCountry(void)
{
	return Text(agk::GetRawGeoCountry());
}

float Input::GetRawGeoLatitude(void)
{
	return agk::GetRawGeoLatitude();
}
	
float Input::GetRawGeoLongitude(void)
{
	return agk::GetRawGeoLongitude();
}
	
Text Input::GetRawGeoPostalCode(void)
{
	return Text(agk::GetRawGeoPostalCode());
}
	
Text Input::GetRawGeoState(void)
{
	return Text(agk::GetRawGeoState());
}
	
RFTPoint Input::GetRawGyroVelocity(void)
{
	return RFTPoint(GetRawGyroVelocityX(), GetRawGyroVelocityY(), GetRawGyroVelocityZ());
}

float Input::GetRawGyroVelocityX(void)
{
	return agk::GetRawGyroVelocityX();
}

float Input::GetRawGyroVelocityY(void)
{
	return agk::GetRawGyroVelocityY();
}

float Input::GetRawGyroVelocityZ(void)
{
	return agk::GetRawGyroVelocityZ();
}

RFTPoint Input::GetRawInclinoPitchYawRoll(void)
{
	return RFTPoint(GetRawInclinoPitch(), GetRawInclinoYaw(), GetRawInclinoRoll());
}

float Input::GetRawInclinoPitch(void)
{
	return agk::GetRawInclinoPitch();
}

float Input::GetRawInclinoRoll(void)
{
	return agk::GetRawInclinoRoll();
}

float Input::GetRawInclinoYaw(void)
{
	return agk::GetRawInclinoYaw();
}

bool Input::GetRawJoystickButtonPressed(unsigned short joystickID, unsigned short buttonID)
{
	return (bool)agk::GetRawJoystickButtonPressed(joystickID, buttonID);
}

bool Input::GetRawJoystickButtonReleased(unsigned short joystickID, unsigned short buttonID)
{
	return (bool)agk::GetRawJoystickButtonReleased(joystickID, buttonID);
}

bool Input::GetRawJoystickButtonState(unsigned short joystickID, unsigned short buttonID)
{
	return (bool)agk::GetRawJoystickButtonState(joystickID, buttonID);
}

bool Input::GetRawJoystickExists(unsigned short joystickID)
{
	return (bool)agk::GetRawJoystickExists(joystickID);
}

float Input::GetRawJoystickRX(unsigned short joystickID)
{
	return agk::GetRawJoystickRX(joystickID);
}

float Input::GetRawJoystickRY(unsigned short joystickID)
{
	return agk::GetRawJoystickRY(joystickID);
}

float Input::GetRawJoystickRZ(unsigned short joystickID)
{
	return agk::GetRawJoystickRZ(joystickID);
}

float Input::GetRawJoystickX(unsigned short joystickID)
{
	return agk::GetRawJoystickX(joystickID);
}

float Input::GetRawJoystickY(unsigned short joystickID)
{
	return agk::GetRawJoystickY(joystickID);
}

float Input::GetRawJoystickZ(unsigned short joystickID)
{
	return agk::GetRawJoystickZ(joystickID);
}

bool Input::GetRawKeyPressed(unsigned int key)
{
	if (agk::GetRawKeyPressed(key))
		return true;

	return false;
}

bool Input::GetRawKeyReleased(unsigned int key)
{
	if (agk::GetRawKeyReleased(key))
		return true;

	return false;
}

bool Input::GetRawKeyState(unsigned int key)
{
	if (agk::GetRawKeyState(key))
		return true;

	return false;
}

int Input::GetRawLastKey()
{
	return agk::GetRawLastKey();
}

float Input::GetRawLightLevel(void)
{
	return agk::GetRawLightLevel();
}

bool Input::GetRawMouseLeftPressed(void)
{
	if (agk::GetRawMouseLeftPressed())
		return true;

	return false;
}

bool Input::GetRawMouseLeftReleased(void)
{
	if (agk::GetRawMouseLeftReleased())
		return true;

	return false;
}

bool Input::GetRawMouseLeftState(void)
{
	if (agk::GetRawMouseLeftState())
		return true;

	return false;
}

RFTPoint Input::GetRawMouseLocation(void)
{
	return RFTPoint(GetRawMouseLocationX(), GetRawMouseLocationY());
}

float Input::GetRawMouseLocationX(void)
{
	return agk::GetRawMouseX();
}

float Input::GetRawMouseLocationY(void)
{
	return agk::GetRawMouseY();
}

/* Not working*/
/*bool Input::GetRawMouseMiddlePressed()
{
	return (bool)agk::GetRawMouseMiddlePressed();
}

bool Input::GetRawMouseMiddleReleased(void)
{
	return (bool)agk::GetRawMouseMiddleReleased();
}

bool Input::GetRawMouseMiddleState(void)
{
	return (bool)agk::GetRawMouseMiddleState();
} */

bool Input::GetRawMouseRightPressed(void)
{
	if (agk::GetRawMouseRightPressed())
		return true;

	return false;
}

bool Input::GetRawMouseRightReleased(void)
{
	if (agk::GetRawMouseRightReleased())
		return true;

	return false;
}

bool Input::GetRawMouseRightState(void)
{
	if (agk::GetRawMouseRightState())
		return true;

	return false;
}

//////////////////////////////////////
// Returns the current position of the mouse wheel, 
// can be positive or negative, 
// starts at 0. 
// If no mouse exists it will always return 0.
////////////////////////////////////
/* Not Working*/
/*float Input::GetRawMouseWheel()
{
	return agk::GetRawMouseWheel();
}

/////////////////////////////////
// Returns the difference between the current mouse wheel position and the previous mouse wheel position, 
// can be positive or negative, 
// updated once a frame. 
// If no mouse exists it will always return 0.
///////////////////////////////////
float Input::GetRawMouseWheelDelta()
{
	return agk::GetRawMouseWheelDelta();
} */

unsigned short Input::GetRawNextTouchEvent()
{
	return agk::GetRawNextTouchEvent();
}

//void GetRawNFCCount(void); //Not yet functional
//void GetRawNFCData(void); //Not yet functional
//void GetRawNFCDataState(void); //not yet functional
//void GetRawNFCName(void); //not yet functional
//void GetRawNextNFCDevice(void); //not yet functional

float Input::GetRawOrientationW(void)
{
	return agk::GetRawOrientationW();
}

float Input::GetRawOrientationX(void)
{
	return agk::GetRawOrientationX();
}

float Input::GetRawOrientationY(void)
{
	return agk::GetRawOrientationY();
}

float Input::GetRawOrientationZ(void)
{
	return agk::GetRawOrientationZ();
}

///////////////////////////////////
// Returns the number of touch events currently taking place. 
// By default the AGK does not count an event until it knows what type of event it is, e.g. short, long, drag, etc. 
// To count unknown events as well set bIncludeUnknown to true. 
// Use false to ignore unknown events.
/////////////////////////////////////
unsigned short Input::GetRawTouchCount(bool includeUnkown)
{
	if (includeUnkown)
		return agk::GetRawTouchCount(1);
	
	return agk::GetRawTouchCount(0);
}

////////////////////////////////
// Returns the position in screen coordinates where the touch event is currently located. 
// This coordinate will be in view coordinates, 
// if you are offsetting the view port you may want to convert it to world coordinates using ScreenToWorldX
///////////////////////////////
RFTPoint Input::GetRawTouchCurrentPos(unsigned short touchIndex)
{
	return RFTPoint(_GetRawTouchCurrentX(touchIndex), _GetRawTouchCurrentY(touchIndex));
}

////////////////////////////////
// Returns the position in screen coordinates where the touch event was last recorded before its current location. 
// This coordinate will be in view coordinates, 
// if you are offsetting the view port you may want to convert it to world coordinates using ScreenToWorldX.
////////////////////////////////
RFTPoint Input::GetRawTouchLastPos(unsigned short touchIndex)
{
	return RFTPoint(_GetRawTouchLastX(touchIndex), _GetRawTouchLastY(touchIndex));
}

/////////////////////////////
// Returns true if the touch has been released, 
// this will always be true for short events, 
// hold and drag events will keep reporting false until they are released at which point you may wish to take some action. 
// Each event will only report released as true once before being removed from the event list. 
// If a touch event is ignored (not queried) for one frame after it is released it will be deleted from the event list.
/////////////////////////////
bool Input::GetRawTouchReleased(unsigned short touchIndex)
{
	return (bool)agk::GetRawTouchReleased(touchIndex);
}

/////////////////////////////
// Returns the position in screen coordinates where the touch event started. 
// This coordinate will be in view coordinates, 
// if you are offsetting the view port you may want to convert it to world coordinates using ScreenToWorldX.
/////////////////////////////
RFTPoint Input::GetRawTouchStartPos(unsigned short touchIndex)
{
	return RFTPoint(_GetRawTouchStartX(touchIndex), _GetRawTouchStartY(touchIndex));
}

/////////////////////////////
// Returns the total time that this event took, 
// from press to release in seconds.
/////////////////////////////
float Input::GetRawTouchTime(unsigned short touchIndex)
{
	return agk::GetRawTouchTime(touchIndex);
}

/////////////////////////////
// Returns the type of the given touch event. 
// All you can be sure about with unknown events is that the finger is currently on screen and has been there less than 1 second. 
// After 1 second it automatically becomes a hold event. 
// If the user lifts their finger off the screen it becomes a short event, 
// and if they move their finger it becomes a drag event. 
// If no events are available it returns 0. 
// Events may change from being hold events to being drag events, 
// but short and drag events do not change type. 
// Unknown events are guaranteed to change type once more information is available. 
// Possible return values are 0 to indicate a default touch, 
// 1 for a short touch, 
// 2 for a hold and 3 for dragging.
///////////////////////////////
TouchType Input::GetRawTouchType(unsigned short touchIndex)
{
	return (TouchType)agk::GetRawTouchType(touchIndex);
}

int Input::GetRawTouchValue(unsigned short touchIndex)
{
	return agk::GetRawTouchValue(touchIndex);
}

///////////////////////////
// Sets the dead zone for all real joysticks so that any X or Y value below the given threshold will return 0 instead. 
// This value must be between 0 and 1, 
// by default it is set to 0.15.
//////////////////////////
void Input::SetRawJoystickDeadZone(float value)
{
	if (value > 1.0f)
		agk::SetRawJoystickDeadZone(1.0f);
	else if (value < 0.0f)
		agk::SetRawJoystickDeadZone(0.0f);
	else
		agk::SetRawJoystickDeadZone(value);
}

void Input::SetRawMousePosition(RFTPoint Location)
{
	agk::SetRawMousePosition(Location.GetX(), Location.GetY());
}

void Input::SetRawMousePosition(float x, float y)
{
	agk::SetRawMousePosition(x, y);
}

void Input::SetRawMouseVisible(bool isVisible)
{
	agk::SetRawMouseVisible((int) isVisible);
}

/////////////////////////
// Allows you to set some custom data to be stored in this event that you can retrieve later. 
// Could be a value or pointer.
//////////////////////////
void Input::SetRawTouchValue(unsigned short touchIndex, int value)
{
	agk::SetRawTouchValue(touchIndex, value);
}

float Input::_GetRawTouchCurrentX(unsigned short touchIndex)
{
	return agk::GetRawTouchCurrentX(touchIndex);
}

float Input::_GetRawTouchCurrentY(unsigned short touchIndex)
{
	return agk::GetRawTouchCurrentY(touchIndex);
}

float Input::_GetRawTouchLastX(unsigned short touchIndex)
{
	return agk::GetRawTouchLastX(touchIndex);
}

float Input::_GetRawTouchLastY(unsigned short touchIndex)
{
	return agk::GetRawTouchLastY(touchIndex);
}

float Input::_GetRawTouchStartX(unsigned short touchIndex)
{
	return agk::GetRawTouchStartX(touchIndex);
}

float Input::_GetRawTouchStartY(unsigned short touchIndex)
{
	return agk::GetRawTouchStartY(touchIndex);
}