#include "Facebook.h"
#include "agk.h"

Facebook::Facebook(void)
{
}


Facebook::~Facebook(void)
{
}

#if ((OS == ANDROID) || (OS == IOS))

void Facebook::DestroyLikeButton(void)
{
	agk::FacebookDestroyLikeButton();
}

void Facebook::DownloadFriendsPhoto(unsigned int friendID)
{
	agk::FacebookDownloadFriendsPhoto(friendID);
}

Text Facebook::GetDownloadFile(void)
{

	return Text(agk::GetFacebookDownloadFile());
}

DownloadState Facebook::GetDownloadState(void)
{
	short stateValue = agk::GetFacebookDownloadState();

	if (stateValue < 0)
		return ERRORSTATE;

	else return (DownloadState) stateValue;
}

void Facebook::GetFriends(void)
{
	agk::FacebookGetFriends();
}

unsigned int Facebook::GetFriendsCount(void)
{
	return agk::FacebookGetFriendsCount();
}

Text Facebook::GetFriendsID(int index)
{
	return Text(agk::FacebookGetFriendsID(index));
}

Text Facebook::GetFreindsName(int index)
{
	return Text(agk::FacebookGetFriendsName(index));
}

DownloadState Facebook::GetFriendsState(void)
{
	int state = agk::FacebookGetFriendsState();

	switch (state)
	{
	case -1:
		return ERRORSTATE;
	case 0:
		return DOWNLOADING;
	case 1:
		return FINISHED;
	default:
		return NOACTIVITY;
    }

}

bool Facebook::GetLoggedIn(void)
{
	if (agk::GetFacebookLoggedIn() == 1)
		return true;

	return false;
}

Text Facebook::GetUserID(void)
{
	return Text(agk::FacebookGetUserID());
}

Text Facebook::GetUserName(void)
{
	return Text(agk::FacebookGetUserName());
}

void Facebook::Login(void)
{
	agk::FacebookLogin();
}

void Facebook::Logout(void)
{
	agk::FacebookLogout();
}

void Facebook::PostOnFriendsWall(Text ID, Text Link, Text Picture, Text Name, Text Caption, Text Description)
{
    char normalized[6][64] = {"", "", "", "", "", ""};
    
	strcpy(normalized[0], ID.GetCString());
    strcpy(normalized[1], Link.GetCString());
    strcpy(normalized[2], Picture.GetCString());
    strcpy(normalized[3], Name.GetCString());
    strcpy(normalized[4], Caption.GetCString());
    strcpy(normalized[5], Description.GetCString());
    
	agk::FacebookPostOnFriendsWall(normalized[0], normalized[1], normalized[2], normalized[3], normalized[4], normalized[5]);
}

void Facebook::PostOnMyWall(Text Link, Text Picture, Text Name, Text Caption, Text Description)
{
    char normalized[5][64] = {"", "", "", "", ""};
    
    strcpy(normalized[0], Link.GetCString());
    strcpy(normalized[1], Picture.GetCString());
    strcpy(normalized[2], Name.GetCString());
    strcpy(normalized[3], Caption.GetCString());
    strcpy(normalized[4], Description.GetCString());
	agk::FacebookPostOnMyWall(normalized[0], normalized[1], normalized[2], normalized[3], normalized[4]);
}

void Facebook::Setup(Text AppID)
{
    char normalized[64] = {""};
    
    strcpy(normalized, AppID.GetCString());
    
	agk::FacebookSetup(normalized);
}

void Facebook::ShowLikeButton(Text URL, int x, int y, int width, int height)
{
    char normalized[64] = {""};
    
    strcpy(normalized, URL.GetCString());
    
	agk::FacebookShowLikeButton(normalized, x, y, width, height);
}

#endif