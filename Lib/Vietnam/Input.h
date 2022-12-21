#pragma once

#include "Point.h"
#include "Text.h"
#include "Defines.h"
#include <vector>

class Input
{
public:
	Input(void);
	~Input(void);

	////////////////Accelerometer
	RFTPoint GetDirection();
	float GetDirectionAngle();
	float GetDirectionSpeed();
	float GetDirectionX();
	float GetDirectionY();

	////////////////////Platform Specific & Support
	void CompleteRawJoystickDetection(void);

	bool GetAccelerometerExists(void);
	bool GetButtonPressed(unsigned short button);
	bool GetButtonReleased(unsigned short button);
	bool GetButtonState(unsigned short button);
	bool GetCameraExists(void);
	bool GetCompassExists(void);
	bool GetGeolocationExists(void);
	bool GetGyrometerExists(void);
	bool GetInclinometerExists(); 
	bool GetJoystickExists(void);
	RFTPoint GetJoystickLocation(void);
	float GetJoystickX(void);
	float GetJoystickY(void);
	bool GetKeyboardExists(void);
	unsigned int GetLastChar(void);
	bool GetLightSensorExists(void);
	bool GetMouseExists(void);
	bool GetMultiTouchExists(); 
	unsigned short GetNextButtonID();
	bool GetNFCExists(); 
	bool GetOrientationSensorExists(void);
	RFTPoint GetRawAccel(void);
	float GetRawAccelX(void);
	float GetRawAccelY(void);
	float GetRawAccelZ(void);
	float GetRawCompassNorth(bool isMagNorth);
	unsigned int GetRawFirstNFCDevice(void); 
	unsigned int GetRawFirstTouchEvent(bool includeUnknown); 
	Text GetRawGeoCity(void);
	Text GetRawGeoCountry(void); 
	float GetRawGeoLatitude(void); 
	float GetRawGeoLongitude(void);
	Text GetRawGeoPostalCode(void);
	Text GetRawGeoState(void);
	RFTPoint GetRawGyroVelocity(void);
	float GetRawGyroVelocityX(void);
	float GetRawGyroVelocityY(void);
	float GetRawGyroVelocityZ(void);
	RFTPoint GetRawInclinoPitchYawRoll(void);
	float GetRawInclinoPitch(void);
	float GetRawInclinoRoll(void);
	float GetRawInclinoYaw(void);
	bool GetRawJoystickButtonPressed(unsigned short joystickID, unsigned short buttonID); 
	bool GetRawJoystickButtonReleased(unsigned short joystickID, unsigned short buttonID); 
	bool GetRawJoystickButtonState(unsigned short joystickID, unsigned short buttonID); 
	bool GetRawJoystickExists(unsigned short joystickID); 
	float GetRawJoystickRX(unsigned short joystickID); 
	float GetRawJoystickRY(unsigned short joystickID);
	float GetRawJoystickRZ(unsigned short joystickID);
	float GetRawJoystickX(unsigned short joystickID);
	float GetRawJoystickY(unsigned short joystickID);
	float GetRawJoystickZ(unsigned short joystickID);
	bool GetRawKeyPressed(unsigned int key);
	bool GetRawKeyReleased(unsigned int key);
	bool GetRawKeyState(unsigned int key);
	int GetRawLastKey(); 
	float GetRawLightLevel(void);
	bool GetRawMouseLeftPressed(void);
	bool GetRawMouseLeftReleased(void);
	bool GetRawMouseLeftState(void);
	RFTPoint GetRawMouseLocation(void);
	float GetRawMouseLocationX(void);
	float GetRawMouseLocationY(void);
	//Not Working
	/*bool GetRawMouseMiddlePressed(void); 
	bool GetRawMouseMiddleReleased(void);
	bool GetRawMouseMiddleState(void);*/
	//////
	bool GetRawMouseRightPressed(void);
	bool GetRawMouseRightReleased(void);
	bool GetRawMouseRightState(void);
	//Not working
	/*float GetRawMouseWheel(); 
	float GetRawMouseWheelDelta(); */
	unsigned short GetRawNextTouchEvent(); 
	/* Not yet functional
	void GetRawNFCCount(void); 
	void GetRawNFCData(void); 
	void GetRawNFCDataState(void); 
	void GetRawNFCName(void); 
	void GetRawNextNFCDevice(void);
	*/
	float GetRawOrientationW(void);
	float GetRawOrientationX(void);
	float GetRawOrientationY(void);
	float GetRawOrientationZ(void);
	unsigned short GetRawTouchCount(bool includeUnkown);
	RFTPoint GetRawTouchCurrentPos(unsigned short touchIndex); 
	RFTPoint GetRawTouchLastPos(unsigned short touchIndex);
	bool GetRawTouchReleased(unsigned short touchIndex);
	RFTPoint GetRawTouchStartPos(unsigned short touchIndex);
	float GetRawTouchTime(unsigned short touchIndex);
	TouchType GetRawTouchType(unsigned short touchIndex);
	int GetRawTouchValue(unsigned short touchIndex);

	//void SendRawNFCData(void); //Not functional
	void SetRawJoystickDeadZone(float value); 
	void SetRawMousePosition(RFTPoint Location);
	void SetRawMousePosition(float x, float y);
	void SetRawMouseVisible(bool isVisible);
	void SetRawTouchValue(unsigned short touchIndex, int value); 

private:
	/*static bool _touchIndex[8];
	static bool _joystickID[8];
	static bool _buttonID[16];*/

	static std::vector<bool*> _touchIndex;
	static std::vector<bool*> _joystickID;
	static std::vector<bool*> _buttonID;

	float _GetRawTouchCurrentX(unsigned short touchIndex);
	float _GetRawTouchCurrentY(unsigned short touchIndex);
	float _GetRawTouchLastX(unsigned short touchIndex);
	float _GetRawTouchLastY(unsigned short touchIndex);
	float _GetRawTouchStartX(unsigned short touchIndex);
	float _GetRawTouchStartY(unsigned short touchIndex);
};

