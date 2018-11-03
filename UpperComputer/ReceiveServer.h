#include "DataSocket.h"


#pragma once

// ReceiveServer ÃüÁîÄ¿±ê

class ReceiveServer : public CSocket
{
public:
	ReceiveServer();
	virtual ~ReceiveServer();
	virtual void OnAccept(int nErrorCode);
    DataSocket* pSocket;
};


