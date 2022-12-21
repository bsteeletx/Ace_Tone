#ifndef _Menu_Song_H_
#define _Menu_Song_H_

#include "Sprite.h"
#include "agk.h"
#include "Music.h"

class MenuSong : public Sprite
{
public:
	MenuSong(int songum, float yOffset, int modnum, int tabnum, unsigned int commonAtlasID);
	~MenuSong();

	void Init();
	bool ClickedPreview();
	void Hide();
	void Reveal();
	void Update(float mouse);
	bool UpdateMouseClick(RFTPoint MouseLoc);
	void UpdateScore(unsigned short score);
	void Stop();
	//float GetHeight();
	//float Y();
	float GetPos();
	int GetSongNum();
private:
	//Sprite* _sprite;
	Sprite* _preview;
	Sprite *_BuyIt;
	int SongNum;
	int modnum;
	int tabnum;
	float current_pos;
	//float size;
	Text* SongName;
	Text* Artist;
	Sprite *_RecordScore[3];
	unsigned int _commonAtlasID;
	bool _clickedPreview;
	Text *_iTunesPurchaseURL;
	float _yOffset;
	
	Music *_PreviewSong;
};
#endif