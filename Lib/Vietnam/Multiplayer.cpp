#include "Multiplayer.h"
#include "agk.h"

Multiplayer::Multiplayer()
{
	_networkID = 0;
	_port = 1025;
	_isHost = false;
}

Multiplayer::~Multiplayer()
{
	/*if (IsActive())
		close();*/
}


//host
Multiplayer::Multiplayer(Text NetworkName, Text MyName)
{
	while (!IsNetworkActive())
	{
		_networkID = agk::HostNetwork(NetworkName.GetCString(), MyName.GetCString(), _port);
		if (!_networkID)
			_port++;
	}

	_isHost = true;
}

//join
Multiplayer::Multiplayer(Text NetNameOrIP, Text MyName, unsigned short portNumber)
{
	if (_IsANum(NetNameOrIP.GetChar(0)))
		_networkID = agk::JoinNetwork(NetNameOrIP.GetCString(), portNumber, MyName.GetCString());
	else
		_networkID = agk::JoinNetwork(NetNameOrIP.GetCString(), MyName.GetCString());
}

///////////////////////////////////
// Deletes a disconnected client from the client list. 
// If this function is called on a client that is not disconnected it will produce an error and not affect the client. 
// Does not delete the client immediately, 
// the background code may take a few frames to get around to deleting it. 
// Calling this command multiple times on a disconnected client should not cause a problem.
///////////////////////////////////
void Multiplayer::DeleteNetworkClient(unsigned int clientID)
{
	agk::DeleteNetworkClient(_networkID, clientID);
}

unsigned int Multiplayer::GetNetworkServerID(void)
{
	return agk::GetNetworkServerID(_networkID);
}

bool Multiplayer::IsNetworkActive(void)
{
	if (agk::IsNetworkActive(_networkID) == 1)
		return true;
	
	return false;
}

void Multiplayer::SetNetworkLatency(unsigned short latency)
{
	if (latency > 0.0f)
		agk::SetNetworkLatency(_networkID, latency);
}

void Multiplayer::SetNetworkLocalFloat(Text VariableName, float value, bool reSetAfterRead)
{
	if (reSetAfterRead)
		agk::SetNetworkLocalFloat(_networkID, VariableName.GetCString(), value, 1);
	else
		agk::SetNetworkLocalFloat(_networkID, VariableName.GetCString(), value, 0);
}

void Multiplayer::SetNetworkLocalInt(Text VariableName, int value, bool reSetAfterRead)
{
	if (reSetAfterRead)
		agk::SetNetworkLocalInteger(_networkID, VariableName.GetCString(), value, 1);
	else
		agk::SetNetworkLocalInteger(_networkID, VariableName.GetCString(), value, 0);
}

void Multiplayer::SetNetworkNoMoreClients(void)
{
	agk::SetNetworkNoMoreClients(_networkID);
}

void Multiplayer::CloseNetwork(void)
{
	agk::CloseNetwork(_networkID);
}

bool Multiplayer::_IsANum(char text)
{
	switch (text)
	{
	case '0': return true;
	case '1': return true;
	case '2': return true;
	case '3': return true;
	case '4': return true;
	case '5': return true;
	case '6': return true;
	case '7': return true;
	case '8': return true;
	case '9': return true;
	default: return false;
	}
}