#include "Error.h"
#include "agk.h"

Error::Error(void)
{
}


Error::~Error(void)
{
}

Text Error::GetLast(void)
{
	return Text(agk::GetLastError());
}

bool Error::GetOccurred(void)
{
	if (agk::GetErrorOccurred() == 1)
		return true;
	
	return false;
}

void Error::Log(Text Error)
{
	char logMessage[64];

	if (Error.GetLength() < 64)
		strcpy(logMessage, Error.GetCString());

	agk::Log(logMessage);
}

void Error::SetMode(unsigned short mode)
{
	agk::SetErrorMode(mode);
}