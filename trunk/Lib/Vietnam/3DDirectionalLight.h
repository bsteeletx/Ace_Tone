#ifndef _3DDIRECTIONALLIGHT_H_
#define _3DDIRECTIONALLIGHT_H_

#include "Color.h"
#include "Vector.h"

class DirectionalLight
{
public:
	DirectionalLight(void);
	~DirectionalLight(void);
	DirectionalLight(Vector Direction, Color Value);

	void Clear(void);

	void Delete();

	bool GetExists(void);

	void SetColor(Color Value);
	void SetDirection(Vector Direction);

private:
	static unsigned int _lightCounter;
	unsigned int _lightID;
};

#endif