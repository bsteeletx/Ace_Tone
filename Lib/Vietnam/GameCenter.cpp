#include "GameCenter.h"
#include "AGKTime.h"
#include "AGKCore.h"
#include "Error.h"
#include "agk.h"

GameCenter::GameCenter(Text iTunesBoardID)
{
	//check to see if game center exists
	if (!_GetExists())
		return;
	
	//if not, do setup
	_Setup(); //might need to do this first
	//then login
	_Login();

	_GameCenterID = iTunesBoardID;
}

GameCenter::~GameCenter()
{

}

/*
void GameCenter::AchievementsReset()
{

}
*/

/////////////////////////////
// Shows the user their achievements and progress
////////////////////////////
void GameCenter::AchievementsShow()
{
	agk::GameCenterAchievementsShow();
}

////////////////////////////////
// Shows the user the named leaderboard, 
// the name must match the Leaderboard ID given to your board in iTunes connect
////////////////////////////////
void GameCenter::ShowLeaderBoard()
{
	agk::GameCenterShowLeaderBoard(_GameCenterID.GetCString());
}

/////////////////////////////////
// Change the users progress on reaching a named achievement, 
// the name must match the Achievement ID given to the achievement in iTunes Connect.
/////////////////////////////////////
void GameCenter::SubmitAchievement(Text AchievementID, unsigned short percentComplete)
{
	agk::GameCenterSubmitAchievement(AchievementID.GetCString(), percentComplete);
}

////////////////////////////////
// Submits a score to a named leader board, 
// this must match the Leaderboard ID given to your board in iTunes connect
///////////////////////////////////
void GameCenter::SubmitScore(unsigned int score)
{
	agk::GameCenterSubmitScore(score, _GameCenterID.GetCString());
}

////////////////////////////////
// Returns true if the current platform supports Game Center. Currently this will only return true on iOS.
///////////////////////////////
bool GameCenter::_GetExists()
{
	return (bool)agk::GetGameCenterExists();
}

///////////////////////////////////
// Will return true if the user is logged in to Game Center
// The login process is Asynchronous so after calling GameCenterLogin it may take a few seconds for this command to return true
///////////////////////////////////
bool GameCenter::_GetLoggedIn()
{
	return (bool)agk::GetGameCenterLoggedIn();
}

///////////////////////////////
// Call this once to log the user in to Game Center, 
// if they are already logged in to the Game Center app then this happens in the background and does not interrupt the user, 
// otherwise a popup will appear asking them to log in
///////////////////////////////
void GameCenter::_Login()
{
	agk::GameCenterLogin();

	//don't return until logged in
	AGKTime Timer;
	Text CurrentTime = Timer.GetCurrent();
	Text CurrentDate = Timer.GetCurrentDate();
	AGKCore Converter;
	Error ErrorLog;
	
	unsigned short secondsFromUnix = 0;
	unsigned short startTime = 0;
	int unixTime = 0;

	//this SOOOO needs to be tested
	unixTime = Timer.GetUnixFromDate(Converter.Val(Converter.Left(CurrentDate, 4)), Converter.Val(Converter.Mid(CurrentDate, 5, 2)), Converter.Val(Converter.Right(CurrentDate, 2)),
		Converter.Val(Converter.Left(CurrentTime, 2)), Converter.Val(Converter.Mid(CurrentTime, 3, 2)), Converter.Val(Converter.Right(CurrentTime, 2)));
	startTime = Timer.GetSecondsFromUnix(unixTime);
	secondsFromUnix = startTime;
	
	while (!_GetLoggedIn())
	{
		unixTime = Timer.GetUnixFromDate(Converter.Val(Converter.Left(CurrentDate, 4)), Converter.Val(Converter.Mid(CurrentDate, 5, 2)), Converter.Val(Converter.Right(CurrentDate, 2)),
			Converter.Val(Converter.Left(CurrentTime, 2)), Converter.Val(Converter.Mid(CurrentTime, 3, 2)), Converter.Val(Converter.Right(CurrentTime, 2)));

		secondsFromUnix = Timer.GetSecondsFromUnix(unixTime);
		
		if (secondsFromUnix - startTime > 30) //greater than 30 seconds, return?
		{
			ErrorLog.Log(Text("GameCenter Timed Out!"));
			break;
		}
	}
}

////////////////////////////////
// Call this once to setup your app for further Game Center commands
///////////////////////////////
void GameCenter::_Setup()
{
	agk::GameCenterSetup();
}