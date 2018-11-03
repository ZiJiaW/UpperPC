// PubSub.cpp: implementation of the CPubSub class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PubSub.h"
#include "UpperComputer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPubSub::CPubSub()
{
	m_hCom = INVALID_HANDLE_VALUE;
}

CPubSub::~CPubSub()
{

}

//===========================================================
// ���ܣ�����Դ
// ������ComNo�����ںţ�Baut�������ʣ�Data������λ��Stop��ֹͣλ
//       Parity��У��λ��cbInBuf��������д�С��cbOutBuf��������д�С
//    BYTE ByteSize;        /* Number of bits/byte, 4-8        */
//    BYTE Parity;          /* 0-4=None,Odd,Even,Mark,Space    */
//    BYTE StopBits;        /* 0,1,2 = 1, 1.5, 2               */
//===========================================================
BOOL CPubSub::OpenCom(CString str_ComPort,DWORD Baut,int Data,int Stop,int Parity,DWORD cbInBuf,DWORD cbOutBuf)
{
	if(INVALID_HANDLE_VALUE!=m_hCom)
		CloseCom();

	DCB Dcb;
	COMMTIMEOUTS TimeOut;

	if(INVALID_HANDLE_VALUE!=m_hCom)
	{
		CloseHandle(m_hCom);
	}

	Baut=(Baut<50)? 50:Baut;
	Data=((Data>=4)&&(Data<=8))?(BYTE)Data:8;
	Stop=Stop>3 ? (BYTE)0:Stop;
	Parity=Parity>4 ? (BYTE)0:Parity;

	// ���ӡ�\\\\.\\�����Դ�COM10���ϵĴ��ں�
	str_ComPort = _T("\\\\.\\COM") + str_ComPort;
	//// ��Ҫ��Ϊchar���ͣ�ʹ��cstringʱ��ֹͣλΪ1.5ʱ��ʧ��
	char *char_ComPort = str_ComPort.GetBuffer(str_ComPort.GetLength());
	str_ComPort.ReleaseBuffer();
	
	m_hCom=CreateFile(char_ComPort,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,NULL,NULL);
	if(m_hCom==INVALID_HANDLE_VALUE)
		return FALSE;

	GetCommState(m_hCom,&Dcb);
	Dcb.BaudRate=Baut;
	Dcb.ByteSize=Data;
	Dcb.StopBits=Stop;
	Dcb.Parity=Parity;
	if(!SetCommState(m_hCom,&Dcb))
	{
		CloseHandle(m_hCom);
		m_hCom=INVALID_HANDLE_VALUE;
		return FALSE;
	}
	memset(&TimeOut, 0, sizeof(TimeOut));
	TimeOut.ReadIntervalTimeout = MAXDWORD;
	SetCommTimeouts(m_hCom, &TimeOut);//��ʾ��������

	SetupComm(m_hCom,cbInBuf,cbOutBuf);

	return TRUE;

}

//================================================
// ���ܣ���ȡ���пڻ��������ֽ���
//================================================
int CPubSub::GetDataLen()
{
	if(m_hCom==INVALID_HANDLE_VALUE)
		return 0;

	COMSTAT comstat;
	DWORD dwError;
	if(ClearCommError(m_hCom,&dwError,&comstat))
		return comstat.cbInQue;
	dwError=GetLastError();
	return 0;
}

//===================================================
// ���ܣ������п�
//===================================================
DWORD CPubSub::ReadCom(BYTE *pBuff,int nCount)
{
	if(m_hCom==INVALID_HANDLE_VALUE)
		return 0;
	DWORD read=0;
	ReadFile(m_hCom , pBuff , nCount , &read , NULL);
	return read;
}

//==================================================
// ���ܣ�д���п�
// ������pBuff:���ݻ�����,nCount:Ҫд�����ݵ��ֽ���
//==================================================
BOOL CPubSub::WriteCom(BYTE *pBuff, int nCount)
{
	if(m_hCom==INVALID_HANDLE_VALUE)
		return FALSE;
	DWORD written=0;
	BOOL ret=WriteFile(m_hCom,pBuff,nCount,&written,NULL);
	return ret;
}

//==============================================
// ���ܣ��رմ��п�
//==============================================
BOOL CPubSub::CloseCom()
{
	if(m_hCom!=INVALID_HANDLE_VALUE)
	{
		if(CloseHandle(m_hCom))
        {
			m_hCom=INVALID_HANDLE_VALUE;
        }
	}
	return (m_hCom==INVALID_HANDLE_VALUE);
}

//==============================================
// ���ܣ�������ڻ�����
//==============================================
void CPubSub::ClrComBuf()
{
    PurgeComm( m_hCom, PURGE_TXABORT );  // ��ֹ���ڽ��еķ��Ͳ���
    PurgeComm( m_hCom, PURGE_RXABORT );  // ��ֹ���ڽ��еĽ��ղ���
    PurgeComm( m_hCom, PURGE_TXCLEAR );  // ������ͻ�����
    PurgeComm( m_hCom, PURGE_RXCLEAR );  // ������ջ�����

}

