#include "MultiplayerBroadcast.h"
#include "agk.h"

Broadcast::Broadcast()
{
	_CreateListener();
}

Broadcast::~Broadcast()
{

}

///////////////////////////////////
// Deletes a broadcast listener and frees up the port for something else to listen on it.
////////////////////////////////
void Broadcast::DeleteListener()
{
	agk::DeleteBroadcastListener(_listenerID);
}

/////////////////////////////////////
// Checks a broadcast listener for any broadcasts. 
// Returns 0 if nothing has been received. 
// Returns a message ID if something has been received, 
// you can access the contents of this message using network message commands. 
// The message must be deleted when you have finished reading from it.
///////////////////////////////////
int Broadcast::GetMessage()
{
	return agk::GetBroadcastMessage(_listenerID);
}

///////////////////////////////
// Broadcasts are special network communications as they do not use a destination address and are instead received by all devices on a network.
// Broadcast packets are not forwarded by routers so can only be used on the local area network, 
// or more specifically the local subnet.
// This can be useful for discovering devices as one device can send a broadcast packet containing its IP address and another device can pick it up, 
// read the IP and connect back to the first device to create a two - way connection.
// AGK networks are broadcast in this manner on port 45631 and send a packet containing the name of a network that has been hosted by another AGK device.
// By using a broadcast listener you can pick these messages up, 
// extract the network names and display them to the user for them to choose which network they want to connect to.
// Returns an ID you can use to interact with this broadcast listener.
///////////////////////////////////
void Broadcast::_CreateListener()
{
	_listenerID = agk::CreateBroadcastListener(45631);
}