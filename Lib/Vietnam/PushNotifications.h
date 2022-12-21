#ifndef _PUSHNOTIFICATIONS_H_
#define _PUSHNOTIFICATIONS_H_

#include "Text.h"

class PushNotifications
{
public:
	PushNotifications();
	~PushNotifications();

	Text GetToken();
	
private:
	bool _Setup(); 
};

#endif