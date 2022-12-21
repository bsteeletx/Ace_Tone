#ifndef _2DPHYSICSFORCE_H_
#define _2DPHYSICSFORCE_H_

#include "Point.h"

class Force
{
public:
	Force();
	~Force();
	Force(RFTPoint Location, float power, float limit, float range, bool fade);

	void Delete();

	void SetPosition(RFTPoint Location);
	void SetPower(float powerInNewtons);
	void SetRange(float range);

private:
	unsigned int _forceID;

	void _Create(RFTPoint Location, float power, float limit, float range, bool fade);
};
#endif