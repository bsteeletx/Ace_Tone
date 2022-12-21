#ifndef _MULTIPLAYERMESSAGE_H_
#define _MULTIPLAYERMESSAGE_H_

#include "Text.h"

class Message
{
public:
	Message();
	~Message();

	void AddNetworkFloat(float value);
	void AddNetworkInt(int value);
	void AddNetworkString(Text Value);

	void DeleteNetwork(void);

	unsigned int GetNetwork(unsigned int networkID);
	float GetNetworkFloat(void);
	unsigned int GetNetworkFromClient(void);
	Text GetNetworkFromIP(void);
	int GetNetworkInt(void);
	Text GetNetworkString(void);

	void SendNetwork(unsigned int networkID, unsigned int clientID);

private:
	unsigned int _messageID;

	unsigned int _CreateNetwork(void);
};
#endif