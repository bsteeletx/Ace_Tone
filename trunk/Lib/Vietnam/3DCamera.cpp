#include "3DCamera.h"
#include "agk.h"

Camera::Camera(void)
{
	_cameraID = 1;
}

Camera::~Camera(void)
{
}

RFTPoint Camera::GetAngles(void)
{
	return RFTPoint(agk::GetCameraAngleX(_cameraID), agk::GetCameraAngleY(_cameraID), agk::GetCameraAngleZ(_cameraID));
}

float Camera::GetAngleX(void)
{
	return agk::GetCameraAngleX(_cameraID);
}

float Camera::GetAngleY(void)
{
	return agk::GetCameraAngleY(_cameraID);
}

float Camera::GetAngleZ(void)
{
	return agk::GetCameraAngleZ(_cameraID);
}

RFTPoint Camera::GetLocation(void)
{
	return RFTPoint(agk::GetCameraX(_cameraID), agk::GetCameraY(_cameraID), agk::GetCameraZ(_cameraID));
}

Quaternion Camera::GetQuat(void)
{
	return Quaternion(GetQuatW(), GetQuatX(), GetQuatY(), GetQuatZ());
}

float Camera::GetQuatW(void)
{
	return agk::GetCameraQuatW(_cameraID);
}

float Camera::GetQuatX(void)
{
	return agk::GetCameraQuatX(_cameraID);
}

float Camera::GetQuatY(void)
{
	return agk::GetCameraQuatY(_cameraID);
}

float Camera::GetQuatZ(void)
{
	return agk::GetCameraQuatZ(_cameraID);
}

float Camera::GetX(void)
{
	return agk::GetCameraX(_cameraID);
}

float Camera::GetY(void)
{
	return agk::GetCameraY(_cameraID);
}

float Camera::GetZ(void)
{
	return agk::GetCameraZ(_cameraID);
}

void Camera::MoveLocal(RFTPoint Location)
{
	agk::MoveCameraLocalX(_cameraID, Location.GetX());
	agk::MoveCameraLocalY(_cameraID, Location.GetY());
	agk::MoveCameraLocalZ(_cameraID, Location.GetZ());
}

void Camera::MoveLocalX(float x)
{
	agk::MoveCameraLocalX(_cameraID, x);
}

void Camera::MoveLocalY(float y)
{
	agk::MoveCameraLocalY(_cameraID, y);
}

void Camera::MoveLocalZ(float z)
{
	agk::MoveCameraLocalZ(_cameraID, z);
}

void Camera::RotateGlobal(RFTPoint RotateAmounts)
{
	agk::RotateCameraGlobalX(_cameraID, RotateAmounts.GetX());
	agk::RotateCameraGlobalY(_cameraID, RotateAmounts.GetY());
	agk::RotateCameraGlobalZ(_cameraID, RotateAmounts.GetZ());
}

void Camera::RotateGlobalX(float x)
{
	agk::RotateCameraGlobalX(_cameraID, x);
}

void Camera::RotateGlobalY(float y)
{
	agk::RotateCameraGlobalY(_cameraID, y);
}

void Camera::RotateGlobalZ(float z)
{
	agk::RotateCameraGlobalZ(_cameraID, z);
}

void Camera::RotateLocal(RFTPoint RotateAmounts)
{
	agk::RotateCameraLocalX(_cameraID, RotateAmounts.GetX());
	agk::RotateCameraLocalY(_cameraID, RotateAmounts.GetY());
	agk::RotateCameraLocalZ(_cameraID, RotateAmounts.GetZ());
}

void Camera::SetFOV(float value)
{
	agk::SetCameraFOV(_cameraID, value);
}

void Camera::SetLookAt(RFTPoint Location, float roll)
{
	agk::SetCameraLookAt(_cameraID, Location.GetX(), Location.GetY(), Location.GetZ(), roll);
}

void Camera::SetPosition(RFTPoint Location)
{
	agk::SetCameraPosition(_cameraID, Location.GetX(), Location.GetY(), Location.GetZ());
}

void Camera::SetPosition(float x, float y, float z)
{
	agk::SetCameraPosition(_cameraID, x, y, z);
}

void Camera::SetRange(float nearValue, float farValue)
{
	agk::SetCameraRange(_cameraID, nearValue, farValue);
}
	
void Camera::SetRotation(RFTPoint RotationAmounts)
{
	agk::SetCameraRotation(_cameraID, RotationAmounts.GetX(), RotationAmounts.GetY(), RotationAmounts.GetZ());
}

void Camera::SetRotation(float x, float y, float z)
{
	agk::SetCameraRotation(_cameraID, x, y, z);
}

void Camera::SetRotationQuat(Quaternion Rotation)
{
	agk::SetCameraRotationQuat(_cameraID, Rotation.GetW(), Rotation.GetX(), Rotation.GetY(), Rotation.GetZ());
}

void Camera::SetRotationQuat(float w, float x, float y, float z)
{
	agk::SetCameraRotationQuat(_cameraID, w, x, y, z);
}