#pragma once




// StatusSocket 命令目标

class StatusSocket : public CSocket
{
public:
	StatusSocket();
	virtual ~StatusSocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	int ServerCmdParse(CString str_ServerCmdStr);
	CString GetServerCmdParam(CString str_ServerCmdStr, CString str_ServerCmdKeyWordStr);

	void Init();
	CArchive* m_pArchiveOut;
	CArchive* m_pArchiveIn;
	CSocketFile* m_pFile;
	virtual void OnClose(int nErrorCode); 

    // 加载文件接收
    bool bool_ServerFileRevEn;
	char char_ServerFileRevBuf[64*1024];
    DWORD dword_FileRevSumLength;
    CFile f_LoadFile;



};


