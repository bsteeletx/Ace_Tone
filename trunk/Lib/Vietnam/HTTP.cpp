#include "agk.h"
#include "HTTP.h"

HTTP::HTTP()
{
	_httpID = _CreateConnection();
}

HTTP::~HTTP()
{
	//deleteConnection();
}

void HTTP::CloseConnection()
{
	agk::CloseHTTPConnection(_httpID);
}

void HTTP::DeleteConnection()
{
	agk::DeleteHTTPConnection(_httpID);
}

int HTTP::GetFile(Text CompleteURLPath, Text LocalStorage, Text PostData)
{
	return agk::GetHTTPFile(_httpID, CompleteURLPath.GetCString(), LocalStorage.GetCString(), PostData.GetCString());
}

int HTTP::GetFile(Text CompleteURLPath, Text LocalStorage)
{
	return agk::GetHTTPFile(_httpID, CompleteURLPath.GetCString(), LocalStorage.GetCString());
}

bool HTTP::GetFileComplete()
{
	if (agk::GetHTTPFileComplete(_httpID) == 1)
		return true;

	return false;
}

float HTTP::GetFileProgress()
{
	return agk::GetHTTPFileProgress(_httpID);
}

//////////////////////////
// Returns true if the device is connected to the internet, 
// false if not.
///////////////////////
bool HTTP::GetInternetState()
{
	return (bool)agk::GetInternetState();
}

Text HTTP::GetResponse()
{
	return Text(agk::GetHTTPResponse(_httpID));
}

bool HTTP::GetResponseReady()
{
	if (agk::GetHTTPResponseReady(_httpID) == 1)
		return true;

	return false;
}

///////////////////////////
// Opens the default browser of the current platform with points it to the page given.
//////////////////////////
void HTTP::OpenBrowser(Text URL)
{
	agk::OpenBrowser(URL.GetCString());
}

int HTTP::SendFile(Text Page, Text PostData, Text LocalFile)
{
	return agk::SendHTTPFile(_httpID, Page.GetCString(), PostData.GetCString(), LocalFile.GetCString());
}

Text HTTP::SendRequest(Text Page)
{
	return Text(agk::SendHTTPRequest(_httpID, Page.GetCString()));
}

Text HTTP::SendRequest(Text Page, Text PostData)
{
	return Text(agk::SendHTTPRequest(_httpID, Page.GetCString(), PostData.GetCString()));
}

int HTTP::SendRequestASync(Text Page, Text PostData)
{
	return agk::SendHTTPRequestASync(_httpID, Page.GetCString(), PostData.GetCString());
}

int HTTP::SendRequestASync(Text Page)
{
	return agk::SendHTTPRequestASync(_httpID, Page.GetCString());
}

int HTTP::SetHost(Text Host, bool isSecure)
{
	if (isSecure)
		return agk::SetHTTPHost(_httpID, Host.GetCString(), 1);

	return agk::SetHTTPHost(_httpID, Host.GetCString(), 0);
}

int HTTP::SetHost(Text Host, bool isSecure, Text Username, Text Password)
{
	if (isSecure)
		return agk::SetHTTPHost(_httpID, Host.GetCString(), 1, Username.GetCString(), Password.GetCString());

	return agk::SetHTTPHost(_httpID, Host.GetCString(), 0, Username.GetCString(), Password.GetCString());
}

unsigned int HTTP::_CreateConnection()
{
	return agk::CreateHTTPConnection();
}