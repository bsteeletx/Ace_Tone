#ifndef _MENU_Module_H_
#define _MENU_Module_H_

#include "Sprite.h"
#include "Color.h"
#include "agk.h"
#include "InputPointer.h"
#include "Menu_Song.h"
#include <vector>

class Module : public Sprite
{
public:
	Module(int tabnum, int modnum, unsigned int commonAtlasID);
	~Module();
	
	void Init(float offsetY);
	bool CheckForHits(RFTPoint MouseLoc);
	bool ClickedPreview();
	float GetModuleHeight();
	unsigned int GetSongNumber();
	void Hide();
	void Reveal();
	void Update(float y);
	void Stop();
	//float Title_Pos();
	float Bottom();
	float GetPos();
	void UpdateScores(std::vector<int> songIndexes, std::vector<unsigned short> songScores);
private:
	std::vector<MenuSong*> _list; //list of songs in the module (dynamic)
	//Sprite* _modtitle;
	int _tab_num;
	int _modnum;
	//int _numsongs;
	float current_pos;
	float _height;
	Text* ModText;
	unsigned int _commonAtlasID;
	unsigned int _hitSong;
	bool _clickedPreview;
};
#endif