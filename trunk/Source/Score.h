#ifndef _SCORE_H_
#define _SCORE_H_

#include "ScoreRecord.h"
#include <vector>

class Score
{
public:
	Score();
	//Score(Text CorrectNotes, Text TierLogic, Image Parent);
	~Score();

	void Init();

	void IncreaseScore(int chordNote);

private:
	//unsigned short _score;
	//std::vector<Text> _SuccessNotes;
	bool _inOrder;

	int _scoreLevels[3];

	//ScorePick _VisualScore[3];
};

#endif