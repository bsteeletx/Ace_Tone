#ifndef _3DPOINTLIGHT_H_
#define _3DPOINTLIGHT_H_

#include "Point.h"
#include "Color.h"

class PointLight
{
public:
	PointLight(void);
	PointLight(RFTPoint Location, float radius, Color Value);
	~PointLight(void);
	PointLight(float x, float y, float z, float radius, Color Value);

	void Clear(void);

	void Delete();

	bool GetExists(void);

	void SetColor(Color Value);
	void SetPosition(RFTPoint Location);
	void SetPosition(float x, float y, float z);
	void SetRadius(float value);

private:
	static unsigned int _lightCounter;
	unsigned int _lightID;
};

#endif