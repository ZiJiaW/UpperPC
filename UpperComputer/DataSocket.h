#pragma once

// DataSocket ����Ŀ��

class DataSocket : public CSocket
{
public:
	DataSocket();
	virtual ~DataSocket();
	virtual void OnReceive(int nErrorCode);
	virtual BOOL OpenFile(CString filePath);
    void FileRevFailed();


protected:
	
	CFile f_LoadFile;//Ҫ������ļ�����


};


