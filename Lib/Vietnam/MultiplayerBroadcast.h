#ifndef _MULTIPLAYERBROADCAST_H_
#define _MULTIPLAYERBROADCAST_H_

//#include "Multiplayer.h"

class Broadcast
{
public:
	Broadcast();
	~Broadcast();

	void DeleteListener();

	int GetMessage(); 

private:
	int _listenerID;

	void _CreateListener();
};
#endif