#include "Twitter.h"
#include "AGKCore.h"
#include "agk.h"

Twitter::Twitter()
{}

Twitter::Twitter(Text Key, Text Secret)
{
	char twitterKey[128] = {NULL};
	char twitterSecret[128] = {NULL};
	strcpy(twitterKey, Key.GetCString());
	strcpy(twitterSecret, Secret.GetCString());
	agk::TwitterSetup(twitterKey, twitterSecret);
}


Twitter::~Twitter(void)
{
}

void Twitter::Message(Text Message)
{
	char tweet[256] = {NULL};
	AGKCore Conversion;
	
	if (Conversion.Len(Message) <= 140)
	{
		strcpy(tweet, Message.GetCString());
		agk::TwitterMessage(tweet);
	}
}
