#include "PushNotifications.h"
#include "agk.h"

PushNotifications::PushNotifications()
{
	_Setup();
}

PushNotifications::~PushNotifications()
{

}

Text PushNotifications::GetToken()
{
	return Text(agk::GetPushNotificationToken());
}

bool PushNotifications::_Setup()
{
	return (bool)agk::PushNotificationSetup();
}