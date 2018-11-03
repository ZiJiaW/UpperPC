// PubSub.h: interface for the CPubSub class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PUBSUB_H__D4912420_5469_11D7_9960_00C0DF246602__INCLUDED_)
#define AFX_PUBSUB_H__D4912420_5469_11D7_9960_00C0DF246602__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "winbase.h"


class CPubSub
{
public:
	CPubSub();
	virtual ~CPubSub();

	HANDLE m_hCom;

	BOOL OpenCom(CString str_ComPort,DWORD Baut,int Data,int Stop,int Parity,DWORD cbInBuf,DWORD cbOutBuf);
	int GetDataLen();
	DWORD ReadCom(BYTE *pBuff,int nCount);
	BOOL WriteCom(BYTE *pBuff, int nCount);
	BOOL CloseCom();
    void ClrComBuf();

};





#endif // !defined(AFX_PUBSUB_H__D4912420_5469_11D7_9960_00C0DF246602__INCLUDED_)
