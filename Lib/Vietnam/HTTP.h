#ifndef _HTTP_H_
#define _HTTP_H_

#include "Text.h"

class HTTP
{
public:
	HTTP();
	~HTTP();

	void CloseConnection();

	void DeleteConnection();

	int GetFile(Text CompleteURLPath, Text LocalStorage, Text PostData);
	int GetFile(Text CompleteURLPath, Text LocalStorage);
	bool GetFileComplete();
	float GetFileProgress();
	bool GetInternetState(); 
	Text GetResponse();
	bool GetResponseReady();

	void OpenBrowser(Text URL);

	int SendFile(Text Page, Text PostData, Text LocalFile);
	Text SendRequest(Text Page);
	Text SendRequest(Text Page, Text PostData);
	int SendRequestASync(Text Page, Text PostData);
	int SendRequestASync(Text Page);
	int SetHost(Text Host, bool isSecure);
	int SetHost(Text Host, bool isSecure, Text Username, Text Password);

private:
	unsigned int _httpID;

	unsigned int _CreateConnection();
};
#endif