// DataSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UpperComputer.h"
#include "DataSocket.h"
#include "UpperComputerDlg.h"
#include "resource.h"
#include "define.h"

// DataSocket
int int_FileRevSize = 0; //ÿ���յ��Ĵ�С
char char_FileRevBuffer[2048] = {0};//���ջ���
DWORD dword_FileRevSumLength = 0;  //�ܹ����մ�С

DataSocket::DataSocket()
{
}

DataSocket::~DataSocket()
{
}


// DataSocket ��Ա����

//FPGA��¼�߳�
UINT _FpgaProgramThread(LPVOID lparam)
{  	
    int int_FpgaProgramStatus = 0;

    // ɾ��impact���log�ļ�
    if (PathFileExists(_T("_impactbatch.log")))
    {
        CFile::Remove(_T("_impactbatch.log"));    
    }

    // ����impact��batchģʽ����ִ����¼ָ��
	system("impact -batch program\\runimpact.bat");

    // �ȴ�impact�����־���
    Sleep(10000);

    // ������¼�ɹ���־
    if (PathFileExists(_T("_impactbatch.log")))
    {
        int_FpgaProgramStatus = ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->SearchInFile(_T("_impactbatch.log"), _T("Programmed successfully"));

    }

    if ( int_FpgaProgramStatus )
    {
		// ������¼�ɹ�ָ��:<Loaded><Result>��</Result></Loaded>
		((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->SendCmd(_T("<Loaded><Result>Successful</Result></Loaded>")); 

		// ��־��"FPGA���سɹ���"
        ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->WriteLogFile(1,_T("FPGA���سɹ���"));
        
	    // �������ݲɼ���ʱ��
	    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SetTimer( TIMERID_DATA_SAMPLE, TIMERID_DATA_SAMPLE_TIME, NULL );

    
    }
    else
    {
        // ������¼ʧ��ָ��:<Loaded><Result>��</Result></Loaded>
		((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->SendCmd(_T("<Loaded><Result>Failed</Result></Loaded>")); 

        // ������λ��״̬
        ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->str_WorkStatus = _T("Free");

        // ��־��"FPGA����ʧ�ܡ�"
        ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->WriteLogFile(1,_T("FPGA����ʧ�ܡ�"));
    
    }
 
    return 1;

}


void DataSocket::OnReceive(int nErrorCode)
{
	// TODO: �����ļ�
	int int_RevFileHashCode = 0;

    // �ر��ļ����ճ�ʱ��ʱ��
	((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->KillTimer(TIMERID_FILEREV);

	int_FileRevSize = Receive(char_FileRevBuffer, 2048); 

	if (this->f_LoadFile==NULL)
	{
		// ��־��"�ļ���������!"
		// ���ļ�����xxxx��

		return;
	}

	this->f_LoadFile.Write(char_FileRevBuffer,int_FileRevSize);
	dword_FileRevSumLength+=int_FileRevSize;

	if (dword_FileRevSumLength == ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_FileLength)
	{
        // �ر����Socket
		Close();
		((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->m_FileRevSocket->Close();

		// ���ͽ���ȷ��ָ��:<Receive><Result>��</Result></Receive>
		((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->SendCmd(_T("<Receive><Result>Successful</Result></Receive>")); 

		dword_FileRevSumLength = 0;//��ԭ
		this->f_LoadFile.Close();//�ر��ļ�

		// ��־��"�ļ����ճɹ���"
        ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->WriteLogFile(1,_T("�ļ����ճɹ���"));

        AfxBeginThread(_FpgaProgramThread,this);
        


	}
    else
    {
        // �����ļ����ճ�ʱ��ʱ��
	    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SetTimer( TIMERID_FILEREV, TIMERID_FILEREV_TIME, NULL );

    
    }

	CSocket::OnReceive(nErrorCode);
}


BOOL DataSocket::OpenFile( CString filePath )
{
	if (!this->f_LoadFile.Open(filePath,CFile::modeCreate|CFile::modeReadWrite))
	{
		// ��־�����ļ�����ʧ�ܣ���
        ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->WriteLogFile(1,_T("�ļ�����ʧ�ܡ�"));

		return -1;
	}
	return 1;
}

void DataSocket::FileRevFailed()
{

	dword_FileRevSumLength = 0;//��ԭ
    if (this->f_LoadFile != NULL)
    {
	    this->f_LoadFile.Close();//�ر��ļ�
    }
}
