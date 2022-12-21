#pragma once

#include "Point.h"
#include "Quaternion.h"

class Camera 
{
public:
	Camera(void);
	~Camera(void);

	RFTPoint GetAngles(void);
	float GetAngleX(void);
	float GetAngleY(void);
	float GetAngleZ(void);
	RFTPoint GetLocation(void);

	Quaternion GetQuat(void);
	float GetQuatW(void);
	float GetQuatX(void);
	float GetQuatY(void);
	float GetQuatZ(void);
	float GetX(void);
	float GetY(void);
	float GetZ(void);

	void MoveLocal(RFTPoint Location);
	void MoveLocalX(float x);
	void MoveLocalY(float y);
	void MoveLocalZ(float z);

	void RotateGlobal(RFTPoint RotateAmounts);
	void RotateGlobalX(float x);
	void RotateGlobalY(float y);
	void RotateGlobalZ(float z);
	void RotateLocal(RFTPoint RotateAmounts); 
	/*void RotateLocalX(float x);
	void RotateLocalY(float y);
	void RotateLocalZ(float z);*//////////Should just use full Rotate

	void SetFOV(float value);
	void SetLookAt(RFTPoint Location, float roll);
	void SetPosition(RFTPoint Location);
	void SetPosition(float x, float y, float z);
	void SetRange(float near, float far);
	void SetRotation(RFTPoint RotationAmounts);
	void SetRotation(float x, float y, float z);
	void SetRotationQuat(Quaternion Rotation);
	void SetRotationQuat(float w, float x, float y, float z);

private:

	unsigned int _cameraID;
};

