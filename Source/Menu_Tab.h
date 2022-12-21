#ifndef _MENU_TAB_H_
#define _MENU_TAB_H_

#include "Sprite.h"
#include "agk.h"
#include "Color.h"
#include "Menu_Module.h"
#include <vector>

class Tab : public Sprite
{
public:
	Tab();
	Tab(int tabnum, float offset, unsigned int commonAtlasID);
	~Tab();
	
	void Init();
	bool ClickedOnPreview();
	int GetTabNum();
	int GetSongSelected();
	void Delete();
	void CreateModules(int);
	void Update(float y);
	void Stop();
	void Hide();
	void HideList();
	void RevealList();
	//float Height();
	float Bottom();
	//Sprite* TabSprite();
	void Show();
	bool UpdateMouseClick(RFTPoint MousePosition);
	void UpdateScores(std::vector<int> songIndexes, std::vector<unsigned short> scores);
	//void PlayPreview(int song);
private:
	int tab_num;
	//int num_modules;
	float _titlebar_height;
	//Sprite* _tabsprite;
	std::vector<Module*> _Module;
	Text *_TabText;
	Sprite *_Selected;
	unsigned int _commonAtlasID;
	unsigned int _moduleNumber;
};
#endif