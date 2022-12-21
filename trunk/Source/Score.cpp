#include "Score.h"
#include "AGKCore.h"

Score::Score()
{
	_inOrder = true;

	for (int i = 0; i < 3; i++)
		_scoreLevels[i] = 0;
}

/*Score::Score(Text Settings, Image Parent)
{
	_inOrder = true;
} */

Score::~Score()
{}

void Score::Init()
{
	/*if (Header == Text("Score Levels"))
	{
		AGKCore Converter;
		for (int i = 0; i < 3; i++)
		{
			Text ScoreLevel;
			Index.SplitAtDelimeter(&ScoreLevel, &Index, ',');
			_scoreLevels[i] = Converter.Val(ScoreLevel);
		}
	} */
}