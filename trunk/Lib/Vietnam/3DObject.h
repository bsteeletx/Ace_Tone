#ifndef _3DOBJECT_H_
#define _3DOBJECT_H_

#include "Defines.h"
#include "Image.h"
#include "Color.h"
#include "Vector.h"
#include "Quaternion.h"
#include "Text.h"

//class Text;

class Object
{
public:
	Object(void);
	~Object(void);
	Object(Text Filename, float height = 1.0f);

	bool checkForCollisionsWith(Object Other);
	Object *Clone(void);

	void Delete();

	RFTPoint Get3DVectorFromScreen(void);
	float Get3DVectorXFromScreen(void);
	float Get3DVectorYFromScreen(void);
	float Get3DVectorZFromScreen(void);
	RFTPoint GetAngle(void);
	float GetAngleX(void);
	float GetAngleY(void);
	float GetAngleZ(void);
	CullMode GetCullMode(void);
	DepthMode GetDepthReadMode(void);
	DepthMode GetDepthWrite(void);
	RFTPoint GetDistanceFrom(Object Other);
	bool GetExists(void);
	float GetHeight(void);	
	unsigned int GetID(void);
	bool GetInScreen(void);
	float GetLength(void);	
	ObjectType GetType(void);
	Quaternion GetQuat(void);
	float GetQuatW(void);
	float GetQuatX(void);
	float GetQuatY(void);
	float GetQuatZ(void);
	unsigned int GetTextureID(void);
	TransparencyMode GetTransparency(void);
	bool GetVisible(void);
	RFTPoint GetLocation(void);
	float GetWidth(void);
	float GetX(void);
	float GetY(void);
	float GetZ(void);

	//seems too dangerous to use
	//Object *instance(void);
	void MoveLocal(RFTPoint Location);
	void MoveLocalX(float x);
	void MoveLocalY(float y);
	void MoveLocalZ(float z);

	unsigned short RayCast(RFTPoint StartPos, RFTPoint EndPos); 
	void RotateGlobal(RFTPoint RotationAmounts);
	void RotateGlobalX(float x);
	void RotateGlobalY(float y);
	void RotateGlobalZ(float z);
	void RotateLocal(RFTPoint RotationAmounts);
	void RotateLocalX(float x);
	void RotateLocalY(float y);
	void RotateLocalZ(float z);

	void SetCollisionMode(bool isOn);
	void SetColor(Color DiffuseColor);
	void SetCullMode(CullMode value);
	void SetDepthReadMode(DepthMode value);
	void SetDepthWrite(DepthMode value);
	void SetImage(Image ForObject, unsigned short texStage);
	void SetLightMode(bool lightingOn);
	void SetLookAt(RFTPoint LookLocation);
	void SetLookAt(RFTPoint LookLocation, float roll);
	void SetPosition(RFTPoint Location);
	void SetPosition(float x, float y, float z);
	void SetRotation(RFTPoint RotationAmounts);
	void SetRotation(float pitch, float yaw, float roll);
	void SetRotationQuat(Quaternion Values);
	void SetRotationQuat(float w, float x, float y, float z);
	void SetScale(RFTPoint ScaleValues);
	void SetShader(unsigned int shaderID);
	void SetTransparency(TransparencyMode Value);
	void SetVisible(bool isVisible);
	void SetX(float x);
	void SetY(float y);
	void SetZ(float z);
	unsigned short SphereCast(RFTPoint StartPos, RFTPoint EndPos, float radius, bool checkForAll = false); 
	unsigned short SphereSlide(RFTPoint StartPos, RFTPoint EndPos, float radius, bool checkForAll = false);

protected:
	unsigned int _objectID;
	ObjectType _ObjectShape;
	
	unsigned int _textureID;
	float _thisLength;
	float _thisHeight;
	float _thisWidth;
};

class BoxObject :
	public Object
{
public:
	BoxObject();
	~BoxObject();
	BoxObject(float width, float height, float length);
};

class Cone :
	public Object
{
public:
	Cone();
	~Cone();
	Cone(float height, float diameter, int segments);
};

class Cylinder :
	public Object
{
public:
	Cylinder();
	~Cylinder();
	Cylinder(float height, float diameter, int segments);
};

class Plane :
	public Object
{
public:
	Plane();
	~Plane();
	Plane(float width, float height);
};

class Sphere :
	public Object
{
public:
	Sphere();
	~Sphere();
	Sphere(float diameter, int rows, int columns);
};

#endif