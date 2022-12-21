#pragma once

#include "File.h"
#include "Text.h"
#include "Defines.h"

class Facebook
{
public:
	Facebook(void);
	~Facebook(void);

#if (OS != WINDOWS)
	void DestroyLikeButton(void);
	void DownloadFriendsPhoto(unsigned int friendID);

	Text GetDownloadFile(void);
	DownloadState GetDownloadState(void);
	void GetFriends(void);
	unsigned int GetFriendsCount(void);
	Text GetFriendsID(int index);
	Text GetFreindsName(int index);
	DownloadState GetFriendsState(void);
	bool GetLoggedIn(void);
	Text GetUserID(void);
	Text GetUserName(void);

	//void InviteFriend(); //Not supported

	void Login(void);
	void Logout(void);

	void PostOnFriendsWall(Text ID, Text Link, Text Picture, Text Name, Text Caption, Text Description);
	void PostOnMyWall(Text Link, Text Picture, Text Name, Text Caption, Text Description);

	void Setup(Text AppID);
	void ShowLikeButton(Text URL, int x, int y, int width, int height);
#endif
};

