// ReceiveServer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UpperComputer.h"
#include "ReceiveServer.h"
#include "UpperComputerDlg.h"


// ReceiveServer

ReceiveServer::ReceiveServer()
{
}

ReceiveServer::~ReceiveServer()
{
}


// ReceiveServer ��Ա����


void ReceiveServer::OnAccept(int nErrorCode)
{
	// 
	pSocket = new DataSocket();
	Accept(*pSocket); 

    if (!PathFileExists(_T("program")))
    {
	    CreateDirectory(_T("program"),NULL);
    }
    if (PathFileExists(_T("program\\bitfile.bit")))
    {
        CFile::Remove(_T("program\\bitfile.bit"));
    }
	pSocket->OpenFile(_T("program\\bitfile.bit"));
	CSocket::OnAccept(nErrorCode);
}
