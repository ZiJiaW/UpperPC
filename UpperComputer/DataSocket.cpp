// DataSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "UpperComputer.h"
#include "DataSocket.h"
#include "UpperComputerDlg.h"
#include "resource.h"
#include "define.h"

// DataSocket
int int_FileRevSize = 0; //每次收到的大小
char char_FileRevBuffer[2048] = {0};//接收缓存
DWORD dword_FileRevSumLength = 0;  //总共接收大小

DataSocket::DataSocket()
{
}

DataSocket::~DataSocket()
{
}


// DataSocket 成员函数

//FPGA烧录线程
UINT _FpgaProgramThread(LPVOID lparam)
{  	
    int int_FpgaProgramStatus = 0;

    // 删除impact软件log文件
    if (PathFileExists(_T("_impactbatch.log")))
    {
        CFile::Remove(_T("_impactbatch.log"));    
    }

    // 启动impact的batch模式，并执行烧录指令
	system("impact -batch program\\runimpact.bat");

    // 等待impact软件日志完成
    Sleep(10000);

    // 查找烧录成功标志
    if (PathFileExists(_T("_impactbatch.log")))
    {
        int_FpgaProgramStatus = ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->SearchInFile(_T("_impactbatch.log"), _T("Programmed successfully"));

    }

    if ( int_FpgaProgramStatus )
    {
		// 发送烧录成功指令:<Loaded><Result>…</Result></Loaded>
		((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->SendCmd(_T("<Loaded><Result>Successful</Result></Loaded>")); 

		// 日志："FPGA加载成功。"
        ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->WriteLogFile(1,_T("FPGA加载成功。"));
        
	    // 启动数据采集定时器
	    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SetTimer( TIMERID_DATA_SAMPLE, TIMERID_DATA_SAMPLE_TIME, NULL );

    
    }
    else
    {
        // 发送烧录失败指令:<Loaded><Result>…</Result></Loaded>
		((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->SendCmd(_T("<Loaded><Result>Failed</Result></Loaded>")); 

        // 更新上位机状态
        ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->str_WorkStatus = _T("Free");

        // 日志："FPGA加载失败。"
        ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->WriteLogFile(1,_T("FPGA加载失败。"));
    
    }
 
    return 1;

}


void DataSocket::OnReceive(int nErrorCode)
{
	// TODO: 接收文件
	int int_RevFileHashCode = 0;

    // 关闭文件接收超时定时器
	((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->KillTimer(TIMERID_FILEREV);

	int_FileRevSize = Receive(char_FileRevBuffer, 2048); 

	if (this->f_LoadFile==NULL)
	{
		// 日志："文件创建错误!"
		// “文件名：xxxx”

		return;
	}

	this->f_LoadFile.Write(char_FileRevBuffer,int_FileRevSize);
	dword_FileRevSumLength+=int_FileRevSize;

	if (dword_FileRevSumLength == ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_FileLength)
	{
        // 关闭相关Socket
		Close();
		((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->m_FileRevSocket->Close();

		// 发送接收确认指令:<Receive><Result>…</Result></Receive>
		((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->SendCmd(_T("<Receive><Result>Successful</Result></Receive>")); 

		dword_FileRevSumLength = 0;//复原
		this->f_LoadFile.Close();//关闭文件

		// 日志："文件接收成功："
        ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->WriteLogFile(1,_T("文件接收成功。"));

        AfxBeginThread(_FpgaProgramThread,this);
        


	}
    else
    {
        // 启动文件接收超时定时器
	    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SetTimer( TIMERID_FILEREV, TIMERID_FILEREV_TIME, NULL );

    
    }

	CSocket::OnReceive(nErrorCode);
}


BOOL DataSocket::OpenFile( CString filePath )
{
	if (!this->f_LoadFile.Open(filePath,CFile::modeCreate|CFile::modeReadWrite))
	{
		// 日志：“文件创建失败：”
        ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->WriteLogFile(1,_T("文件创建失败。"));

		return -1;
	}
	return 1;
}

void DataSocket::FileRevFailed()
{

	dword_FileRevSumLength = 0;//复原
    if (this->f_LoadFile != NULL)
    {
	    this->f_LoadFile.Close();//关闭文件
    }
}
