#ifndef _MULTIPLAYER_H_
#define _MULTIPLAYER_H_

#include "Text.h"
#include "MultiplayerBroadcast.h"
#include "MultiplayerMessage.h"
#include <vector>

//class Broadcast;
//class Message;

class Multiplayer
{
public:
	Multiplayer();
	~Multiplayer();
	Multiplayer(Text NetworkName, Text MyName);
	Multiplayer(Text NetNameOrIP, Text MyName, unsigned short portNumber = 1025);

	/////////////////////Properties
	void CloseNetwork(void);
	
	void DeleteNetworkClient(unsigned int clientID);

	bool GetNetworkClientDisconnected(unsigned int client);
	float GetNetworkClientFloat(unsigned int client);
	int GetNetworkClientInt(unsigned int client);
	Text GetNetworkClientName(unsigned int client);
	short GetNetworkClientPing(unsigned int client);
	Text GetNetworkClientUserData(unsigned int client);
	unsigned int GetNetworkFirstClient(void);
	unsigned int GetNetworkMyClientID(void);
	unsigned int GetNetworkNextClient(void);
	short GetNetworkNumClients(void);
	unsigned int GetNetworkServerID(void);

	void SetNetworkClientUserData(unsigned int client, unsigned int index, int value);
	void SetNetworkLocalFloat(Text VariableName, float value, bool resetAfterRead);
	void SetNetworkLocalInt(Text VariableName, int value, bool resetAfterRead);
	
	////////////////Setup
	bool IsNetworkActive(void);

	void SetNetworkLatency(unsigned short latency);
	void SetNetworkNoMoreClients(void);

	Broadcast Listener;
	std::vector<Message> Messages;

protected:
	unsigned int _networkID;
	unsigned short _port;

private:
	bool _isHost;

	bool _IsANum(char test);
};
#endif