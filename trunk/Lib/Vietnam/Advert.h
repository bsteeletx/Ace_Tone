#ifndef _ADVERT_H_
#define _ADVERT_H_

#include "Text.h"
#include "Point.h"

class Advert
{
public:
	Advert(void);
	~Advert(void);
	Advert(int horzPos, int vertPos, Text AdMobID, Text InneractiveID, float offsetX = 0.0f, float offsetY = 0.0f, bool test = false);

	void Delete();
	
	void RequestRefresh(void);

	//SetLocationEx does not seem to be available for current version, maybe next one?
	void SetLocation(unsigned short horz, unsigned short vert, float width);//, float offsetX = 0.0f, float offsetY = 0.0f);
	void SetPosition(RFTPoint Location, float width);
	void SetPosition(float x, float y, float width);
	void SetVisible(bool isVisible);

private:
	void _SetAdMobDetails(Text ID);
	void _SetInneractiveDetails(Text Code);
};
#endif
