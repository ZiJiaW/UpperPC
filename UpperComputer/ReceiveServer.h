#include "DataSocket.h"


#pragma once

// ReceiveServer ����Ŀ��

class ReceiveServer : public CSocket
{
public:
	ReceiveServer();
	virtual ~ReceiveServer();
	virtual void OnAccept(int nErrorCode);
    DataSocket* pSocket;
};


