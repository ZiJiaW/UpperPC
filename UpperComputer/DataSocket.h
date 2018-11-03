#pragma once

// DataSocket 命令目标

class DataSocket : public CSocket
{
public:
	DataSocket();
	virtual ~DataSocket();
	virtual void OnReceive(int nErrorCode);
	virtual BOOL OpenFile(CString filePath);
    void FileRevFailed();


protected:
	
	CFile f_LoadFile;//要保存的文件变量


};


