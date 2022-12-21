#pragma once

#include "Text.h"

class GameCenter
{
public:
	GameCenter(Text iTunesBoardID);
	~GameCenter();

	//void AchievementsReset(); 
	void AchievementsShow();

	void ShowLeaderBoard(); 
	void SubmitAchievement(Text AchievementID, unsigned short percentComplete); 
	void SubmitScore(unsigned int score); 

private:
	bool _GetExists(); 
	bool _GetLoggedIn(); 

	void _Login(); 

	void _Setup(); 

	Text _GameCenterID;

	//might need some other functions like load achievements (from a text file).
};