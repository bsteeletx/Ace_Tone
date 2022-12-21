#pragma once
class Quaternion
{
public:
	Quaternion(void);
	~Quaternion(void);
	Quaternion(float w, float x, float y, float z);

	float GetW(void);
	float GetX(void);
	float GetY(void);
	float GetZ(void);

	void ResetAllTo(float w, float x, float y, float z);
	
	void SetW(float value);
	void SetX(float value);
	void SetY(float value);
	void SetZ(float value);

private:
	float _wRot, _xRot, _yRot, _zRot;
};

