#include "RateApp.h"
#include "Defines.h"
#include "agk.h"

RateApp::RateApp()
{
#if (OS == IOS)
	agk::RateApp(IOS_GAME_ID);
#endif
}


RateApp::~RateApp(void)
{
}
