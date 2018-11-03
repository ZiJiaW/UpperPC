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
// 功能：打开资源
// 参数：ComNo：串口号，Baut：波特率，Data：数据位，Stop：停止位
//       Parity：校验位，cbInBuf：输入队列大小，cbOutBuf：输出队列大小
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

	// 增加“\\\\.\\”，以打开COM10以上的串口号
	str_ComPort = _T("\\\\.\\COM") + str_ComPort;
	//// 需要改为char类型，使用cstring时，停止位为1.5时打开失败
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
	SetCommTimeouts(m_hCom, &TimeOut);//表示立即返回

	SetupComm(m_hCom,cbInBuf,cbOutBuf);

	return TRUE;

}

//================================================
// 功能：获取串行口缓冲区的字节数
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
// 功能：读串行口
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
// 功能：写串行口
// 参数：pBuff:数据缓冲区,nCount:要写入数据的字节数
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
// 功能：关闭串行口
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
// 功能：清楚串口缓冲区
//==============================================
void CPubSub::ClrComBuf()
{
    PurgeComm( m_hCom, PURGE_TXABORT );  // 终止正在进行的发送操作
    PurgeComm( m_hCom, PURGE_RXABORT );  // 终止正在进行的接收操作
    PurgeComm( m_hCom, PURGE_TXCLEAR );  // 清除发送缓冲区
    PurgeComm( m_hCom, PURGE_RXCLEAR );  // 清除接收缓冲区

}

