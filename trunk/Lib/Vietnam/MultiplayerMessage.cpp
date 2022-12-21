#include "MultiplayerMessage.h"
#include "agk.h"

Message::Message(void)
{
	_messageID = _CreateNetwork();
}

Message::~Message(void)
{
	//deleteNM();
}

void Message::AddNetworkFloat(float value)
{
	agk::AddNetworkMessageFloat(_messageID, value);
}

void Message::AddNetworkInt(int value)
{
	agk::AddNetworkMessageInteger(_messageID, value);
}

void Message::AddNetworkString(Text Value)
{
	agk::AddNetworkMessageString(_messageID, Value.GetCString());
}

unsigned int Message::GetNetwork(unsigned int networkID)
{
	return agk::GetNetworkMessage(networkID);
}

float Message::GetNetworkFloat(void)
{
	return agk::GetNetworkMessageFloat(_messageID);
}

unsigned int Message::GetNetworkFromClient(void)
{
	return agk::GetNetworkMessageFromClient(_messageID);
}

Text Message::GetNetworkFromIP(void)
{
	return Text(agk::GetNetworkMessageFromIP(_messageID));
}

int Message::GetNetworkInt(void)
{
	return agk::GetNetworkMessageInteger(_messageID);
}

Text Message::GetNetworkString(void)
{
	return Text(agk::GetNetworkMessageString(_messageID));
}

void Message::SendNetwork(unsigned int networkID, unsigned int clientID)
{
	agk::SendNetworkMessage(networkID, clientID, _messageID);
}

unsigned int Message::_CreateNetwork(void)
{
	return agk::CreateNetworkMessage();
}

void Message::DeleteNetwork(void)
{
	agk::DeleteNetworkMessage(_messageID);
}