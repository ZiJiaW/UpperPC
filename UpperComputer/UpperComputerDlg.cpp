
// UpperComputerDlg.cpp : 实现文件
//


#include "stdafx.h"
#include "UpperComputer.h"
#include "UpperComputerDlg.h"
#include "afxdialogex.h"
#include "define.h"
#include "Mmsystem.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CUpperComputerDlg 对话框




CUpperComputerDlg::CUpperComputerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUpperComputerDlg::IDD, pParent)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUpperComputerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BUTTON_Connect, Idc_Button_ServerConnect);
    DDX_Control(pDX, IDC_BUTTON_Disconnect, Idc_Button_ServerDisconnect);
    DDX_Control(pDX, IDC_COMBO_ComSel, Idc_Combo_ComSel);
    DDX_Control(pDX, IDC_BUTTON_ComClose, Idc_Button_ComClose);
    DDX_Control(pDX, IDC_BUTTON_ComOpen, Idc_Button_ComOpen);
    DDX_Control(pDX, IDC_EDIT_ServerStatusPort, Idc_Edit_ServerStatusPort);
    DDX_Control(pDX, IDC_IPADDRESS_ServerIPAddr, Idc_IPaddress_ServerIPAddr);
    DDX_Control(pDX, IDC_EDIT_FpgaRegAddr, Idc_Edit_FpgaRegAddr);
    DDX_Control(pDX, IDC_EDIT_FpgaRegData, Idc_Edit_FpgaRegData);
    DDX_Control(pDX, IDC_BUTTON_FpgaRegWrite, Idc_Button_FpgaRegWrite);
    DDX_Control(pDX, IDC_BUTTON_FpgaRegRead, Idc_Button_FpgaRegRead);
    DDX_Control(pDX, IDC_EDIT_LogDisplay, Idc_Edit_LogDisplay);
    DDX_Control(pDX, IDC_CHECK_LogFileDisplayEn, Idc_Check_LogDisplay);
    DDX_Control(pDX, IDC_EDIT_FpgaUpdateFilePath, Idc_Edit_FpgaUpdateFilePath );             
    DDX_Control(pDX, IDC_BUTTON_FPGAUpdateFileSelect, Idc_Button_FPGAUpdateFileSelect);
    DDX_Control(pDX, IDC_BUTTON_FpgaUpdateStart, Idc_Button_FpgaUpdateStart);
    DDX_Control(pDX, IDC_PROGRESS_FpgaUpdateProgress, Idc_Progress_FpgaUpdateProgress);
	DDX_Control(pDX, IDC_RADIO_MasterFpgaSelect, Idc_Radio_MasterFpgaSelect);
	DDX_Control(pDX, IDC_RADIO_ExpFpgaSelect, Idc_Radio_ExpFpgaSelect);
    DDX_Control(pDX, IDC_RADIO_ExpFpgaUartTest, Idc_Radio_ExpFpgaUartTest);
    DDX_Control(pDX, IDC_RADIO_SpiFlashSelect, Idc_Radio_SpiFlashSelect);
	DDX_Control(pDX, IDC_RADIO_SpiFlashStatusSelect, Idc_Radio_SpiFlashStatusSelect);
	DDX_Control(pDX, IDC_RADIO_SpiFlashChipEraseSelect, Idc_Radio_SpiFlashChipEraseSelect);
	DDX_Control(pDX, IDC_RADIO_JtagIRSelect, Idc_Radio_JtagIRSelect);
	DDX_Control(pDX, IDC_RADIO_JtagDRSelect, Idc_Radio_JtagDRSelect);
	DDX_Control(pDX, IDC_RADIO_FPGAUpdateJtagSelect, Idc_Radio_FPGAUpdateJtagSelect);
    DDX_Control(pDX, IDC_CHECK_FPGAUpdateAutoTestEn, Idc_Check_FPGAUpdateAutoTestEn);
	DDX_Control(pDX, IDC_RADIO_FPGAUpdateSpiFlashSelect, Idc_Radio_FPGAUpdateSpiFlashSelect);
	DDX_Control(pDX, IDC_RADIO_FT232HSelect, Idc_Radio_FT232HSelect);
    DDX_Control(pDX, IDC_COMBO_HardwareTestSel, Idc_Combo_HardwareTestSel);
    DDX_Control(pDX, IDC_BUTTON_HardwareTestStart, Idc_Button_HardwareTestStart);
    DDX_Control(pDX, IDC_BUTTON_HardwareTestStop, Idc_Button_HardwareTestStop);
    DDX_Control(pDX, IDC_CHECK_HardwareTestAutoEn, Idc_Check_HardwareTestAutoEn);
	
	
    
    
}

BEGIN_MESSAGE_MAP(CUpperComputerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CUpperComputerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_Connect, &CUpperComputerDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_Disconnect, &CUpperComputerDlg::OnBnClickedButtonDisconnect)

	ON_WM_TIMER()

    ON_BN_CLICKED(IDC_BUTTON_ComOpen, &CUpperComputerDlg::OnBnClickedButtonComopen)
    ON_BN_CLICKED(IDC_BUTTON_ComClose, &CUpperComputerDlg::OnBnClickedButtonComclose)
    ON_BN_CLICKED(IDC_BUTTON_FpgaRegWrite, &CUpperComputerDlg::OnBnClickedButtonFpgaregwrite)
    ON_BN_CLICKED(IDC_BUTTON_FpgaRegRead, &CUpperComputerDlg::OnBnClickedButtonFpgaregread)
    ON_BN_CLICKED(IDC_BUTTON_FPGAUpdateFileSelect, &CUpperComputerDlg::OnBnClickedButtonFpgaupdatefileselect)
    ON_BN_CLICKED(IDC_BUTTON_FpgaUpdateStart, &CUpperComputerDlg::OnBnClickedButtonFpgaupdatestart)
	ON_BN_CLICKED(IDC_BUTTON_HardwareTestStart, &CUpperComputerDlg::OnBnClickedButtonHardwareteststart)
	ON_BN_CLICKED(IDC_BUTTON_HardwareTestStop, &CUpperComputerDlg::OnBnClickedButtonHardwareteststop)
	ON_BN_CLICKED(IDC_BUTTON_FpgaUpdateStop, &CUpperComputerDlg::OnBnClickedButtonFpgaupdatestop)
END_MESSAGE_MAP()


// CUpperComputerDlg 消息处理程序

// 子线程
//VGA视频推送线程
UINT _VgaSendThread(LPVOID lparam)
{  	
	CUpperComputerDlg* pDlg=(CUpperComputerDlg*)lparam;//取得主窗口指针

	// 启动VGA图像推送，推送给服务器
	CString str_System = _T("ffmpeg -f dshow -i video=\"VGA2USB V2U967295\" -pixel_format yuyv422 -an -f flv -y \"rtmp://10.2.26.104:1935/live/") + pDlg->str_UpperComputerID + _T("\"");
	//CString str_System = _T("ffmpeg -f dshow -i video=\"VGA2USB V2U967295\" -pixel_format yuyv422 -an -f flv -y \"rtmp://192.168.1.107:1935/live/") + pDlg->str_UpperComputerID + _T("\"");
	system(str_System);
 
    return 1;

}

BOOL CUpperComputerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
    
    // 限制log显示编辑框的容量，单位：个字符
    Idc_Edit_LogDisplay.SetLimitText(-1);

    // 变量初始化
	str_WorkStatus = _T("Ready");
    str_WorkMode = _T("ExperimentMode");
    str_ServerMsg_DataPort = _T("0");

	// 服务器主机名和端口号初始化
    CStdioFile f_ServerInf;

    if (PathFileExists(_T("ServerInf.txt")))
    {
        // 打开服务器信息文件
	    f_ServerInf.Open(_T("ServerInf.txt"),CFile::modeNoTruncate|CFile::modeRead);
        // 读取IP地址：x.x.x.x
        f_ServerInf.ReadString( str_ServerIPAddress );
        // 读取端口号
        f_ServerInf.ReadString( str_ServerStatusPort );
        // 读取本机ID号
        f_ServerInf.ReadString( str_UpperComputerID );
        // 关闭文件
        f_ServerInf.Close();
        // 显示服务器IP地址和端口号
	    Idc_IPaddress_ServerIPAddr.SetWindowText(str_ServerIPAddress);
	    Idc_Edit_ServerStatusPort.SetWindowText(str_ServerStatusPort);

    }
    else 
    {
		AfxMessageBox(_T("没有发现服务器信息文件！")); 
    }
	// 服务器断开按钮不可用
	Idc_Button_ServerDisconnect.EnableWindow(FALSE);
    

	// 串口号
	for ( unsigned int i = 1; i < 256; i++ )
	{
		CString str_ComPort;
		str_ComPort.Format(_T("%d"),i);
		Idc_Combo_ComSel.AddString(str_ComPort);
	}
	Idc_Combo_ComSel.SetCurSel(0);    
	// 串口关闭按钮不可用
	Idc_Button_ComClose.EnableWindow(FALSE);

    // 实验串口状态
    bool_ExpComStatus = 0;

	// 硬件自检功能选择
	Idc_Combo_HardwareTestSel.AddString(_T("JTAG接口"));
	Idc_Combo_HardwareTestSel.AddString(_T("实验串口"));
	Idc_Combo_HardwareTestSel.AddString(_T("数码管"));
	Idc_Combo_HardwareTestSel.AddString(_T("LED"));
	Idc_Combo_HardwareTestSel.AddString(_T("拨码开关"));
	Idc_Combo_HardwareTestSel.AddString(_T("按键"));
	Idc_Combo_HardwareTestSel.AddString(_T("PS2接口"));
	Idc_Combo_HardwareTestSel.AddString(_T("时钟"));
	//Idc_Combo_HardwareTestSel.AddString(_T("VGA接口"));
	//Idc_Combo_HardwareTestSel.AddString(_T("Flash"));
	//Idc_Combo_HardwareTestSel.AddString(_T("SDRAM"));
	Idc_Combo_HardwareTestSel.SetCurSel(0);    
	// 停止按钮不可用
	Idc_Button_HardwareTestStop.EnableWindow(FALSE);



	// 新建log文件
    if (PathFileExists(_T("uppercomputer.log")))
    {
	    f_LogFile.Open(_T("uppercomputer.log"),CFile::modeNoTruncate|CFile::modeWrite);
        f_LogFile.SeekToEnd();

    }
    else
    {
	    f_LogFile.Open(_T("uppercomputer.log"),CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);
    }

    AutoOpenMasterCom();

	//// 启动VGA图像推送，推送给服务器
	//AfxBeginThread(_VgaSendThread,this);

    Idc_Check_LogDisplay.SetCheck(1);// 默认开启log打印

    // 向服务器发送连接请求
	m_ServerConnectStatus = 0;
	m_ServerRegisterStatus = 0;
	//OnBnClickedButtonConnect();

	// 启动注册定时器
	SetTimer( TIMERID_REGISTER, TIMERID_REGISTER_TIME, NULL );
    // 启动断网检测
    SetTimer(TIMERID_CHECK_CONNECT, TIMERID_CHECK_CONNECT_TIME, NULL);
	//// 打开ft232h
	//OnBnClickedButtonComopen();

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++just for debug

    wsEndpoint = new WebsocketEndpoint();
    WriteLogFile(1, _T("开启WS终端......"));
    /*if (wsEndpoint->connect("ws://127.0.0.1:9002") != -1)
    {
        WriteLogFile(0, _T("connect with localhost 9002 port!"));
    }
    else {
        WriteLogFile(0, _T("connect failed!"));
    }*/
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //OnBnClickedButtonConnect();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CUpperComputerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUpperComputerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CUpperComputerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUpperComputerDlg::OnBnClickedOk()
{
    f_LogFile.Close();
    //delete wsEndpoint;
	CDialogEx::OnOK();
}

void CUpperComputerDlg::OnClose() 
{
    //delete wsEndpoint;// 销毁终端
    CDialog::OnClose();
}


// 子线程
////VGA视频推送线程
//UINT _VgaSendThread(LPVOID lparam)
//{  	
//	// 启动VGA图像推送，推送给服务器
//	//CString str_System = _T("ffmpeg -f dshow -i video=\"VGA2USB V2U967295\" -pixel_format yuyv422 -an -f flv -y \"rtmp://10.2.26.104:1935/live/") + str_UpperComputerID + _T("\" > ffmpeg.log");
//	CString str_System = _T("ffmpeg -f dshow -i video=\"VGA2USB V2U967295\" -pixel_format yuyv422 -an -f flv -y \"rtmp://192.168.1.107:1935/live/") + str_UpperComputerID + _T("\"");
//	system(str_System);
// 
//    return 1;
//
//}

// 实验fpga 串口测试线程
UINT _ExpFpgaUartTestThread(LPVOID lparam)
{
    CString str_FpgaReadData0;
    CString str_FpgaReadData1;
    CString str_FpgaRegData;


    CUpperComputerDlg* pDlg = (CUpperComputerDlg*)lparam;//取得主窗口指针

                                                         // 实验串口控制模块清零
    pDlg->FpgaWrite(0, 0x60, 0x0);
    // 配置实验串口
    pDlg->ExpComOpen(1000000, 8, 0, 0);

    // 获取测试数据
    pDlg->Idc_Edit_FpgaRegData.GetWindowText(str_FpgaRegData);
    str_FpgaRegData = str_FpgaRegData.Right(16);

    for (;;)
    {
        // 实验fpga 串口测试
        if (pDlg->Idc_Radio_ExpFpgaUartTest.GetCheck())
        {
            // 写入测试数据
            pDlg->ExpFpgaWrite(0, 1, _tcstoui64(str_FpgaRegData, 0, 16));

            // 切换地址，先读0地址，再读1地址
            str_FpgaReadData0 = pDlg->ExpFpgaRead(0);
            str_FpgaReadData1 = pDlg->ExpFpgaRead(1);

            pDlg->Idc_Edit_FpgaRegData.SetWindowText(str_FpgaReadData1);
            if (str_FpgaReadData1 != str_FpgaRegData)
            {
                pDlg->WriteLogFile(1, _T("实验fpga 串口测试失败！\r\nstr_FpgaRegData = ") + str_FpgaRegData + _T("str_FpgaReadData0 = ") + str_FpgaReadData0 + _T("str_FpgaReadData1 = ") + str_FpgaReadData1);

            }


        }
        else
        {

            break;

        }
    }

    return 1;

}

// FPGA加载线程
UINT _FpgaUpdateThread(LPVOID lparam)
{  	
	CFile f_FpgaUpdateFile;
	CString str_FpgaUpdateFilePath;
    unsigned int uint_FpgaUpdateFileLength;
	BYTE byte_FpgaUpdateFileReadBuf[64*1024];
    unsigned int uint_FpgaUpdateFileReadLen;

 	BYTE byte_FpgaReadBuf[64*1024];
 	BYTE byte_FpgaWriteBuf[64*1024];
    unsigned __int64 uint64_SpiFlashPageAddr;
    int int_SpiFlashStatusData;
	int i;
	CString str_FpgaReadData;
	int int_JtagTestTotalTimes = 0;
	int int_JtagTestSuccessTimes = 0;
	int int_JtagTestFailedTimes = 0;
	CString str_JtagTestTimesTmp;


	CUpperComputerDlg* pDlg=(CUpperComputerDlg*)lparam;//取得主窗口指针

	pDlg->int_FpgaUpdateStatus = 0;

	// 如果选择spi-flash烧写，则等待擦除完成，10s超时
    if (pDlg->Idc_Radio_FPGAUpdateSpiFlashSelect.GetCheck())
	{
		// 等待擦除完成
		for (i = 0; i < 10; i++)
		{
			// 读取spi-flash状态寄存器
			int_SpiFlashStatusData = _tcstoui64(pDlg->SpiFlashStatusRead(),0,16);

			// 如果busy位为1，则继续等待，每次等1s
			if((int_SpiFlashStatusData & 0x0001) == 0x0001)
			{
				Sleep(1000);
			}
			else
			{
				break;
			}

		}


		// 如果busy位有效，则擦除失败
		if((int_SpiFlashStatusData & 0x0001) == 0x0001)
		{

			// 浏览文件按钮可用
			pDlg->Idc_Button_FPGAUpdateFileSelect.EnableWindow(TRUE);
			// 启动按钮可用
			pDlg->Idc_Button_FpgaUpdateStart.EnableWindow(TRUE);
			pDlg->WriteLogFile(1,_T("FPGA 升级：\r\nSPI-Flash 擦除失败！"));

			return 0;

		}
	}

	//打开要烧写的文件
	if (pDlg->int_FpgaUpdateMode == FPGA_UPDATE_MODE_LOCAL)
	{
		// 选择在线加载文件路径
		pDlg->Idc_Edit_FpgaUpdateFilePath.GetWindowText(str_FpgaUpdateFilePath);
	 
	}
	else if (pDlg->int_FpgaUpdateMode == FPGA_UPDATE_MODE_ONLINE)
	{
		// 设置在线加载文件路径
		str_FpgaUpdateFilePath = _T("program\\bitfile.bit");
	}

	// 打开加载bit文件
	if(!f_FpgaUpdateFile.Open(str_FpgaUpdateFilePath, CFile::modeRead | CFile::typeBinary))
	{
		pDlg->WriteLogFile(1,_T("FPGA 升级：\r\n加载文件打开失败！"));
		return 0;
	}

    // 获取文件长度
    uint_FpgaUpdateFileLength = f_FpgaUpdateFile.GetLength();

    // 设置烧写进度范围
	pDlg->Idc_Progress_FpgaUpdateProgress.SetRange32(0,uint_FpgaUpdateFileLength);
	// 烧写进度归零
	pDlg->Idc_Progress_FpgaUpdateProgress.SetPos(0); 

    // 开始烧写文件
	pDlg->WriteLogFile(1,_T("FPGA 升级：\r\n正在加载文件。。。"));
    uint64_SpiFlashPageAddr = FPGA_UPDATE_START_ADDR;
	int_SpiFlashStatusData = 0;

    if (pDlg->Idc_Radio_FPGAUpdateSpiFlashSelect.GetCheck())
	{
		// 指向文件开头
		f_FpgaUpdateFile.Seek(BIT_START_ADDR_XC6SLX16, CFile::begin);  

		for(;;)
		{    
			// 如果busy位有效，则烧写失败
			if((int_SpiFlashStatusData & 0x0001) == 0x0001)
			{
				//关闭要烧写的文件
				f_FpgaUpdateFile.Close();

				// 浏览文件按钮可用
				pDlg->Idc_Button_FPGAUpdateFileSelect.EnableWindow(TRUE);
				// 启动按钮可用
				pDlg->Idc_Button_FpgaUpdateStart.EnableWindow(TRUE);
				pDlg->WriteLogFile(1,_T("FPGA 升级：\r\nSPI-Flash 烧写失败！"));
			
				return 0;

			}
			// 如果busy位无效，则继续烧写
			else
			{
				//一次读取256字节的文件内容
				uint_FpgaUpdateFileReadLen = f_FpgaUpdateFile.Read(byte_FpgaUpdateFileReadBuf, 256);
				if(uint_FpgaUpdateFileReadLen == 0)
				{
					break;
				}
			

				//烧写文件内容
				pDlg->SpiFlashPageProgram(uint64_SpiFlashPageAddr, byte_FpgaUpdateFileReadBuf, uint_FpgaUpdateFileReadLen);

				// 更新烧写进度条
				uint64_SpiFlashPageAddr += uint_FpgaUpdateFileReadLen;
				pDlg->Idc_Progress_FpgaUpdateProgress.SetPos(uint64_SpiFlashPageAddr - FPGA_UPDATE_START_ADDR); 

			}

			// 等待页面烧写完成
			for (i = 0; i < 3; i++)
			{
				// 读取spi-flash状态寄存器
				int_SpiFlashStatusData = _tcstoui64(pDlg->SpiFlashStatusRead(),0,16);

				// 如果busy位为1，则继续等待，每次等1ms
				if((int_SpiFlashStatusData & 0x0001) == 0x0001)
				{
					Sleep(1);
				}
				else
				{
					break;
				}

			}

		}

		// 烧写进度归零
		pDlg->Idc_Progress_FpgaUpdateProgress.SetPos(0); 
		// 指向文件开头
		f_FpgaUpdateFile.Seek(BIT_START_ADDR_XC6SLX16, CFile::begin);  

		// 开始校验
		pDlg->WriteLogFile(1,_T("FPGA 升级：\r\nSPI-Flash 正在校验。。。"));
		uint64_SpiFlashPageAddr = FPGA_UPDATE_START_ADDR;

		// 拉高spi-flash的片选信号，终止当前操作
		pDlg->FpgaWrite(0,0x40,0x1);
		// 拉低spi-flash的片选信号
		pDlg->FpgaWrite(0,0x40,0x0);
		// 写入 Read Data (03h) 指令
		pDlg->FpgaWrite(0,0x41,0x03);
		// 写入起始地址的[23:16]
		pDlg->FpgaWrite(0,0x41,((uint64_SpiFlashPageAddr >> 16) & 0x00000000000000ff));
		// 写入起始地址的[15:8]
		pDlg->FpgaWrite(0,0x41,((uint64_SpiFlashPageAddr >> 8) & 0x00000000000000ff));
		// 写入起始地址的[7:0]
		pDlg->FpgaWrite(0,0x41,(uint64_SpiFlashPageAddr & 0x00000000000000ff));

		for(;;)
		{    
		 
			//一次读取4k字节的文件内容
			uint_FpgaUpdateFileReadLen = f_FpgaUpdateFile.Read(byte_FpgaUpdateFileReadBuf, 64);
			if(uint_FpgaUpdateFileReadLen == 0)
			{
				pDlg->int_FpgaUpdateStatus = 1;
				pDlg->WriteLogFile(1,_T("SPI-Flash 加载成功！"));
				//关闭要烧写的文件
				f_FpgaUpdateFile.Close();
				break;
			}

			// 清除spi-flash rx buffer
			pDlg->FpgaWrite(0,0x40,0x2);

			for (i = 0; i < uint_FpgaUpdateFileReadLen * 2; i = i + 2)
			{
				byte_FpgaWriteBuf[i] = 0x1;
				byte_FpgaWriteBuf[i+1] = 0x00;
			}
			// 读取spi-flash数据
			pDlg->FpgaBlockWrite(0x41,byte_FpgaWriteBuf,2,uint_FpgaUpdateFileReadLen * 2);

			// 从fpga读取数据
			pDlg->FpgaBlockRead(0x42,byte_FpgaReadBuf,1,uint_FpgaUpdateFileReadLen);
			for (i = 0; i < uint_FpgaUpdateFileReadLen; i++)
			{
				//str_FpgaReadData = pDlg->FpgaRead(0x42);
	
				//if (((BYTE)(_tcstoul(str_FpgaReadData.Mid(14, 2), 0, 16))) != byte_FpgaUpdateFileReadBuf[i])
				if (byte_FpgaReadBuf[i] != byte_FpgaUpdateFileReadBuf[i])
				{
					// 拉高spi-flash的片选信号，终止当前操作
					pDlg->FpgaWrite(0,0x40,0x1);
					//关闭要烧写的文件
					f_FpgaUpdateFile.Close();

					// 浏览文件按钮可用
					pDlg->Idc_Button_FPGAUpdateFileSelect.EnableWindow(TRUE);
					// 启动按钮可用
					pDlg->Idc_Button_FpgaUpdateStart.EnableWindow(TRUE);
					pDlg->WriteLogFile(1,_T("FPGA 升级：\r\nSPI-Flash 校验失败！"));
					return 0;
				}
			}
   


			// 更新烧写进度条
			uint64_SpiFlashPageAddr += uint_FpgaUpdateFileReadLen;
			pDlg->Idc_Progress_FpgaUpdateProgress.SetPos(uint64_SpiFlashPageAddr - FPGA_UPDATE_START_ADDR); 
		}

		// 拉高spi-flash的片选信号
		pDlg->FpgaWrite(0,0x40,0x1);

	}

	// jtag加载模式
    else if (pDlg->Idc_Radio_FPGAUpdateJtagSelect.GetCheck())
	{


		f_FpgaUpdateFile.GetFileTitle();

		do
		{
			// 启动jtag加载超时定时器
			pDlg->SetTimer( TIMERID_JTAG_TIMEOUT, TIMERID_JTAG_TIMEOUT_TIME, NULL );

			pDlg->WriteLogFile(1,_T("FPGA 升级：\r\n开始JTAG加载。。。"));

			// 烧写进度归零
			pDlg->Idc_Progress_FpgaUpdateProgress.SetPos(0); 
			// 指向文件开头
			f_FpgaUpdateFile.Seek(BIT_START_ADDR_XC6SLX100, CFile::begin);  

			// 开始烧写文件
			uint64_SpiFlashPageAddr = FPGA_UPDATE_START_ADDR;
			int_SpiFlashStatusData = 0;


			// jtag 初始化
			pDlg->JtagStateReset();
			pDlg->JtagStateIdle();
		
			//Loading device with 'bypass' instruction.
			pDlg->JtagSIR(6,0x3f);
			// Loading device with a `jprogram` instruction. 
			pDlg->JtagSIR(6,0xb);
			// Loading device with a `cfg_in` instruction. 
			pDlg->JtagSIR(6,0x5);
			Sleep(10);
			pDlg->JtagStateReset();
			// Loading device with a `cfg_in` instruction. 
			pDlg->JtagSIR(6,0x5);
			pDlg->JtagSDR(32,0x0);
			pDlg->JtagSIR(6,0x5);


			// tap状态机从“RUN-TEST/IDLE” 状态进入“SHIFT-DR”状态，TMS输出“001”
			pDlg->FpgaWrite(0, 0x50, 0x3);
			pDlg->FpgaWrite(0, 0x51, 0x0000000100000000);


			// 写入前导数据, msb first
			pDlg->FpgaWrite(0, 0x50, 0x100000020);
			pDlg->FpgaWrite(0, 0x51, 0x30a10008);
			pDlg->FpgaWrite(0, 0x51, 0x0);


			pDlg->FpgaWrite(0, 0x700, 0x1);
			pDlg->FpgaWrite(0, 0x700, 0x2);


			// 写入文件数据
			for(;;)
			{    

				//读取文件内容
				uint_FpgaUpdateFileReadLen = f_FpgaUpdateFile.Read(byte_FpgaUpdateFileReadBuf, JTAG_BLOCK_WRITE_LENGTH);

				if(f_FpgaUpdateFile.GetPosition() == uint_FpgaUpdateFileLength)
				{
					//烧写文件内容
					pDlg->FpgaBlockWrite(0x51, byte_FpgaUpdateFileReadBuf, 4, uint_FpgaUpdateFileReadLen - 4);
					// 最后4-byte中的最后1-bit，tms要输出1
					pDlg->FpgaWrite(0, 0x51, 0x8000000000000000 | ((byte_FpgaUpdateFileReadBuf[uint_FpgaUpdateFileReadLen - 4]) << 24) | ((byte_FpgaUpdateFileReadBuf[uint_FpgaUpdateFileReadLen - 3]) << 16) | ((byte_FpgaUpdateFileReadBuf[uint_FpgaUpdateFileReadLen - 2]) << 8) | (byte_FpgaUpdateFileReadBuf[uint_FpgaUpdateFileReadLen - 1]));

					break;
				}
				else
				{
					//烧写文件内容
					pDlg->FpgaBlockWrite(0x51, byte_FpgaUpdateFileReadBuf, 4, uint_FpgaUpdateFileReadLen);
				
				}


				// 更新烧写进度条
				uint64_SpiFlashPageAddr += uint_FpgaUpdateFileReadLen;
				pDlg->Idc_Progress_FpgaUpdateProgress.SetPos(uint64_SpiFlashPageAddr); 


			}
			pDlg->FpgaWrite(0, 0x700, 0x0);

			// tap状态机进入“RUN-TEST/IDLE”状态，TMS输出“01”
			pDlg->FpgaWrite(0, 0x50, 0x2);
			pDlg->FpgaWrite(0, 0x51, 0x0000000100000000);

			// Loading device with a `jstart` instruction. 
			pDlg->JtagSIR(6,0xc);
			Sleep(1);
			//Loading device with 'bypass' instruction.
			pDlg->JtagSIR(6,0x3f);
			//Loading device with 'bypass' instruction.
			pDlg->JtagSIR(6,0x3f);

			// Loading device with a `jstart` instruction. 
			pDlg->JtagSIR(6,0xc);
			Sleep(1);
			pDlg->JtagSIR(6,0x3f);
			pDlg->JtagSDR(1,0x0);

			Sleep(500);
			// 从主控fpga读取实验fpga加载完成标志位
			str_FpgaReadData = pDlg->FpgaRead(0x10);
			unsigned __int64 uint64_FpgaReadData = _tcstoui64(str_FpgaReadData,0,16);

			// 关闭jtag加载超时定时器
			pDlg->KillTimer(TIMERID_JTAG_TIMEOUT);

			if (pDlg->Idc_Check_FPGAUpdateAutoTestEn.GetCheck())
			{

				// 实验fpga加载成功
				if ((uint64_FpgaReadData & 0x0000000000004000) == 0x0000000000004000)
				{

					pDlg->WriteLogFile(1,_T("JTAG加载成功。。。"));
					int_JtagTestSuccessTimes++;
				}
				else
				{
					pDlg->WriteLogFile(1,_T("JTAG加载失败。。。"));
					int_JtagTestFailedTimes++;
				}

				int_JtagTestTotalTimes++;

				str_JtagTestTimesTmp.Format(_T("%d"),int_JtagTestTotalTimes);
				pDlg->WriteLogFile(0,_T("测试总数：") + str_JtagTestTimesTmp);
				str_JtagTestTimesTmp.Format(_T("%d"),int_JtagTestSuccessTimes);
				pDlg->WriteLogFile(0,_T("成功次数：") + str_JtagTestTimesTmp);
				str_JtagTestTimesTmp.Format(_T("%d"),int_JtagTestFailedTimes);
				pDlg->WriteLogFile(0,_T("失败次数：") + str_JtagTestTimesTmp);
			}
			else
			{
				//关闭文件
				f_FpgaUpdateFile.Close();


 				// 实验fpga加载成功
				if ((uint64_FpgaReadData & 0x0000000000004000) == 0x0000000000004000)
				{
					pDlg->int_FpgaUpdateStatus = 1;
					if (pDlg->int_FpgaUpdateMode == FPGA_UPDATE_MODE_LOCAL)
					{
						pDlg->WriteLogFile(1,_T("FPGA 升级：\r\nFPGA本地加载成功！"));
					}
					else if (pDlg->int_FpgaUpdateMode == FPGA_UPDATE_MODE_ONLINE)
					{
						pDlg->WriteLogFile(1,_T("FPGA 升级：\r\nFPGA在线加载成功！"));

						// 发送烧录成功指令:<Loaded><Result>…</Result></Loaded>
						pDlg->wsEndpoint->send("<Loaded><Result>Successful</Result></Loaded>"); 
        
						// 启动数据采集定时器
						pDlg->SetTimer( TIMERID_DATA_SAMPLE, TIMERID_DATA_SAMPLE_TIME, NULL );
						pDlg->str_FpgaSampleData0 = _T("");
						pDlg->str_FpgaSampleData1 = _T("");



					
					}
				}
				else
				{
					pDlg->int_FpgaUpdateStatus = 2;
					if (pDlg->int_FpgaUpdateMode == FPGA_UPDATE_MODE_LOCAL)
					{
						pDlg->WriteLogFile(1,_T("FPGA 升级：\r\nFPGA本地加载失败！"));
					}
					else if (pDlg->int_FpgaUpdateMode == FPGA_UPDATE_MODE_ONLINE)
					{
						pDlg->WriteLogFile(1,_T("FPGA 升级：\r\nFPGA在线加载失败！"));

						// 更新上位机状态
						pDlg->str_WorkStatus = _T("Ready");

						// 发送烧录失败指令:<Loaded><Result>…</Result></Loaded>
						pDlg->wsEndpoint->send("<Loaded><Result>Failed</Result></Loaded>"); 
					
					}
				}

			}

		}while(pDlg->Idc_Check_FPGAUpdateAutoTestEn.GetCheck());
	}

    // 浏览文件按钮可用
    pDlg->Idc_Button_FPGAUpdateFileSelect.EnableWindow(TRUE);
    // 启动按钮可用
    pDlg->Idc_Button_FpgaUpdateStart.EnableWindow(TRUE);
	
	return 0;
}




// 子函数
// 启动fpga升级线程
void CUpperComputerDlg::FpgaUpdateThreadStart()
{
	AfxBeginThread(_FpgaUpdateThread,this);

}


// jtag 相关
// tap状态机进入“TEST-LOGIC-RESET”状态
void CUpperComputerDlg::JtagStateReset()
{

	// 复位tap状态机，TMS连续输出至少5个“1”，
    FpgaWrite(0, 0x50, 0x100000008);
    FpgaWrite(0, 0x51, 0x000000ff00000000);

}

// tap状态机进入“RUN-TEST/IDLE”状态
void CUpperComputerDlg::JtagStateIdle()
{

	// TMS输出“0”
    FpgaWrite(0, 0x50, 0x100000001);
    FpgaWrite(0, 0x51, 0x0000000000000000);

}

// jtag输入指令
void CUpperComputerDlg::JtagSIR(unsigned __int64 uint64_IRLengthInBit,unsigned __int64 uint64_IR)
{

	// tap状态机从“RUN-TEST/IDLE” 状态进入“SHIFT-IR”状态，TMS输出“0011”
    FpgaWrite(0, 0x50, 0x4);
    FpgaWrite(0, 0x51, 0x0000000300000000);

	unsigned __int64 uint64_TmsAtLastBit = 0x0000000080000000;
	for (int i = 0; i < uint64_IRLengthInBit; i++)
	{
		uint64_TmsAtLastBit = uint64_TmsAtLastBit << 1;
	
	}

	// 写入指令,TMS保持输出“0”
    FpgaWrite(0, 0x50, (0x00000000ffffffff & uint64_IRLengthInBit));
    FpgaWrite(0, 0x51, (uint64_TmsAtLastBit | (0x00000000ffffffff & uint64_IR)));

	// tap状态机进入“RUN-TEST/IDLE”状态，TMS输出“01”
    FpgaWrite(0, 0x50, 0x2);
    FpgaWrite(0, 0x51, 0x0000000100000000);

}

// jtag输入数据，1次最多32-bit
void CUpperComputerDlg::JtagSDR(unsigned __int64 uint64_DRLengthInBit,unsigned __int64 uint64_DR)
{

	// tap状态机从“RUN-TEST/IDLE” 状态进入“SHIFT-DR”状态，TMS输出“001”
    FpgaWrite(0, 0x50, 0x3);
    FpgaWrite(0, 0x51, 0x0000000100000000);

	unsigned __int64 uint64_TmsAtLastBit = 0x0000000080000000;
	for (int i = 0; i < uint64_DRLengthInBit; i++)
	{
		uint64_TmsAtLastBit = uint64_TmsAtLastBit << 1;
	
	}

	// 写入数据,TMS保持输出“0”
    FpgaWrite(0, 0x50, (0x00000000ffffffff & uint64_DRLengthInBit));
    FpgaWrite(0, 0x51, (uint64_TmsAtLastBit | (0x00000000ffffffff & uint64_DR)));

	// tap状态机进入“RUN-TEST/IDLE”状态，TMS输出“01”
    FpgaWrite(0, 0x50, 0x2);
    FpgaWrite(0, 0x51, 0x0000000100000000);

}



// 向服务器发送指令
/*
void CUpperComputerDlg::SendCmd(CString str_SendStr)
{
	int send_status;
    send_status = m_StatusSocket->Send(str_SendStr + CString(_T("\r\n")), str_SendStr.GetLength()+2, 0);

    //if (1 == Idc_Check_LogDisplay.GetCheck())
	//if (send_status != SOCKET_ERROR)
 //   {
	    // 日志：“向服务器发送指令：”
	    WriteLogFile(1,_T("向服务器发送指令："));
	    WriteLogFile(0,str_SendStr);
    //}

}*/

// 自动打开串口，从COM1到COM255扫描并打开，打开后访问fpga寄存器，能访问到表示打开成功。
BOOL CUpperComputerDlg::AutoOpenMasterCom()
{
	CString str_ComPort;

    if(cpubsub_MasterCom.m_hCom == INVALID_HANDLE_VALUE)
    {
        for ( int i = 1; i < 256*5; i++ )
        {
            str_ComPort.Format(_T("%d"),i & 0xff);
            if(cpubsub_MasterCom.OpenCom(str_ComPort,COM_PORT_BAUDRATE,COM_PORT_DATABIT,COM_PORT_STOPBIT,COM_PORT_PARITYBIT,COMBUFSIZE,COMBUFSIZE))
            {
				CString str_FpgaRead = FpgaRead(0x0);
				
				if (str_FpgaRead.Mid(10, 5) == _T("f6281"))
				{
					Idc_Button_ComOpen.EnableWindow(FALSE);
					Idc_Button_ComClose.EnableWindow(TRUE);
					Idc_Combo_ComSel.EnableWindow(FALSE);
					Idc_Combo_ComSel.SetCurSel((i-1) & 0xff);
					// 日志：“主控串口打开成功：”
					// “串口号：COMX”
                    WriteLogFile(1, _T("主控串口打开成功：\r\n串口号：") + str_ComPort);
					return 1;
				}
				else
				{
					cpubsub_MasterCom.CloseCom();
				}
            }
        }
    }

    if(cpubsub_MasterCom.m_hCom==INVALID_HANDLE_VALUE)
    {
	    Idc_Button_ComOpen.EnableWindow(TRUE);
	    Idc_Button_ComClose.EnableWindow(FALSE);
		// 日志：“串口打开失败。”
        WriteLogFile(1,_T("主控串口打开失败。"));
		return 0;
    }

	return 1;

}

// 获取当前时间
CString CUpperComputerDlg::GetTime()
{
    CString str_CurrentTime;
    CString str_CurrentTimeMS;

    // 获取日期、时、分、秒
    CTime time_CurrentTime = CTime::GetCurrentTime();
    str_CurrentTime = time_CurrentTime.Format(_T("%Y-%m-%d %H:%M:%S"));

    // 获取ms时间
    str_CurrentTimeMS.Format(_T("( %d ms ）"), timeGetTime());
    return (_T("\r\n") + str_CurrentTime + str_CurrentTimeMS + _T("\r\n"));

}



// 打印日志文件
void CUpperComputerDlg::LogDisplay(int int_NewLog, CString str_Log)
{
    // 新日志内容，要标注时间
    if (int_NewLog)
    {
        // 获取当前时间
        CString str_CurrentTime = GetTime();


        //更新编辑框内容
        CString strInfo;
        Idc_Edit_LogDisplay.GetWindowText(strInfo);
        int nLength = strInfo.GetLength();
        Idc_Edit_LogDisplay.SetSel(nLength, nLength, 1);
        Idc_Edit_LogDisplay.ReplaceSel(str_CurrentTime);


    }

    //更新编辑框内容
    CString strInfo;
    Idc_Edit_LogDisplay.GetWindowText(strInfo);
    int nLength = strInfo.GetLength();
    Idc_Edit_LogDisplay.SetSel(nLength, nLength, 1);
    Idc_Edit_LogDisplay.ReplaceSel(str_Log);


}

// 写日志文件
void CUpperComputerDlg::WriteLogFile(int int_NewLog, CString str_Log)
{
    // 新日志内容，要标注时间
    if (int_NewLog)
    {
        // 获取当前时间
        CString str_CurrentTime = GetTime();

        f_LogFile.Write(str_CurrentTime, str_CurrentTime.GetLength());

    }
    // 日志内容写入日志文件
    str_Log += _T("\r\n");
    f_LogFile.Write(str_Log, str_Log.GetLength());

    if (1 == Idc_Check_LogDisplay.GetCheck())
    {
        //更新编辑框内容
        LogDisplay(int_NewLog, str_Log);
    }


}


// 打开并设置实验fpga串口参数
// 波特率：ExpComBautrate;       /* 1bps 到10Mbps */
// 数据位：ExpComDataBits;       /* Number of bits/byte, 4-8        */
// 校验位：ExpComParityBit;      /* 0-4=None,Odd,Even,Mark,Space    */
// 停止位：ExpComStopBit;        /* 0,1,2 = 1, 1.5, 2               */
BOOL CUpperComputerDlg::ExpComOpen(int int_ExpComBautrate, BYTE byte_ExpComDataBits, BYTE byte_ExpComParityBit, BYTE byte_ExpComStopBit)
{
	unsigned __int64 uint64_ExpComParam;
	unsigned __int64 uint64_ExpComClkDivider;

	if (int_ExpComBautrate <= 0)
	{
		// 日志
        WriteLogFile(1,_T("实验串口波特率小于等于0！"));

		return 0;
	}
	uint64_ExpComClkDivider = EXPCOM_CLK_FREQ / int_ExpComBautrate;
	uint64_ExpComParam = ((uint64_ExpComClkDivider << 16) | 0x1000 | (byte_ExpComDataBits << 8) | (byte_ExpComParityBit << 4) | byte_ExpComStopBit);

	// 写入主控fpga
	FpgaWrite(0,0x60,uint64_ExpComParam);

	// 回读校验
	CString str_FpgaReadData = FpgaRead(0x60);

	if (_tcstoui64(str_FpgaReadData,0,16) == uint64_ExpComParam)
	{
		return 1;
	}
	else 
	{
		return 0;
	}

}

// 关闭实验fpga串口
BOOL CUpperComputerDlg::ExpComClose()
{


	// 写入主控fpga
	FpgaWrite(0,0x60,0x0);

	// 回读校验
	CString str_FpgaReadData = FpgaRead(0x60);

	if (_tcstoui64(str_FpgaReadData,0,16) == 0x0)
	{
		return 1;
	}
	else 
	{
		return 0;
	}

}

// 读实验串口
unsigned int CUpperComputerDlg::ExpComRead(BYTE *byte_ExpComReadBuffer, unsigned int uint_ExpComReadLength)
{
    unsigned int uint_ExpComReadLengthTmp = 0;
    CString str_FpgaReadData;
    int i;

    //uint_ExpComReadLengthTmp = FpgaBlockRead(0x62, byte_ExpComReadBuffer, 0x1, uint_ExpComReadLength);

    for (i = 0; i < uint_ExpComReadLength; i++)
    {
        str_FpgaReadData = FpgaRead(0x38);
        byte_ExpComReadBuffer[i] = (BYTE)(_tcstoul(str_FpgaReadData.Mid(8, 2), 0, 16));

    }

    return uint_ExpComReadLengthTmp;
}

// 写实验串口
void CUpperComputerDlg::ExpComWrite(BYTE *byte_ExpComWriteBuffer,unsigned int uint_ExpComWriteLength)
{


	FpgaBlockWrite(0x61, byte_ExpComWriteBuffer, 0x1, uint_ExpComWriteLength);
	return;
}



void CUpperComputerDlg::FpgaWrite(unsigned int uint_WriteCmd, unsigned __int64 uint64_WriteAddr, unsigned __int64 uint64_WriteData)
{
	// fpga 寄存器写入
    BYTE byte_FpgaWriteBuf[128];


    cpubsub_MasterCom.ClrComBuf();

    byte_FpgaWriteBuf[0]  = (byte)( 0xf6 );
    byte_FpgaWriteBuf[1]  = (byte)(( uint_WriteCmd << 7 ) + (( uint64_WriteAddr >> 8 ) & 0x7f ));
    byte_FpgaWriteBuf[2]  = (byte)(  uint64_WriteAddr & 0xff );
    byte_FpgaWriteBuf[3]  = (byte)(( uint64_WriteData >> 56 ) & 0xff );
    byte_FpgaWriteBuf[4]  = (byte)(( uint64_WriteData >> 48 ) & 0xff );
    byte_FpgaWriteBuf[5]  = (byte)(( uint64_WriteData >> 40 ) & 0xff );
    byte_FpgaWriteBuf[6]  = (byte)(( uint64_WriteData >> 32 ) & 0xff );
    byte_FpgaWriteBuf[7]  = (byte)(( uint64_WriteData >> 24 ) & 0xff );
    byte_FpgaWriteBuf[8]  = (byte)(( uint64_WriteData >> 16 ) & 0xff );
    byte_FpgaWriteBuf[9]  = (byte)(( uint64_WriteData >> 8  ) & 0xff );
    byte_FpgaWriteBuf[10] = (byte)(( uint64_WriteData ) & 0xff );
    byte_FpgaWriteBuf[11] = 0;

	for ( unsigned int i = 0; i < 11; i++ )
    {
        byte_FpgaWriteBuf[11] = byte_FpgaWriteBuf[11] ^ byte_FpgaWriteBuf[i];
    }

	cpubsub_MasterCom.WriteCom( byte_FpgaWriteBuf,12 );

}

CString CUpperComputerDlg::FpgaRead(unsigned __int64 uint64_ReadAddr)
{
	// fpga 寄存器读取
    BYTE byte_FpgaReadBuf[512];
    BYTE byte_FpgaReadCheck = 0;
    unsigned int uint_FpgaReadLength = 0;
	unsigned int i;
	unsigned int uint_ComReadTimeCount;
	CString str_FpgaReadData = _T("");
	CString str_temp;

	// 写入读指令
	FpgaWrite(1,uint64_ReadAddr,0);
	uint_ComReadTimeCount = 0;

	// 检测缓冲区字节数，接收到12个字节或超时100ms，退出循环等待
	do
	{
		Sleep(1);
	    uint_FpgaReadLength = cpubsub_MasterCom.GetDataLen();
		uint_ComReadTimeCount++;
	
	}while((uint_FpgaReadLength < 12)&&(uint_ComReadTimeCount < 100));

    if ((uint_FpgaReadLength < 12)&&(uint_ComReadTimeCount >= 100))
    {
		// 日志：“FPGA读取失败。”
        WriteLogFile(1,_T("FPGA读取失败！"));
    
    }

	// 读取数据
    cpubsub_MasterCom.ReadCom( byte_FpgaReadBuf, uint_FpgaReadLength );

	// 校验协议头部数据
    if (byte_FpgaReadBuf[0] == 0xF6)
    {
        // 计算校验码
		for ( i = 0; i < 12; i++ )  
        {
            byte_FpgaReadCheck = byte_FpgaReadCheck ^ byte_FpgaReadBuf[i];
        }

		//校验正确后，转换成64位字符串
        if ( byte_FpgaReadCheck == 0x00 )  
        {
            for ( i = 3; i < 11; i++ )
            {
				str_temp.Format(_T("%02x"),byte_FpgaReadBuf[i]);
				str_FpgaReadData += str_temp;
                            
            }

        }
    }

	return str_FpgaReadData;




}

// uint_UnitDataLength ：为单个寄存器中有效数据的字节数
// uint_TotalDataLength ：为数据的字节总数，这个必须是uint_UnitDataLength的整数倍
// (uint_TotalDataLength / uint_UnitDataLength) * 12 <= COMBUFSIZE
void CUpperComputerDlg::FpgaBlockWrite(unsigned int uint_WriteAddr, BYTE *byte_FpgaWriteBuf, unsigned int uint_UnitDataLength, unsigned int uint_TotalDataLength)
{
	BYTE byte_FpgaWriteBufTmp[COMBUFSIZE];
	unsigned int i=0;
	unsigned int j=0;
		

	// 在数据中插入帧头、指令、地址、校验码
	for (i = 0; i < uint_TotalDataLength; i = i + uint_UnitDataLength)
	{
		byte_FpgaWriteBufTmp[j]    = (byte)0xf6;
		byte_FpgaWriteBufTmp[j+1]  = (byte)(( uint_WriteAddr >> 8 ) & 0x7f );
		byte_FpgaWriteBufTmp[j+2]  = (byte)(uint_WriteAddr & 0xff);
		switch (uint_UnitDataLength)
		{
			case 1 :
				{
					byte_FpgaWriteBufTmp[j+3]  = 0x00;
					byte_FpgaWriteBufTmp[j+4]  = 0x00;
					byte_FpgaWriteBufTmp[j+5]  = 0x00;
					byte_FpgaWriteBufTmp[j+6]  = 0x00;
					byte_FpgaWriteBufTmp[j+7]  = 0x00;
					byte_FpgaWriteBufTmp[j+8]  = 0x00;
					byte_FpgaWriteBufTmp[j+9]  = 0x00;
					byte_FpgaWriteBufTmp[j+10] = byte_FpgaWriteBuf[i];
					break;
				}
			case 2 :
				{
					byte_FpgaWriteBufTmp[j+3]  = 0x00;
					byte_FpgaWriteBufTmp[j+4]  = 0x00;
					byte_FpgaWriteBufTmp[j+5]  = 0x00;
					byte_FpgaWriteBufTmp[j+6]  = 0x00;
					byte_FpgaWriteBufTmp[j+7]  = 0x00;
					byte_FpgaWriteBufTmp[j+8]  = 0x00;
					byte_FpgaWriteBufTmp[j+9]  = byte_FpgaWriteBuf[i];
					byte_FpgaWriteBufTmp[j+10] = byte_FpgaWriteBuf[i+1];
					break;
				}
			case 3 :
				{
					byte_FpgaWriteBufTmp[j+3]  = 0x00;
					byte_FpgaWriteBufTmp[j+4]  = 0x00;
					byte_FpgaWriteBufTmp[j+5]  = 0x00;
					byte_FpgaWriteBufTmp[j+6]  = 0x00;
					byte_FpgaWriteBufTmp[j+7]  = 0x00;
					byte_FpgaWriteBufTmp[j+8]  = byte_FpgaWriteBuf[i];
					byte_FpgaWriteBufTmp[j+9]  = byte_FpgaWriteBuf[i+1];
					byte_FpgaWriteBufTmp[j+10] = byte_FpgaWriteBuf[i+2];
					break;
				}
			case 4 :
				{
					byte_FpgaWriteBufTmp[j+3]  = 0x00;
					byte_FpgaWriteBufTmp[j+4]  = 0x00;
					byte_FpgaWriteBufTmp[j+5]  = 0x00;
					byte_FpgaWriteBufTmp[j+6]  = 0x00;
					byte_FpgaWriteBufTmp[j+7]  = byte_FpgaWriteBuf[i];
					byte_FpgaWriteBufTmp[j+8]  = byte_FpgaWriteBuf[i+1];
					byte_FpgaWriteBufTmp[j+9]  = byte_FpgaWriteBuf[i+2];
					byte_FpgaWriteBufTmp[j+10] = byte_FpgaWriteBuf[i+3];
					break;
				}
			case 5 :
				{
					byte_FpgaWriteBufTmp[j+3]  = 0x00;
					byte_FpgaWriteBufTmp[j+4]  = 0x00;
					byte_FpgaWriteBufTmp[j+5]  = 0x00;
					byte_FpgaWriteBufTmp[j+6]  = byte_FpgaWriteBuf[i];
					byte_FpgaWriteBufTmp[j+7]  = byte_FpgaWriteBuf[i+1];
					byte_FpgaWriteBufTmp[j+8]  = byte_FpgaWriteBuf[i+2];
					byte_FpgaWriteBufTmp[j+9]  = byte_FpgaWriteBuf[i+3];
					byte_FpgaWriteBufTmp[j+10] = byte_FpgaWriteBuf[i+4];
					break;
				}
			case 6 :
				{
					byte_FpgaWriteBufTmp[j+3]  = 0x00;
					byte_FpgaWriteBufTmp[j+4]  = 0x00;
					byte_FpgaWriteBufTmp[j+5]  = byte_FpgaWriteBuf[i];
					byte_FpgaWriteBufTmp[j+6]  = byte_FpgaWriteBuf[i+1];
					byte_FpgaWriteBufTmp[j+7]  = byte_FpgaWriteBuf[i+2];
					byte_FpgaWriteBufTmp[j+8]  = byte_FpgaWriteBuf[i+3];
					byte_FpgaWriteBufTmp[j+9]  = byte_FpgaWriteBuf[i+4];
					byte_FpgaWriteBufTmp[j+10] = byte_FpgaWriteBuf[i+5];
					break;
				}
			case 7 :
				{
					byte_FpgaWriteBufTmp[j+3]  = 0x00;
					byte_FpgaWriteBufTmp[j+4]  = byte_FpgaWriteBuf[i];
					byte_FpgaWriteBufTmp[j+5]  = byte_FpgaWriteBuf[i+1];
					byte_FpgaWriteBufTmp[j+6]  = byte_FpgaWriteBuf[i+2];
					byte_FpgaWriteBufTmp[j+7]  = byte_FpgaWriteBuf[i+3];
					byte_FpgaWriteBufTmp[j+8]  = byte_FpgaWriteBuf[i+4];
					byte_FpgaWriteBufTmp[j+9]  = byte_FpgaWriteBuf[i+5];
					byte_FpgaWriteBufTmp[j+10] = byte_FpgaWriteBuf[i+6];
					break;
				}
			case 8 :
				{
					byte_FpgaWriteBufTmp[j+3]  = byte_FpgaWriteBuf[i];
					byte_FpgaWriteBufTmp[j+4]  = byte_FpgaWriteBuf[i+1];
					byte_FpgaWriteBufTmp[j+5]  = byte_FpgaWriteBuf[i+2];
					byte_FpgaWriteBufTmp[j+6]  = byte_FpgaWriteBuf[i+3];
					byte_FpgaWriteBufTmp[j+7]  = byte_FpgaWriteBuf[i+4];
					byte_FpgaWriteBufTmp[j+8]  = byte_FpgaWriteBuf[i+5];
					byte_FpgaWriteBufTmp[j+9]  = byte_FpgaWriteBuf[i+6];
					byte_FpgaWriteBufTmp[j+10] = byte_FpgaWriteBuf[i+7];
					break;
				}
			default :
				{
					byte_FpgaWriteBufTmp[j+3]  = 0x00;
					byte_FpgaWriteBufTmp[j+4]  = 0x00;
					byte_FpgaWriteBufTmp[j+5]  = 0x00;
					byte_FpgaWriteBufTmp[j+6]  = 0x00;
					byte_FpgaWriteBufTmp[j+7]  = 0x00;
					byte_FpgaWriteBufTmp[j+8]  = 0x00;
					byte_FpgaWriteBufTmp[j+9]  = 0x00;
					byte_FpgaWriteBufTmp[j+10] = 0x00;
					break;
				}
		
		}
		byte_FpgaWriteBufTmp[j+11] = 0xf6;

		for ( unsigned int k = 1; k < 11; k++ )
		{
			byte_FpgaWriteBufTmp[j+11] = byte_FpgaWriteBufTmp[j+11] ^ byte_FpgaWriteBufTmp[j+k];
		}

		j = j + 12;

	
	}




    //WriteLogFile(1,_T("before WriteCom"));

	cpubsub_MasterCom.WriteCom( byte_FpgaWriteBufTmp,(uint_TotalDataLength / uint_UnitDataLength) * 12 );
	//WriteLogFile(1,_T("after WriteCom"));

	return;
}

// uint_UnitDataLength ：为单个寄存器中有效数据的字节数
// uint_TotalDataLength ：为数据的字节总数，这个必须是uint_UnitDataLength的整数倍
// (uint_TotalDataLength / uint_UnitDataLength) * 12 <= COMBUFSIZE
unsigned int CUpperComputerDlg::FpgaBlockRead(unsigned int uint_ReadAddr, BYTE *byte_FpgaReadBuf, unsigned int uint_UnitDataLength, unsigned int uint_TotalDataLength)
{
	BYTE byte_FpgaReadBufTmp[COMBUFSIZE];
    BYTE byte_FpgaReadCheck = 0;
    unsigned int uint_ComReadLength = 0;
	unsigned int uint_ComReadTimeCount;
	unsigned int uint_UnitDataCnt = 0;
	CString str_FpgaReadData = _T("");
	CString str_temp;
	unsigned int i=0;
	unsigned int j=0;

	// 写入读指令
	for (i = 0; i < uint_TotalDataLength; i = i + uint_UnitDataLength)
	{
		byte_FpgaReadBufTmp[j]    = (byte)0xf6;
		byte_FpgaReadBufTmp[j+1]  = (byte)(0x80 | (( uint_ReadAddr >> 8 ) & 0x7f ));
		byte_FpgaReadBufTmp[j+2]  = (byte)(uint_ReadAddr & 0xff);
		byte_FpgaReadBufTmp[j+3]  = 0x00;
		byte_FpgaReadBufTmp[j+4]  = 0x00;
		byte_FpgaReadBufTmp[j+5]  = 0x00;
		byte_FpgaReadBufTmp[j+6]  = 0x00;
		byte_FpgaReadBufTmp[j+7]  = 0x00;
		byte_FpgaReadBufTmp[j+8]  = 0x00;
		byte_FpgaReadBufTmp[j+9]  = 0x00;
		byte_FpgaReadBufTmp[j+10] = 0x00;
		byte_FpgaReadBufTmp[j+11] = 0xf6;

		for ( unsigned int k = 1; k < 3; k++ )
		{
			byte_FpgaReadBufTmp[j+11] = byte_FpgaReadBufTmp[j+11] ^ byte_FpgaReadBufTmp[j+k];
		}

		j = j + 12;

	
	}

	uint_TotalDataLength = (uint_TotalDataLength / uint_UnitDataLength) * 12;
	cpubsub_MasterCom.WriteCom(byte_FpgaReadBufTmp, uint_TotalDataLength);



	uint_ComReadTimeCount = 0;

    // 检测缓冲区字节数，接收到总字节数或超时，退出循环等待
	for(;;)
	{
	    uint_ComReadLength = cpubsub_MasterCom.GetDataLen();

		if(uint_ComReadLength >= uint_TotalDataLength)
		{
			break;	
		}
		else if (uint_ComReadTimeCount < 1000)
		{	
			Sleep(1);
			uint_ComReadTimeCount++;
		}
		else
		{
			break;	
			//return 0;
		}
	
	}

	// 读取数据
    cpubsub_MasterCom.ReadCom( byte_FpgaReadBufTmp, uint_ComReadLength );


	// 提取数据
	for (i = 0; i < uint_ComReadLength; i = i + 12)
	{

		// 校验协议头部数据
		if (byte_FpgaReadBufTmp[i] == 0xF6)
		{
			// 计算校验码
			byte_FpgaReadCheck = 0xF6;
			for ( j = 1; j < 12; j++ )  
			{
				byte_FpgaReadCheck = byte_FpgaReadCheck ^ byte_FpgaReadBufTmp[i+j];
			}

			//校验正确后，转换成64位字符串
			if ( byte_FpgaReadCheck == 0x00 )  
			{
				switch (uint_UnitDataLength)
				{
					case 1 :
						{
							byte_FpgaReadBuf[uint_UnitDataCnt] = byte_FpgaReadBufTmp[i+10];
							break;
						}
					case 2 :
						{
							byte_FpgaReadBuf[uint_UnitDataCnt] = byte_FpgaReadBufTmp[i+9];
							byte_FpgaReadBuf[uint_UnitDataCnt+1] = byte_FpgaReadBufTmp[i+10];
							break;
						}
					case 3 :
						{
							byte_FpgaReadBuf[uint_UnitDataCnt] = byte_FpgaReadBufTmp[i+8];
							byte_FpgaReadBuf[uint_UnitDataCnt+1] = byte_FpgaReadBufTmp[i+9];
							byte_FpgaReadBuf[uint_UnitDataCnt+2] = byte_FpgaReadBufTmp[i+10];
							break;
						}
					case 4 :
						{
							byte_FpgaReadBuf[uint_UnitDataCnt] = byte_FpgaReadBufTmp[i+7];
							byte_FpgaReadBuf[uint_UnitDataCnt+1] = byte_FpgaReadBufTmp[i+8];
							byte_FpgaReadBuf[uint_UnitDataCnt+2] = byte_FpgaReadBufTmp[i+9];
							byte_FpgaReadBuf[uint_UnitDataCnt+3] = byte_FpgaReadBufTmp[i+10];
							break;
						}
					case 5 :
						{
							byte_FpgaReadBuf[uint_UnitDataCnt] = byte_FpgaReadBufTmp[i+6];
							byte_FpgaReadBuf[uint_UnitDataCnt+1] = byte_FpgaReadBufTmp[i+7];
							byte_FpgaReadBuf[uint_UnitDataCnt+2] = byte_FpgaReadBufTmp[i+8];
							byte_FpgaReadBuf[uint_UnitDataCnt+3] = byte_FpgaReadBufTmp[i+9];
							byte_FpgaReadBuf[uint_UnitDataCnt+4] = byte_FpgaReadBufTmp[i+10];
							break;
						}
					case 6 :
						{
							byte_FpgaReadBuf[uint_UnitDataCnt] = byte_FpgaReadBufTmp[i+5];
							byte_FpgaReadBuf[uint_UnitDataCnt+1] = byte_FpgaReadBufTmp[i+6];
							byte_FpgaReadBuf[uint_UnitDataCnt+2] = byte_FpgaReadBufTmp[i+7];
							byte_FpgaReadBuf[uint_UnitDataCnt+3] = byte_FpgaReadBufTmp[i+8];
							byte_FpgaReadBuf[uint_UnitDataCnt+4] = byte_FpgaReadBufTmp[i+9];
							byte_FpgaReadBuf[uint_UnitDataCnt+5] = byte_FpgaReadBufTmp[i+10];
							break;
						}
					case 7 :
						{
							byte_FpgaReadBuf[uint_UnitDataCnt] = byte_FpgaReadBufTmp[i+4];
							byte_FpgaReadBuf[uint_UnitDataCnt+1] = byte_FpgaReadBufTmp[i+5];
							byte_FpgaReadBuf[uint_UnitDataCnt+2] = byte_FpgaReadBufTmp[i+6];
							byte_FpgaReadBuf[uint_UnitDataCnt+3] = byte_FpgaReadBufTmp[i+7];
							byte_FpgaReadBuf[uint_UnitDataCnt+4] = byte_FpgaReadBufTmp[i+8];
							byte_FpgaReadBuf[uint_UnitDataCnt+5] = byte_FpgaReadBufTmp[i+9];
							byte_FpgaReadBuf[uint_UnitDataCnt+6] = byte_FpgaReadBufTmp[i+10];
							break;
						}
					case 8 :
						{
							byte_FpgaReadBuf[uint_UnitDataCnt] = byte_FpgaReadBufTmp[i+3];
							byte_FpgaReadBuf[uint_UnitDataCnt+1] = byte_FpgaReadBufTmp[i+4];
							byte_FpgaReadBuf[uint_UnitDataCnt+2] = byte_FpgaReadBufTmp[i+5];
							byte_FpgaReadBuf[uint_UnitDataCnt+3] = byte_FpgaReadBufTmp[i+6];
							byte_FpgaReadBuf[uint_UnitDataCnt+4] = byte_FpgaReadBufTmp[i+7];
							byte_FpgaReadBuf[uint_UnitDataCnt+5] = byte_FpgaReadBufTmp[i+8];
							byte_FpgaReadBuf[uint_UnitDataCnt+6] = byte_FpgaReadBufTmp[i+9];
							byte_FpgaReadBuf[uint_UnitDataCnt+7] = byte_FpgaReadBufTmp[i+10];
							break;
						}
					default :
						{
							byte_FpgaReadBuf[uint_UnitDataCnt] = 0x00;
							byte_FpgaReadBuf[uint_UnitDataCnt+1] = 0x00;
							byte_FpgaReadBuf[uint_UnitDataCnt+2] = 0x00;
							byte_FpgaReadBuf[uint_UnitDataCnt+3] = 0x00;
							byte_FpgaReadBuf[uint_UnitDataCnt+4] = 0x00;
							byte_FpgaReadBuf[uint_UnitDataCnt+5] = 0x00;
							byte_FpgaReadBuf[uint_UnitDataCnt+6] = 0x00;
							byte_FpgaReadBuf[uint_UnitDataCnt+7] = 0x00;
							break;
						}
		
				}

				uint_UnitDataCnt = uint_UnitDataCnt + uint_UnitDataLength;

			}
			else
			{
				break;
			}

		}
	}

	return  uint_UnitDataCnt * uint_UnitDataLength;
}


void CUpperComputerDlg::ExpFpgaWrite(unsigned int uint_WriteCmd, unsigned __int64 uint64_WriteAddr, unsigned __int64 uint64_WriteData)
{
	// fpga 寄存器写入
    BYTE byte_FpgaWriteBuf[128];



    byte_FpgaWriteBuf[0]  = (byte)( 0xf6 );
    byte_FpgaWriteBuf[1]  = (byte)(( uint_WriteCmd << 7 ) + (( uint64_WriteAddr >> 8 ) & 0x7f ));
    byte_FpgaWriteBuf[2]  = (byte)(  uint64_WriteAddr & 0xff );
    byte_FpgaWriteBuf[3]  = (byte)(( uint64_WriteData >> 56 ) & 0xff );
    byte_FpgaWriteBuf[4]  = (byte)(( uint64_WriteData >> 48 ) & 0xff );
    byte_FpgaWriteBuf[5]  = (byte)(( uint64_WriteData >> 40 ) & 0xff );
    byte_FpgaWriteBuf[6]  = (byte)(( uint64_WriteData >> 32 ) & 0xff );
    byte_FpgaWriteBuf[7]  = (byte)(( uint64_WriteData >> 24 ) & 0xff );
    byte_FpgaWriteBuf[8]  = (byte)(( uint64_WriteData >> 16 ) & 0xff );
    byte_FpgaWriteBuf[9]  = (byte)(( uint64_WriteData >> 8  ) & 0xff );
    byte_FpgaWriteBuf[10] = (byte)(( uint64_WriteData ) & 0xff );
    byte_FpgaWriteBuf[11] = (byte)( 0xf6 );

	for ( unsigned int i = 1; i < 11; i++ )
    {
        byte_FpgaWriteBuf[11] = byte_FpgaWriteBuf[11] ^ byte_FpgaWriteBuf[i];
    }

	ExpComWrite( byte_FpgaWriteBuf,12 );

}


CString CUpperComputerDlg::ExpFpgaRead(unsigned __int64 uint64_ReadAddr)
{
    // fpga 寄存器读取
    BYTE byte_FpgaReadBuf[128];
    BYTE byte_FpgaReadCheck = 0xF6;
    unsigned int uint_FpgaReadLength = 0;
    unsigned int i;
    unsigned int uint_ComReadTimeCount;
    CString str_FpgaReadData = _T("");
    CString str_temp;

    // 写入读指令
    ExpFpgaWrite(1, uint64_ReadAddr, 0);
    uint_ComReadTimeCount = 0;

    // 检测缓冲区字节数，接收到12个字节或超时100ms，退出循环等待
    for (;;)
    {
        str_FpgaReadData = FpgaRead(0x62);
        // 截取实验串口接收到的数据个数（byte）
        uint_FpgaReadLength = _tcstoul(str_FpgaReadData.Mid(8, 4), 0, 16);
        uint_ComReadTimeCount++;

        if (uint_FpgaReadLength >= 12)
        {
            break;
        }
        else if (uint_ComReadTimeCount < 100)
        {
            Sleep(1);
        }
        else
        {
            // 日志
            WriteLogFile(1, _T("实验FPGA读取失败！"));

            return _T("");
        }

    }

    // 读取数据
    ExpComRead(byte_FpgaReadBuf, uint_FpgaReadLength);

    str_FpgaReadData = _T("");
    // 校验协议头部数据
    if (byte_FpgaReadBuf[0] == 0xF6)
    {
        // 计算校验码
        for (i = 1; i < 12; i++)
        {
            byte_FpgaReadCheck = byte_FpgaReadCheck ^ byte_FpgaReadBuf[i];
        }

        //校验正确后，转换成64位字符串
        if (byte_FpgaReadCheck == 0x00)
        {
            for (i = 3; i < 11; i++)
            {
                str_temp.Format(_T("%02x"), byte_FpgaReadBuf[i]);
                str_FpgaReadData += str_temp;

            }

        }
        else
        {
            // 日志
            WriteLogFile(1, _T("实验FPGA读取失败！"));

        }
    }

    return str_FpgaReadData;




}

// spi flash 整片擦除
void CUpperComputerDlg::SpiFlashChipErase( )
{


    // 拉高spi-flash的片选信号，终止当前操作
	FpgaWrite(0,0x40,0x1);
    // 拉低spi-flash的片选信号
	FpgaWrite(0,0x40,0x0);
    // 写入 Write Enable (06h)  指令
	FpgaWrite(0,0x41,0x06);
    // 拉高spi-flash的片选信号，执行指令
	FpgaWrite(0,0x40,0x1);

    // 拉低spi-flash的片选信号
	FpgaWrite(0,0x40,0x0);
    // 写入 Chip Erase (C7h / 60h)  指令
	FpgaWrite(0,0x41,0xc7);
    // 拉高spi-flash的片选信号，执行指令
	FpgaWrite(0,0x40,0x1);


}

// 读取spi-flash status 寄存器
CString CUpperComputerDlg::SpiFlashStatusRead() 
{
    CString str_FpgaReadData;
    CString str_SpiFlashStatusData;


    // 共2个byte Status 寄存器

 	// 清除spi-flash rx buffer
	FpgaWrite(0,0x40,0x3);
   // 拉高spi-flash的片选信号，终止当前操作
	FpgaWrite(0,0x40,0x1);
    // 拉低spi-flash的片选信号
	FpgaWrite(0,0x40,0x0);
    // 写入 Read Status Register-1 (05h)  指令
	FpgaWrite(0,0x41,0x05);
    // 从spi-flash读取数据
	FpgaWrite(0,0x41,0x100);
    // 拉高spi-flash的片选信号，终止当前操作
	FpgaWrite(0,0x40,0x1);
    // 从fpga读取数据
	str_FpgaReadData = FpgaRead(0x42);
    // 截取Status 寄存器数据
    str_SpiFlashStatusData = str_FpgaReadData.Mid(14, 2);

 	// 清除spi-flash rx buffer
	FpgaWrite(0,0x40,0x3);
    // 拉低spi-flash的片选信号
	FpgaWrite(0,0x40,0x0);
    // 写入 Read Status Register-2 (35h)  指令
	FpgaWrite(0,0x41,0x35);
    // 从spi-flash读取数据
	FpgaWrite(0,0x41,0x100);
    // 拉高spi-flash的片选信号，结束读取操作
	FpgaWrite(0,0x40,0x1);
    // 从fpga读取数据
	str_FpgaReadData = FpgaRead(0x42);
    // 截取Status 寄存器数据
    str_SpiFlashStatusData =  str_FpgaReadData.Mid(14, 2) + str_SpiFlashStatusData;


	return str_SpiFlashStatusData;

}

// spi flash 页面烧写
void CUpperComputerDlg::SpiFlashPageProgram(unsigned __int64 uint64_StartAddr, BYTE *lpBuf, unsigned int uint_DataLength )
{


    // 拉高spi-flash的片选信号，终止当前操作
	FpgaWrite(0,0x40,0x1);
    // 拉低spi-flash的片选信号
	FpgaWrite(0,0x40,0x0);
    // 写入 Write Enable (06h)  指令
	FpgaWrite(0,0x41,0x06);
    // 拉高spi-flash的片选信号，执行指令
	FpgaWrite(0,0x40,0x1);

    // 拉低spi-flash的片选信号
	FpgaWrite(0,0x40,0x0);
   // 写入 Page Program (02h)  指令
	FpgaWrite(0,0x41,0x02);
    // 写入起始地址的[23:16]
	FpgaWrite(0,0x41,((uint64_StartAddr >> 16) & 0x00000000000000ff));
    // 写入起始地址的[15:8]
	FpgaWrite(0,0x41,((uint64_StartAddr >> 8) & 0x00000000000000ff));
    // 写入起始地址的[7:0]
	FpgaWrite(0,0x41,(uint64_StartAddr & 0x00000000000000ff));

    // 写入数据
    // char 扩展到__int64时，需要屏蔽掉高位，编译器扩展时是把char的最高位复制到__int64的高位
	FpgaBlockWrite(0x41,lpBuf,1,uint_DataLength);
    


    // 拉高spi-flash的片选信号，执行指令
	FpgaWrite(0,0x40,0x1);


}



// 响应函数
/*
void CUpperComputerDlg::OnBnClickedButtonConnect()
{
	BYTE byte_IPAddr[4];

	// 获得输入的服务器IP地址
	Idc_IPaddress_ServerIPAddr.GetAddress(byte_IPAddr[0],byte_IPAddr[1],byte_IPAddr[2],byte_IPAddr[3]);
	str_ServerIPAddress.Format(_T("%d.%d.%d.%d"),byte_IPAddr[0],byte_IPAddr[1],byte_IPAddr[2],byte_IPAddr[3]);
	// 获得服务器状态端口号
	Idc_Edit_ServerStatusPort.GetWindowText(str_ServerStatusPort);
	uint_ServerStatusPort = (unsigned int)_ttoi(str_ServerStatusPort);

	// 建立客户端进行连接服务端
	m_StatusSocket = new StatusSocket();
	m_StatusSocket->Create(); 

	//设置发送缓冲区的小大为64k
	int nSize = 64 * 1024; 
	m_StatusSocket->SetSockOpt(SO_SNDBUF, (char *)nSize, sizeof(int));
	//设置接收缓冲区的小大为64k
	m_StatusSocket->SetSockOpt(SO_RCVBUF, (char *)nSize, sizeof(int));

	if(m_StatusSocket->Connect(str_ServerIPAddress,uint_ServerStatusPort))   
	{

		// 已连接,连接按钮设为不可用
		Idc_Button_ServerConnect.SetWindowText(_T("已连接"));
		Idc_Button_ServerConnect.EnableWindow(FALSE);
	    // 断开连接可用
	    Idc_Button_ServerDisconnect.SetWindowText(_T("断开"));
		Idc_Button_ServerDisconnect.EnableWindow(TRUE);
		m_StatusSocket->Init();//初始化,以便通信

		m_ServerConnectStatus = 1;


		// 日志：“服务器连接成功：”
		// “IP地址：xxx”
		// “端口号：TCP-xxxx”
        WriteLogFile(1,_T("服务器连接成功："));
        WriteLogFile(0,_T("IP地址：")+str_ServerIPAddress);
        WriteLogFile(0,_T("端口号：")+str_ServerStatusPort);

		// 连接成功后，向服务器发送注册请求
		SendCmd(CString(_T("<Register><Id>")) + str_UpperComputerID + CString(_T("</Id></Register>")));
	

	}
	else   
	{		


		m_ServerConnectStatus = 0;
        m_ServerRegisterStatus = 0;

        //关闭文件
        m_StatusSocket->f_LoadFile.Abort();

		// 日志：“服务器连接失败：”
		// “IP地址：xxx”
		// “端口号：TCP-xxxx”
        WriteLogFile(1,_T("服务器连接失败："));
        WriteLogFile(0,_T("IP地址：")+str_ServerIPAddress);
        WriteLogFile(0,_T("端口号：")+str_ServerStatusPort);

		return;
	}

}
*/
void CUpperComputerDlg::OnBnClickedButtonConnect()// 为WebSocket重写之
{
    WriteLogFile(1, _T("正在连接......"));
    BYTE byte_IPAddr[4];
    // 获得输入的服务器IP地址
    Idc_IPaddress_ServerIPAddr.GetAddress(byte_IPAddr[0], byte_IPAddr[1], byte_IPAddr[2], byte_IPAddr[3]);
    str_ServerIPAddress.Format(_T("%d.%d.%d.%d"), byte_IPAddr[0], byte_IPAddr[1], byte_IPAddr[2], byte_IPAddr[3]);
    // 获得端口号
    Idc_Edit_ServerStatusPort.GetWindowText(str_ServerStatusPort);
    uint_ServerStatusPort = (unsigned int)_ttoi(str_ServerStatusPort);
    // say: ws://127.0.0.1:9002
    CString uri = "ws://" + str_ServerIPAddress + ":" + str_ServerStatusPort;
    bool success = wsEndpoint->connect(LPCSTR(uri)) == 1;
    /*
    while(wsEndpoint->getConStatus() == "Connecting"){}// wait for connecting
    success &= wsEndpoint->getConStatus() == "Open";// successfully open
    if (success)
    {
        // 已连接,连接按钮设为不可用
        Idc_Button_ServerConnect.SetWindowText(_T("已连接"));
        Idc_Button_ServerConnect.EnableWindow(FALSE);
        // 断开连接可用
        Idc_Button_ServerDisconnect.SetWindowText(_T("断开"));
        Idc_Button_ServerDisconnect.EnableWindow(TRUE);
        // 连接状态置1
        m_ServerConnectStatus = 1;

        // 连接成功后发送注册请求
        wsEndpoint->send(std::string("<Register><Id>") + LPCSTR(str_UpperComputerID) + "</Id></Register>");
    }
    else// fail to connect
    {
        // 状态不变
        m_ServerConnectStatus = 0;
        m_ServerRegisterStatus = 0;
    }*/
}
/*
void CUpperComputerDlg::OnBnClickedButtonDisconnect()
{

	m_StatusSocket->Close();

    // 更新工作模式为实验模式
    str_WorkMode = _T("ExperimentMode");

    // 更新上位机状态
    str_WorkStatus = _T("Ready");

    // 更新服务器连接状态指示
	m_ServerConnectStatus = 0;
    // 更新服务器注册状态指示
    m_ServerRegisterStatus = 0;

    // 初始化数据写入主控fpga
    FpgaWrite(0,0x10,0xffffffffffffffff);

    //关闭文件
    m_StatusSocket->f_LoadFile.Abort();

    //已断开,连接按钮设为可用
	Idc_Button_ServerConnect.SetWindowText(_T("连接"));
	Idc_Button_ServerConnect.EnableWindow(TRUE);

	//断开连接不可用
	Idc_Button_ServerDisconnect.SetWindowText(_T("已断开"));
	Idc_Button_ServerDisconnect.EnableWindow(FALSE);


	// 日志：“服务器连接中断：”
	// “IP地址：xxx”
	// “端口号：xxxx”
    WriteLogFile(1,_T("服务器连接中断："));
    WriteLogFile(0,_T("IP地址：")+str_ServerIPAddress);
    WriteLogFile(0,_T("端口号：")+str_ServerStatusPort);

}*/

void CUpperComputerDlg::OnBnClickedButtonDisconnect()// 重写
{
    wsEndpoint->close(1000, "User clicked to close.");
    // 关闭相关定时器
    KillTimer(TIMERID_DATA_SAMPLE);
    KillTimer(TIMERID_TEST_DATA_SAMPLE);
    KillTimer(TIMERID_FILEREV);

    // 更新工作模式为实验模式
    str_WorkMode = _T("ExperimentMode");
    // 更新上位机状态
    str_WorkStatus = _T("Ready");
    // 初始化数据写入主控fpga
    FpgaWrite(0, 0x10, 0xffffffffffffffff);
    // 更新状态
    m_ServerConnectStatus = 0;
    m_ServerRegisterStatus = 0;
    //已断开,连接按钮设为可用
    Idc_Button_ServerConnect.SetWindowText(_T("连接"));
    Idc_Button_ServerConnect.EnableWindow(TRUE);
    //断开连接不可用
    Idc_Button_ServerDisconnect.SetWindowText(_T("已断开"));
    Idc_Button_ServerDisconnect.EnableWindow(FALSE);
}



void CUpperComputerDlg::OnTimer(UINT nIDEvent)
{
    CString str_FpgaReadData0;
    CString str_FpgaReadData1;
	CString str_temp;

    if (nIDEvent == TIMERID_CHECK_CONNECT)
    {
        if (m_ServerConnectStatus == 1)
        {
            int time = CTime::GetCurrentTime().GetTime();
            if (time - last_check_time >= 20)
            {
                wsEndpoint->close(1000, "timeout");
            }
        }
    }
    if ( nIDEvent == TIMERID_REGISTER )
	{
		// 连接不成功，继续向服务器发送连接请求
		if (m_ServerConnectStatus == 0)
		{
            // 关闭相关定时器
            KillTimer(TIMERID_DATA_SAMPLE);
            KillTimer(TIMERID_TEST_DATA_SAMPLE);
            KillTimer(TIMERID_FILEREV);

			OnBnClickedButtonConnect();
            m_ServerRegisterStatus = 0;
            //关闭文件
            //m_StatusSocket->f_LoadFile.Abort();
            wsEndpoint->closeFile();

		}
		// 注册不成功，继续向服务器发送注册请求
		else if (m_ServerRegisterStatus == 0)
		{
            // 关闭相关定时器
            KillTimer(TIMERID_DATA_SAMPLE);
            KillTimer(TIMERID_TEST_DATA_SAMPLE);
            KillTimer(TIMERID_FILEREV);

            // 日志：“服务器注册失败：”
            WriteLogFile(1,_T("服务器注册失败。"));

            // 向服务器发送注册指令
            wsEndpoint->send(std::string("<Register><Id>") + LPCSTR(str_UpperComputerID) + "</Id></Register>");
		}
        // 如果主控串口没打开，继续执行打开操作
        if (cpubsub_MasterCom.m_hCom==INVALID_HANDLE_VALUE)
        {
            AutoOpenMasterCom();
        }
	}
	else if ( nIDEvent == TIMERID_DATA_SAMPLE )
	{
        if (str_WorkMode == _T("ExperimentMode"))
        {

            // 读取采集数据0和数据1，设置数据0
            str_FpgaReadData0 = FpgaRead(0x20);
            str_FpgaReadData1 = FpgaRead(0x21);
            str_FpgaSetData0  = FpgaRead(0x11);
            str_FpgaSetData1  = FpgaRead(0x13);


          //  if (1 == Idc_Check_LogDisplay.GetCheck())
          //  {
		        //// 日志：“读取采集数据0和数据1：”
          //      WriteLogFile(1,_T("读取采集数据0和数据1："));
          //      WriteLogFile(0,str_FpgaReadData0);
          //      WriteLogFile(0,str_FpgaReadData1);
          //      WriteLogFile(0,str_FpgaSetData0);
          //      WriteLogFile(0,str_FpgaSetData1);

          //  }


            // 如果有变化，发送给服务器
            // 校验
            //if (((str_FpgaSampleData0 != str_FpgaReadData0)||(str_FpgaSampleData1 != str_FpgaReadData1)) && (str_FpgaSetData0.Mid(4,2) == str_FpgaSetData0.Mid(6,2)))
            // 不校验
            if (((str_FpgaSampleData0 != str_FpgaReadData0)||(str_FpgaSampleData1 != str_FpgaReadData1)))
            {
                // 更新数据
                str_FpgaSampleData0 = str_FpgaReadData0;
                str_FpgaSampleData1 = str_FpgaReadData1;
                // 发送数据指令：<Data>…</Data>
                //SendCmd(_T("<Data>")+str_FpgaSampleData0+str_FpgaSampleData1.Mid(16-10,10)+str_FpgaSetData0.Mid(16-4,4)+str_FpgaSetData1+_T("</Data>"));
                CString toSend = _T("<Data>") + str_FpgaSampleData0 + str_FpgaSampleData1.Mid(16 - 10, 10) + str_FpgaSetData0.Mid(16 - 4, 4) + str_FpgaSetData1 + _T("</Data>");
                wsEndpoint->send(LPCSTR(toSend));
            }


            //读取鼠标键盘数据
            CString str_FpgaReadTmp;
            CString str_Ps2MouseSendData = _T("");
            int int_Ps2MouseSendDataLength = 0;
            CString str_Ps2KeyboardSendData = _T("");
            int int_Ps2KeyboardSendDataLength = 0;
            CString str_ExpComSendData = _T("");
            int int_ExpComSendDataLength = 0;
            CString str_Ps2MouseDataVld;
            CString str_Ps2KeyboardDataVld;
            CString str_ExpComDataVld;
            do
            {
                // 读取鼠标、键盘、实验串口状态，判断主机是否发送数据
                str_FpgaReadTmp = FpgaRead(0x38);
                // 截取鼠标数据有效位
                str_Ps2MouseDataVld = str_FpgaReadTmp.Mid(10, 1);
                // 截取键盘数据有效位
                str_Ps2KeyboardDataVld = str_FpgaReadTmp.Mid(13, 1);
                // 截取实验串口数据有效位
                str_ExpComDataVld = str_FpgaReadTmp.Mid(7, 1);

                // 截取鼠标数据
                if (str_Ps2MouseDataVld == _T("1"))
                {
                    int_Ps2MouseSendDataLength++;
                    str_Ps2MouseSendData += str_FpgaReadTmp.Mid(11, 2);
                }
                // 截取键盘数据
                if (str_Ps2KeyboardDataVld == _T("1"))
                {
                    int_Ps2KeyboardSendDataLength++;
                    str_Ps2KeyboardSendData += str_FpgaReadTmp.Mid(14, 2);
                }
                // 截取实验串口数据
                if (str_ExpComDataVld == _T("1"))
                {
                    int_ExpComSendDataLength++;
                    str_ExpComSendData += str_FpgaReadTmp.Mid(8, 2);
                }

            } while (((str_Ps2MouseDataVld == _T("1")) | (str_Ps2KeyboardDataVld == _T("1")) | (str_ExpComDataVld == _T("1"))) && (int_Ps2MouseSendDataLength < 256) && (int_Ps2KeyboardSendDataLength < 256) && (int_ExpComSendDataLength < 256));

            // 给客户端发送鼠标键盘数据指令：<PS2Send><MouseLength>…</MouseLength><MouseData>…</MouseData>
            //                               <KeyboardLength>…</KeyboardLength><KeyboardData>…</KeyboardData></PS2Send>
            if ((int_Ps2MouseSendDataLength > 0) || (int_Ps2KeyboardSendDataLength > 0))
            {
                CString str_Ps2MouseSendDataLength;
                CString str_Ps2KeyboardSendDataLength;

                str_Ps2MouseSendDataLength.Format(_T("%d"), int_Ps2MouseSendDataLength);
                str_Ps2KeyboardSendDataLength.Format(_T("%d"), int_Ps2KeyboardSendDataLength);

                //SendCmd(_T("<PS2Send><MouseLength>") + str_Ps2MouseSendDataLength + _T("</MouseLength><MouseData>") + str_Ps2MouseSendData + _T("</MouseData><KeyboardLength>") + str_Ps2KeyboardSendDataLength + _T("</KeyboardLength><KeyboardData>") + str_Ps2KeyboardSendData + _T("</KeyboardData></PS2Send>"));
                CString toSend = _T("<PS2Send><MouseLength>") + str_Ps2MouseSendDataLength + _T("</MouseLength><MouseData>") + str_Ps2MouseSendData + _T("</MouseData><KeyboardLength>") + str_Ps2KeyboardSendDataLength + _T("</KeyboardLength><KeyboardData>") + str_Ps2KeyboardSendData + _T("</KeyboardData></PS2Send>");
                wsEndpoint->send(LPCSTR(toSend));
            }

            // 向服务器发送实验串口接收到的数据指令：<COMSend><Length>…</Length><Data>…</Data></COMSend>
            if ((int_ExpComSendDataLength > 0) && bool_ExpComStatus)
            {
                CString str_ExpComSendDataLength;

                str_ExpComSendDataLength.Format(_T("%d"), int_ExpComSendDataLength);

                //SendCmd(_T("<COMSend><Length>") + str_ExpComSendDataLength + _T("</Length>") + _T("<Data>") + str_ExpComSendData + _T("</Data></COMSend>"));
                CString toSend = _T("<COMSend><Length>") + str_ExpComSendDataLength + _T("</Length>") + _T("<Data>") + str_ExpComSendData + _T("</Data></COMSend>");
                wsEndpoint->send(LPCSTR(toSend));
            }
        }


    }
	else if ( nIDEvent == TIMERID_TEST_DATA_SAMPLE )
	{
	    // 关闭自动测试数据采集定时器
	    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->KillTimer(TIMERID_TEST_DATA_SAMPLE);

        if (str_WorkMode == _T("TestMode"))
        {
            // 读取采集数据0和数据1，设置数据0
            str_FpgaReadData0 = FpgaRead(0x20);
            str_FpgaReadData1 = FpgaRead(0x21);
            str_FpgaSetData0  = FpgaRead(0x11);
            str_FpgaSetData1  = FpgaRead(0x13);


            // 直接把采集到的数据发送给服务器
            // 发送测试返回数据指令：<Test>…</Test>
            //SendCmd(_T("<Test>")+str_FpgaReadData0+str_FpgaReadData1.Mid(16-10,10)+str_FpgaSetData0.Mid(16-4,4)+str_FpgaSetData1+_T("</Test>"));
            CString toSend = _T("<Test>") + str_FpgaReadData0 + str_FpgaReadData1.Mid(16 - 10, 10) + str_FpgaSetData0.Mid(16 - 4, 4) + str_FpgaSetData1 + _T("</Test>");
            wsEndpoint->send(LPCSTR(toSend));
        }

    }
    // 文件接收超时
	else if ( nIDEvent == TIMERID_FILEREV )
	{

        // 关闭文件接收超时定时器
	    KillTimer(TIMERID_FILEREV);

        // 加载文件接收使能关闭
        //m_StatusSocket->bool_ServerFileRevEn = 0;
        wsEndpoint->setFileRcvEnable(false);
        //关闭文件
        //m_StatusSocket->f_LoadFile.Abort();
        wsEndpoint->closeFile();

		// 发送接收失败指令:<Receive><Result>…</Result></Receive>
		//SendCmd(_T("<Receive><Result>Failed</Result></Receive>")); 
        wsEndpoint->send("<Receive><Result>Failed</Result></Receive>");

		// 日志："文件接收失败："
        WriteLogFile(1,_T("文件接收失败：文件接收超时。"));
        

    }

	else if (nIDEvent == TIMERID_JTAG_TIMEOUT)
	{	
        // 关闭JTAG加载超时定时器
		KillTimer(TIMERID_JTAG_TIMEOUT);
		
		if (int_FpgaUpdateMode == FPGA_UPDATE_MODE_LOCAL)
		{
            WriteLogFile(1, _T("FPGA 升级：\r\nFPGA本地加载超时失败！"));
		}
		else if (int_FpgaUpdateMode == FPGA_UPDATE_MODE_ONLINE)
		{
            WriteLogFile(1, _T("FPGA 升级：\r\nFPGA在线加载超时失败！"));

			// 发送烧录失败指令:<Loaded><Result>…</Result></Loaded>
			//SendCmd(_T("<Loaded><Result>Failed</Result></Loaded>")); 
            wsEndpoint->send("<Loaded><Result>Failed</Result></Loaded>");
			// 更新上位机状态
			str_WorkStatus = _T("Ready");
		}

	}
	else if (nIDEvent == TIMERID_HARDWARE_TEST)
	{	
		CString str_HardwareTestSel;
		CString str_WindowText;
		CString str_temp1;

		Idc_Combo_HardwareTestSel.GetWindowText(str_HardwareTestSel);

		if (str_HardwareTestSel == _T("JTAG接口"))
		{
			// 启动jtag测试
			if (int_HWTTimeOutCnt == 0)
			{
				if (PathFileExists(_T("program\\ExpFpgaTest.bit")))
				{
					int_HWTTimeOutCnt++;

					// 设置实验fpga测试bit文件路径
					Idc_Edit_FpgaUpdateFilePath.SetWindowText(_T("program\\ExpFpgaTest.bit"));
					// 选择jtag加载模式
					Idc_Check_FPGAUpdateAutoTestEn.SetCheck(0);
					Idc_Radio_FPGAUpdateJtagSelect.SetCheck(1);
					Idc_Radio_FPGAUpdateSpiFlashSelect.SetCheck(0);
					// 设置fpga加载模式为本地模式
					int_FpgaUpdateMode = FPGA_UPDATE_MODE_LOCAL;

                    WriteLogFile(1, _T("硬件自检：\r\n启动JTAG接口测试。。。"));

					// 启动jtag加载线程
					FpgaUpdateThreadStart();


				}
				else 
				{
                    WriteLogFile(1, _T("硬件自检：\r\n没有发现实验fpga测试bit文件！\r\n退出硬件自检程序！"));
					OnBnClickedButtonHardwareteststop();
				}
			
			}
			// 已启动jtag测试，未超时60秒
			else if (int_HWTTimeOutCnt < HWT_JTAG_TIMEOUT)
			{
				int_HWTTimeOutCnt++;

				if (int_FpgaUpdateStatus == 1)
				{
					WriteLogFile(1,_T("硬件自检："));
					WriteLogFile(0,_T("JTAG接口测试成功！"));

					if (Idc_Check_HardwareTestAutoEn.GetCheck()) 
					{
						Idc_Combo_HardwareTestSel.SetWindowText(_T("实验串口"));
						int_HWTTimeOutCnt = 0;
					}
					else
					{
						OnBnClickedButtonHardwareteststop();
					}

				}
				else if (int_FpgaUpdateStatus == 2)
				{
					WriteLogFile(1,_T("硬件自检："));
					WriteLogFile(0,_T("JTAG接口测试失败！"));
					WriteLogFile(0,_T("退出硬件自检程序！"));
					OnBnClickedButtonHardwareteststop();
				}
			
			}
			// 已启动jtag测试，超时
			else
			{
				WriteLogFile(1,_T("硬件自检："));
				WriteLogFile(0,_T("JTAG接口测试超时失败！"));
				WriteLogFile(0,_T("退出硬件自检程序！"));
				OnBnClickedButtonHardwareteststop();
			
			
			}


		}
		else if (str_HardwareTestSel == _T("实验串口"))
		{
			// 启动
			if (int_HWTTimeOutCnt == 0)
			{
				// 写入测试数据
				ExpFpgaWrite(0, 0x1, 0x1122334455667788);
				WriteLogFile(1,_T("硬件自检："));
				WriteLogFile(0,_T("启动实验串口测试。。。"));

				int_HWTTimeOutCnt++;

			
			}
			// 已启动实验串口测试，未超时1秒
			else if (int_HWTTimeOutCnt < HWT_EXPCOM_TIMEOUT)
			{
				int_HWTTimeOutCnt++;

				if (ExpFpgaRead(0x1) == _T("1122334455667788"))
				{
					WriteLogFile(1,_T("硬件自检："));
					WriteLogFile(0,_T("实验串口测试成功！"));

					if (Idc_Check_HardwareTestAutoEn.GetCheck()) 
					{
						Idc_Combo_HardwareTestSel.SetWindowText(_T("数码管"));
						int_HWTTimeOutCnt = 0;
					}
					else
					{
						OnBnClickedButtonHardwareteststop();

					}

				}
			}
			// 已启动实验串口测试，超时1秒
			else
			{
				WriteLogFile(1,_T("硬件自检："));
				WriteLogFile(0,_T("实验串口测试超时失败！"));
				WriteLogFile(0,_T("退出硬件自检程序！"));

				OnBnClickedButtonHardwareteststop();
			}



		}
		else if (str_HardwareTestSel == _T("数码管"))
		{
			// 启动
			if (int_HWTTimeOutCnt == 0)
			{
				uint64_HWTPattern = 0x0000000000000001;
				// 写入测试数据,先测试数据位，共64位
				ExpFpgaWrite(0, 0x21, uint64_HWTPattern);
				ExpFpgaWrite(0, 0x20, 0x0);
				ExpFpgaWrite(0, 0x20, 0x3);
				WriteLogFile(1,_T("硬件自检："));
				WriteLogFile(0,_T("启动数码管测试。。。"));

				int_HWTTimeOutCnt++;

			
			}
			// 已启动数码管测试，测试数据位
			else if (int_HWTTimeOutCnt <= 64)
			{
				// 读取主控fpga采集到的数码管显示信息
				str_FpgaReadData0 = FpgaRead(0x20);
				str_FpgaReadData1 = FpgaRead(0x21);

				str_temp.Format(_T("%016llx"),uint64_HWTPattern);
				str_temp1 = str_FpgaReadData1.Mid(12, 2) + str_FpgaReadData1.Mid(10, 2) + str_FpgaReadData1.Mid(8, 2) + str_FpgaReadData1.Mid(6, 2) + str_FpgaReadData0.Mid(14, 2) + str_FpgaReadData0.Mid(12, 2) + str_FpgaReadData0.Mid(10, 2) + str_FpgaReadData0.Mid(8, 2);
                WriteLogFile(1, _T("硬件自检：\r\n数码管数据位测试图案：0x") + str_temp + _T("\r\n数码管数据位测试显示图案：0x") + str_temp1);

				if (str_temp1 == str_temp)
				{
					// 测试符号位
					if(int_HWTTimeOutCnt == 64)
					{
						uint64_HWTPattern = 0x0000000000000001;
						ExpFpgaWrite(0, 0x21, 0x0000000000000000);
						ExpFpgaWrite(0, 0x22, uint64_HWTPattern);
						ExpFpgaWrite(0, 0x20, 0x0);
						ExpFpgaWrite(0, 0x20, 0x3);
					}
					// 继续测试数据位
					else
					{
						uint64_HWTPattern = uint64_HWTPattern << 1;
						ExpFpgaWrite(0, 0x21, uint64_HWTPattern);
						ExpFpgaWrite(0, 0x20, 0x0);
						ExpFpgaWrite(0, 0x20, 0x3);
					
					}

				}
				else
				{
					WriteLogFile(1,_T("硬件自检："));
					WriteLogFile(0,_T("数码管测试失败！"));
					WriteLogFile(0,_T("退出硬件自检程序！"));
					OnBnClickedButtonHardwareteststop();
				
				}
				int_HWTTimeOutCnt++;

			}
			// 已启动数码管测试，测试符号位
			else if (int_HWTTimeOutCnt <= 72)
			{

				// 读取主控fpga采集到的数码管显示信息
				str_FpgaReadData0 = FpgaRead(0x21);

				str_temp.Format(_T("%02x"),uint64_HWTPattern);
				WriteLogFile(1,_T("硬件自检："));
				WriteLogFile(0,_T("数码管符号位测试图案：0x")+str_temp);
				WriteLogFile(0,_T("数码管符号位测试显示图案：0x") + str_FpgaReadData0.Mid(14, 2));

				if (str_FpgaReadData0.Mid(14, 2) == str_temp)
				{
					// 继续测试符号位
					uint64_HWTPattern = uint64_HWTPattern << 1;
					ExpFpgaWrite(0, 0x22, uint64_HWTPattern);
					ExpFpgaWrite(0, 0x20, 0x0);
					ExpFpgaWrite(0, 0x20, 0x3);
					

				}
				else
				{
					WriteLogFile(1,_T("硬件自检："));
					WriteLogFile(0,_T("数码管测试失败！"));
					WriteLogFile(0,_T("退出硬件自检程序！"));
					OnBnClickedButtonHardwareteststop();
				
				}
				int_HWTTimeOutCnt++;


			}
			else if (int_HWTTimeOutCnt == 73)
			{
				WriteLogFile(1,_T("硬件自检："));
				WriteLogFile(0,_T("数码管测试成功！"));

				if (Idc_Check_HardwareTestAutoEn.GetCheck()) 
				{
					Idc_Combo_HardwareTestSel.SetWindowText(_T("LED"));
					int_HWTTimeOutCnt = 0;
				}
				else
				{
					OnBnClickedButtonHardwareteststop();

				}

			}
		}
		else if (str_HardwareTestSel == _T("LED"))
		{
			// 启动
			if (int_HWTTimeOutCnt == 0)
			{
				uint64_HWTPattern = 0x0000000000000001;
				// 写入测试数据,共32位
				ExpFpgaWrite(0, 0x30, uint64_HWTPattern);
				WriteLogFile(1,_T("硬件自检："));
				WriteLogFile(0,_T("启动LED测试。。。"));

				int_HWTTimeOutCnt++;
			
			}
			// 已启动LED测试
			else if (int_HWTTimeOutCnt <= 32)
			{
				int_HWTTimeOutCnt++;

				// 读取主控fpga采集到的LED显示信息
				str_FpgaReadData0 = FpgaRead(0x20);

				str_temp.Format(_T("%08x"),uint64_HWTPattern);
				str_temp1 = str_FpgaReadData0.Mid(6, 2)+ str_FpgaReadData0.Mid(4, 2)+ str_FpgaReadData0.Mid(2, 2)+ str_FpgaReadData0.Mid(0, 2);
                WriteLogFile(1, _T("硬件自检：\r\nLED测试图案：0x") + str_temp + _T("\r\nLED测试显示图案：0x") + str_temp1);

				if (str_temp1 == str_temp)
				{
					// 继续测试
					uint64_HWTPattern = uint64_HWTPattern << 1;
					ExpFpgaWrite(0, 0x30, uint64_HWTPattern);
					

				}
				else
				{
					WriteLogFile(1,_T("硬件自检："));
					WriteLogFile(0,_T("LED测试失败！"));
					WriteLogFile(0,_T("退出硬件自检程序！"));
					OnBnClickedButtonHardwareteststop();
				
				}
			}
			else if (int_HWTTimeOutCnt == 33)
			{
				WriteLogFile(1,_T("硬件自检："));
				WriteLogFile(0,_T("LED测试成功！"));

				if (Idc_Check_HardwareTestAutoEn.GetCheck()) 
				{
					Idc_Combo_HardwareTestSel.SetWindowText(_T("拨码开关"));
					int_HWTTimeOutCnt = 0;
				}
				else
				{
					OnBnClickedButtonHardwareteststop();

				}

			}
		}
		else if (str_HardwareTestSel == _T("拨码开关"))
		{
			// 启动
			if (int_HWTTimeOutCnt == 0)
			{
				uint64_HWTPattern = 0x0000000000000001;
				// 写入测试数据,共64位
				FpgaWrite(0, 0x12, ~uint64_HWTPattern);
				WriteLogFile(1,_T("硬件自检："));
				WriteLogFile(0,_T("启动拨码开关测试。。。"));

				int_HWTTimeOutCnt++;


			
			}
			// 已启动拨码开关测试
			else if (int_HWTTimeOutCnt <= 64)
			{
				int_HWTTimeOutCnt++;

				// 读取实验fpga采集到的拨码开关信息
				str_FpgaReadData0 = ExpFpgaRead(0x10);

				str_temp.Format(_T("%016llx"),~uint64_HWTPattern);
				str_temp1 = str_FpgaReadData0.Mid(14, 2)+ str_FpgaReadData0.Mid(12, 2)+ str_FpgaReadData0.Mid(10, 2)+ str_FpgaReadData0.Mid(8, 2) +str_FpgaReadData0.Mid(6, 2)+ str_FpgaReadData0.Mid(4, 2)+ str_FpgaReadData0.Mid(2, 2)+ str_FpgaReadData0.Mid(0, 2);
                WriteLogFile(1, _T("硬件自检：\r\n拨码开关测试图案：0x") + str_temp + _T("\r\n拨码开关测试显示图案：0x") + str_temp1);

				if (str_temp1 == str_temp)
				{
					// 继续测试
					uint64_HWTPattern = uint64_HWTPattern << 1;
					FpgaWrite(0, 0x12, (~uint64_HWTPattern));
					

				}
				else
				{
					WriteLogFile(1,_T("硬件自检："));
					WriteLogFile(0,_T("拨码开关测试失败！"));
					WriteLogFile(0,_T("退出硬件自检程序！"));
					OnBnClickedButtonHardwareteststop();
				
				}
			}
			else if (int_HWTTimeOutCnt == 65)
			{
				WriteLogFile(1,_T("硬件自检："));
				WriteLogFile(0,_T("拨码开关测试成功！"));

				if (Idc_Check_HardwareTestAutoEn.GetCheck()) 
				{
					Idc_Combo_HardwareTestSel.SetWindowText(_T("按键"));
					int_HWTTimeOutCnt = 0;
				}
				else
				{
					OnBnClickedButtonHardwareteststop();

				}

			}
		}
		else if (str_HardwareTestSel == _T("按键"))
		{
			// 启动
			if (int_HWTTimeOutCnt == 0)
			{
				uint64_HWTPattern = 0x0000000000000001;
				// 写入测试数据,共8位，bit-13是实验fpga的prog-b信号
				FpgaWrite(0, 0x10, (~uint64_HWTPattern) | 0x0000000000000200);
				WriteLogFile(1,_T("硬件自检："));
				WriteLogFile(0,_T("启动按键测试。。。"));

				int_HWTTimeOutCnt++;

			
			}
			// 已启动按键测试
			else if (int_HWTTimeOutCnt <= 8)
			{
				int_HWTTimeOutCnt++;

				// 读取实验fpga采集到的按键信息
				str_FpgaReadData0 = ExpFpgaRead(0x11);

				str_temp.Format(_T("%02x"),((BYTE)(~uint64_HWTPattern)));
                WriteLogFile(1, _T("硬件自检：\r\n按键测试图案：0x") + str_temp + _T("\r\n按键测试显示图案：0x") + str_FpgaReadData0.Mid(14, 2));

				if (str_FpgaReadData0.Mid(14, 2) == str_temp)
				{
					// 继续测试
					uint64_HWTPattern = uint64_HWTPattern << 1;
					FpgaWrite(0, 0x10, ((~uint64_HWTPattern) | 0x0000000000000200));
					

				}
				else
				{
					WriteLogFile(1,_T("硬件自检："));
					WriteLogFile(0,_T("按键测试失败！"));
					WriteLogFile(0,_T("退出硬件自检程序！"));
					OnBnClickedButtonHardwareteststop();
				
				}
			}
			else if (int_HWTTimeOutCnt == 9)
			{
				WriteLogFile(1,_T("硬件自检："));
				WriteLogFile(0,_T("按键测试成功！"));

				if (Idc_Check_HardwareTestAutoEn.GetCheck()) 
				{
					Idc_Combo_HardwareTestSel.SetWindowText(_T("PS2接口"));
					int_HWTTimeOutCnt = 0;
				}
				else
				{
					OnBnClickedButtonHardwareteststop();

				}

			}
		}
		else if (str_HardwareTestSel == _T("PS2接口"))
		{
			unsigned __int64 uint64_FpgaReadTmp;

            // 启动
            if (int_HWTTimeOutCnt == 0)
            {
                // 复位实验fpga的鼠标模块，bit-13是实验fpga的prog-b信号
                FpgaWrite(0, 0x10, 0x0000000000000200);
                Sleep(10);
                FpgaWrite(0, 0x10, 0x0000000000000201);
                WriteLogFile(1, _T("硬件自检：\r\n启动PS2接口测试。。。"));

                int_HWTTimeOutCnt++;
                int_HWTCnt = 0;

            }
            // 已启动PS2接口测试，未超时
            else if (int_HWTTimeOutCnt < HWT_PS2_TIMEOUT)
            {
                int_HWTTimeOutCnt++;

                if (int_HWTCnt == 0)
                {
                    // 读取鼠标状态，判断主机是否发送数据
                    uint64_FpgaReadTmp = _tcstoui64(FpgaRead(0x38), 0, 16);

                    if ((uint64_FpgaReadTmp & 0x0000000000100000) == 0x0000000000100000)
                    {
                        // 判断接收到的数据
                        if ((uint64_FpgaReadTmp & 0x00000000000ff000) == 0x00000000000ff000)
                        {
                            // 返回应答数据
                            FpgaWrite(0, 0x31, 0xfa);
                            FpgaWrite(0, 0x31, 0xaa);
                            int_HWTCnt++;
                        }
                    }
                }
                else if (int_HWTCnt == 1)
                {
                    // 读取鼠标状态，判断主机是否发送数据
                    uint64_FpgaReadTmp = _tcstoui64(FpgaRead(0x38), 0, 16);

                    if ((uint64_FpgaReadTmp & 0x0000000000100000) == 0x0000000000100000)
                    {
                        // 判断接收到的数据
                        if ((uint64_FpgaReadTmp & 0x00000000000ff000) == 0x00000000000f4000)
                        {
                            // 返回应答数据
                            FpgaWrite(0, 0x31, 0xfa);
                            int_HWTCnt++;

                        }
                    }
                }
                else if (int_HWTCnt == 2)
                {
                    int_HWTCnt++;

                    // 键盘状态初始化
                    FpgaWrite(0, 0x30, 0xf0);
                    FpgaWrite(0, 0x30, 0x1b);
                    FpgaWrite(0, 0x30, 0xf0);
                    FpgaWrite(0, 0x30, 0x1c);

                    // 鼠标状态初始化
                    FpgaWrite(0, 0x31, 0x08);
                    FpgaWrite(0, 0x31, 0x00);
                    FpgaWrite(0, 0x31, 0x00);
                }
                else if (int_HWTCnt == 3)
                {
                    int_HWTCnt++;

                    // 发送键盘"A"键值,需连续发送2个
                    FpgaWrite(0, 0x30, 0x1c);
                    FpgaWrite(0, 0x30, 0x1c);


                }
                else if (int_HWTCnt == 4)
                {
                    int_HWTCnt++;

                    // 读取实验fpga采集到的键盘"A"键值信息
                    str_FpgaReadData0 = ExpFpgaRead(0x98);

                    if (str_FpgaReadData0.Mid(13, 3) == _T("11c"))
                    {
                        WriteLogFile(1, _T("硬件自检：\r\n键盘\"A\"键按下测试。。。"));

                        // 取消键盘"A"键值
                        FpgaWrite(0, 0x30, 0xf0);
                        FpgaWrite(0, 0x30, 0x1c);


                    }
                    else
                    {
                        WriteLogFile(1, _T("硬件自检：\r\n键盘\"A\"键按下测试失败！\r\n退出硬件自检程序！"));
                        OnBnClickedButtonHardwareteststop();

                    }

                }
                else if (int_HWTCnt == 5)
                {
                    int_HWTCnt++;

                    // 读取实验fpga采集到的键盘"A"键值信息
                    str_FpgaReadData0 = ExpFpgaRead(0x98);

                    if (str_FpgaReadData0.Mid(13, 3) == _T("01c"))
                    {
                        WriteLogFile(1, _T("硬件自检：\r\n键盘\"A\"键取消测试。。。"));

                        // 发送鼠标左键键值
                        FpgaWrite(0, 0x31, 0x09);
                        FpgaWrite(0, 0x31, 0x00);
                        FpgaWrite(0, 0x31, 0x00);


                    }
                    else
                    {
                        WriteLogFile(1, _T("硬件自检：\r\n键盘\"A\"键取消测试失败！\r\n退出硬件自检程序！"));
                        OnBnClickedButtonHardwareteststop();

                    }

                }
                else if (int_HWTCnt == 6)
                {
                    int_HWTCnt++;

                    // 读取实验fpga采集到的鼠标左键键值信息
                    str_FpgaReadData0 = ExpFpgaRead(0x98);

                    if (str_FpgaReadData0.Mid(7, 1) == _T("1"))
                    {
                        WriteLogFile(1, _T("硬件自检：\r\n鼠标左键键值测试。。。"));

                        // 发送鼠标中键键值
                        FpgaWrite(0, 0x31, 0x0c);
                        FpgaWrite(0, 0x31, 0x00);
                        FpgaWrite(0, 0x31, 0x00);


                    }
                    else
                    {
                        WriteLogFile(1, _T("硬件自检：\r\n鼠标左键键值测试失败！\r\n退出硬件自检程序！"));
                        OnBnClickedButtonHardwareteststop();

                    }
                }
                else if (int_HWTCnt == 7)
                {
                    int_HWTCnt++;

                    // 读取实验fpga采集到的鼠标中键键值信息
                    str_FpgaReadData0 = ExpFpgaRead(0x98);

                    if (str_FpgaReadData0.Mid(7, 1) == _T("2"))
                    {
                        WriteLogFile(1, _T("硬件自检：\r\n鼠标中键键值测试。。。"));

                        // 发送鼠标右键键值
                        FpgaWrite(0, 0x31, 0x0a);
                        FpgaWrite(0, 0x31, 0x00);
                        FpgaWrite(0, 0x31, 0x00);


                    }
                    else
                    {
                        WriteLogFile(1, _T("硬件自检：\r\n鼠标中键键值测试失败！\r\n退出硬件自检程序！"));
                        OnBnClickedButtonHardwareteststop();

                    }
                }
                else if (int_HWTCnt == 8)
                {
                    int_HWTCnt++;

                    // 读取实验fpga采集到的鼠标右键键值信息
                    str_FpgaReadData0 = ExpFpgaRead(0x98);

                    if (str_FpgaReadData0.Mid(7, 1) == _T("4"))
                    {
                        WriteLogFile(1, _T("硬件自检：\r\n鼠标右键键值测试。。。\r\nPS2接口测试成功！"));

                        if (Idc_Check_HardwareTestAutoEn.GetCheck())
                        {
                            Idc_Combo_HardwareTestSel.SetWindowText(_T("时钟"));
                            int_HWTTimeOutCnt = 0;
                        }
                        else
                        {
                            OnBnClickedButtonHardwareteststop();

                        }


                    }
                    else
                    {
                        WriteLogFile(1, _T("硬件自检：\r\n鼠标中键键值测试失败！\r\n退出硬件自检程序！"));
                        OnBnClickedButtonHardwareteststop();

                    }
                }
            }
			else
			{
                WriteLogFile(1, _T("硬件自检：\r\nPS2测试超时失败！\r\n退出硬件自检程序！"));
                OnBnClickedButtonHardwareteststop();
			
			}
		}
        else if (str_HardwareTestSel == _T("时钟"))
        {
            unsigned __int64 uint64_FpgaReadData = _tcstoui64(ExpFpgaRead(0x40), 0, 16);
            if (uint64_FpgaReadData == 0x1)
            {
                WriteLogFile(1, _T("硬件自检：\r\n1Hz 时钟测试。。。"));

            }
            else
            {
                WriteLogFile(1, _T("硬件自检：\r\n1Hz 时钟测试失败！\r\n退出硬件自检程序！"));
                OnBnClickedButtonHardwareteststop();

            }

            uint64_FpgaReadData = _tcstoui64(ExpFpgaRead(0x41), 0, 16);
            if ((uint64_FpgaReadData > HWT_CLK_1KHZ_OFFSET_N) & (uint64_FpgaReadData < HWT_CLK_1KHZ_OFFSET_P))
            {
                WriteLogFile(1, _T("硬件自检：\r\n1KHz 时钟测试。。。"));

            }
            else
            {
                WriteLogFile(1, _T("硬件自检：\r\n1KHz 时钟测试失败！\r\n退出硬件自检程序！"));
                OnBnClickedButtonHardwareteststop();

            }

            uint64_FpgaReadData = _tcstoui64(ExpFpgaRead(0x42), 0, 16);
            if ((uint64_FpgaReadData > HWT_CLK_750KHZ_OFFSET_N) & (uint64_FpgaReadData < HWT_CLK_750KHZ_OFFSET_P))
            {
                WriteLogFile(1, _T("硬件自检：\r\n750KHz 时钟测试。。。"));

            }
            else
            {
                WriteLogFile(1, _T("硬件自检：\r\n750KHz 时钟测试失败！\r\n退出硬件自检程序！"));
                OnBnClickedButtonHardwareteststop();

            }

            uint64_FpgaReadData = _tcstoui64(ExpFpgaRead(0x43), 0, 16);
            if ((uint64_FpgaReadData > HWT_CLK_12MHZ_OFFSET_N) & (uint64_FpgaReadData < HWT_CLK_12MHZ_OFFSET_P))
            {
                WriteLogFile(1, _T("硬件自检：\r\n12MHz 时钟测试。。。\r\n时钟测试成功！\r\n硬件自检完成，所有硬件测试通过！"));

            }
            else
            {
                WriteLogFile(1, _T("硬件自检：\r\n12MHz 时钟测试失败！\r\n退出硬件自检程序！"));
                OnBnClickedButtonHardwareteststop();

            }

            OnBnClickedButtonHardwareteststop();

        }
		//else if (str_HardwareTestSel == _T("VGA接口"))
		//{
		//
		//}
		//else if (str_HardwareTestSel == _T("Flash"))
		//{
		//	
		//}
		//else if (str_HardwareTestSel == _T("SDRAM"))
		//{
		//	
		//}
	
	
	}
    
	CDialog::OnTimer(nIDEvent);

}



void CUpperComputerDlg::OnBnClickedButtonComopen()
{
	// 打开串口
	CString str_ComPort;

	Idc_Combo_ComSel.GetWindowText(str_ComPort);

    if(cpubsub_MasterCom.m_hCom==INVALID_HANDLE_VALUE)
    {
		if(cpubsub_MasterCom.OpenCom(str_ComPort,COM_PORT_BAUDRATE,COM_PORT_DATABIT,COM_PORT_STOPBIT,COM_PORT_PARITYBIT,COMBUFSIZE,COMBUFSIZE))
        {
			Idc_Button_ComOpen.EnableWindow(FALSE);
			Idc_Button_ComClose.EnableWindow(TRUE);
			Idc_Combo_ComSel.EnableWindow(FALSE);
			// 日志：“主控串口打开成功：”
			// “串口号：COMX”
			WriteLogFile(1,_T("主控串口打开成功："));
			WriteLogFile(0,_T("串口号：")+str_ComPort);
        }
        else
        {
			Idc_Button_ComOpen.EnableWindow(TRUE);
			Idc_Button_ComClose.EnableWindow(FALSE);
			Idc_Combo_ComSel.EnableWindow(TRUE);
			// 日志：“串口打开失败。”
			WriteLogFile(1,_T("主控串口打开失败。"));

        }
    }

	//// 打开ft232h
	//ftStatus = FT_OpenEx("FT2W5GYH", FT_OPEN_BY_SERIAL_NUMBER, &ftHandle);

	//if (!FT_SUCCESS(ftStatus))
	//{
	//	//WriteLogFile(1,_T("串口打开失败。。。"));
	//}
	//else
	//{
	//	ftStatus = FT_SetBaudRate(ftHandle, COM_PORT_BAUDRATE);
	//	if (!FT_SUCCESS(ftStatus))
	//	{
	//		//WriteLogFile(1,_T("串口波特率设置失败。。。"));
	//		return;
	//	}

	//	ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1,FT_PARITY_NONE);
	//	if (!FT_SUCCESS(ftStatus))
	//	{
	//		//WriteLogFile(1,_T("串口参数设置失败。。。"));
	//		return;
	//	}

	//	ftStatus = FT_SetUSBParameters(ftHandle, 64*1024, 64*1024); 
	//	if (!FT_SUCCESS(ftStatus))
	//	{
	//		//WriteLogFile(1,_T("串口缓存设置失败。。。"));
	//		return;
	//	}
	//	ftStatus = FT_SetLatencyTimer(ftHandle, 2); 
	//	if (!FT_SUCCESS(ftStatus))
	//	{
	//		//WriteLogFile(1,_T("串口接收超时设置失败。。。"));
	//		return;
	//	}

	//	ftStatus = FT_SetTimeouts(ftHandle, 10000, 10000); 
	//	if (!FT_SUCCESS(ftStatus))
	//	{
	//		//WriteLogFile(1,_T("串口读写超时设置失败。。。"));
	//		return;
	//	}

	//	 // 清除输入缓存
	//	 FT_Purge(ftHandle, FT_PURGE_RX);
	//	 // 清除输出缓存
	//	 FT_Purge(ftHandle, FT_PURGE_TX);

	//	Idc_Button_ComOpen.EnableWindow(FALSE);
	//	Idc_Button_ComClose.EnableWindow(TRUE);





	
	//}


}


void CUpperComputerDlg::OnBnClickedButtonComclose()
{
	//  关闭串口
    if(cpubsub_MasterCom.CloseCom())
    {
		Idc_Button_ComOpen.EnableWindow(TRUE);
		Idc_Button_ComClose.EnableWindow(FALSE);
	    Idc_Combo_ComSel.EnableWindow(TRUE);
		// 日志：“主控串口关闭成功：”
		WriteLogFile(1,_T("主控串口关闭成功！"));
    }
    else
    {
		// 日志：“主控串口关闭成功：”
		WriteLogFile(1,_T("主控串口关闭失败！"));
    }

	//ftStatus = FT_Close(ftHandle); 
	//if (!FT_SUCCESS(ftStatus))
	//{
	//	//WriteLogFile(1,_T("串口关闭失败。。。"));
	//}
	//else
	//{
	//	Idc_Button_ComOpen.EnableWindow(TRUE);
	//	Idc_Button_ComClose.EnableWindow(FALSE);
	//    Idc_Combo_ComSel.EnableWindow(TRUE);
	//}


}



void CUpperComputerDlg::OnBnClickedButtonFpgaregwrite()
{
	CString str_FpgaRegAddr;
	CString str_FpgaRegData;

    // 获取地址和数据
	Idc_Edit_FpgaRegAddr.GetWindowText(str_FpgaRegAddr);
	Idc_Edit_FpgaRegData.GetWindowText(str_FpgaRegData);
	
	// 主控fpga 寄存器写入
    if (Idc_Radio_MasterFpgaSelect.GetCheck())
    {
        FpgaWrite(0, _tcstoui64(str_FpgaRegAddr,0,16), _tcstoui64(str_FpgaRegData,0,16));
    
    }
	// 实验fpga 寄存器写入
    else if (Idc_Radio_ExpFpgaSelect.GetCheck())
    {
        FpgaWrite(0, 0x60, 0x0);
		ExpComOpen(1000000, 8, 0, 0);
        ExpFpgaWrite(0, _tcstoui64(str_FpgaRegAddr,0,16), _tcstoui64(str_FpgaRegData,0,16));
    
    }
    // spi-flash 数据烧写
    else if (Idc_Radio_SpiFlashSelect.GetCheck())
    {
        BYTE byte_SpiFlashPageProgramBuf[1] = {0};
        // 转换为char，数据只有1byte
        byte_SpiFlashPageProgramBuf[0] = _tcstoui64(str_FpgaRegData,0,16);
        SpiFlashPageProgram(_tcstoui64(str_FpgaRegAddr,0,16), byte_SpiFlashPageProgramBuf, 1);
    
    }
    // spi-flash 整片擦除
    else if (Idc_Radio_SpiFlashChipEraseSelect.GetCheck())
    {
        SpiFlashChipErase();
    
    }
    // jtag 指令寄存器
    else if (Idc_Radio_JtagIRSelect.GetCheck())
    {

		// 复位tap状态机
		JtagStateReset();
		JtagStateIdle();
		JtagSIR((0x00000000ffffffff & _tcstoui64(str_FpgaRegAddr,0,16)),(0x00000000ffffffff & _tcstoui64(str_FpgaRegData,0,16)));






    }
    // jtag 数据寄存器
    else if (Idc_Radio_JtagDRSelect.GetCheck())
    {
		JtagStateReset();
		JtagStateIdle();
		// tap状态机从“RUN-TEST/IDLE” 状态进入“SHIFT-DR”状态，TMS输出“001”
		FpgaWrite(0, 0x50, 0x3);
		FpgaWrite(0, 0x51, 0x0000000100000000);

		// 写入数据,TMS保持输出“0”
		FpgaWrite(0, 0x50, (0x00000000ffffffff & _tcstoui64(str_FpgaRegAddr,0,16)));
		FpgaWrite(0, 0x51, (0x00000000ffffffff & _tcstoui64(str_FpgaRegData,0,16)));


    }
    // ft232h 测试
    else if (Idc_Radio_FT232HSelect.GetCheck())
    {
		WriteLogFile(1,_T("before FpgaWrite。。。"));

        FpgaWrite(0, _tcstoui64(str_FpgaRegAddr,0,16), _tcstoui64(str_FpgaRegData,0,16));
		WriteLogFile(1,_T("after FpgaWrite。。。"));





	}

    

}


void CUpperComputerDlg::OnBnClickedButtonFpgaregread()
{
	// fpga 寄存器读取
	CString str_FpgaRegAddr;
	CString str_FpgaReadData;

    // 获取地址
	Idc_Edit_FpgaRegAddr.GetWindowText(str_FpgaRegAddr);

	// 主控fpga 寄存器读取
    if (Idc_Radio_MasterFpgaSelect.GetCheck())
    {
	    str_FpgaReadData = FpgaRead(_tcstoui64(str_FpgaRegAddr,0,16));
	    Idc_Edit_FpgaRegData.SetWindowText(str_FpgaReadData);

    
    }
	// 实验fpga 寄存器读取
    else if (Idc_Radio_ExpFpgaSelect.GetCheck())
    {
        FpgaWrite(0, 0x60, 0x0);
		ExpComOpen(1000000, 8, 0, 0);
	    str_FpgaReadData = ExpFpgaRead(_tcstoui64(str_FpgaRegAddr,0,16));
	    Idc_Edit_FpgaRegData.SetWindowText(str_FpgaReadData);

    
    }
    // spi-flash 数据读取
    else if (Idc_Radio_SpiFlashSelect.GetCheck())
    {
        unsigned __int64 uint64_SpiFlashReadAddr = _tcstoui64(str_FpgaRegAddr,0,16);


		// 清除spi-flash rx buffer
		FpgaWrite(0,0x40,0x3);
        // 拉高spi-flash的片选信号，终止当前操作
	    FpgaWrite(0,0x40,0x1);
        // 拉低spi-flash的片选信号
	    FpgaWrite(0,0x40,0x0);
        // 写入 Read Data (03h) 指令
	    FpgaWrite(0,0x41,0x03);
        // 写入起始地址的[23:16]
	    FpgaWrite(0,0x41,((uint64_SpiFlashReadAddr >> 16) & 0x00000000000000ff));
        // 写入起始地址的[15:8]
	    FpgaWrite(0,0x41,((uint64_SpiFlashReadAddr >> 8) & 0x00000000000000ff));
        // 写入起始地址的[7:0]
	    FpgaWrite(0,0x41,(uint64_SpiFlashReadAddr & 0x00000000000000ff));


        // 读取spi-flash数据
	    FpgaWrite(0,0x41,0x100);
        // 拉高spi-flash的片选信号
	    FpgaWrite(0,0x40,0x1);
        // 从fpga读取数据
	    str_FpgaReadData = FpgaRead(0x42);
        // 截取spi-flash数据 并显示
	    Idc_Edit_FpgaRegData.SetWindowText(str_FpgaReadData.Mid(14, 2));


    }
    // spi-flash 状态寄存器读取
    else if (Idc_Radio_SpiFlashStatusSelect.GetCheck())
    {
        // 从spi-flash 状态寄存器读取数据并显示
	    Idc_Edit_FpgaRegData.SetWindowText(SpiFlashStatusRead());



    }
    // jtag 回读数据
    else if (Idc_Radio_JtagIRSelect.GetCheck() | Idc_Radio_JtagDRSelect.GetCheck())
    {
	    str_FpgaReadData = FpgaRead(0x52);
	    Idc_Edit_FpgaRegData.SetWindowText(str_FpgaReadData);


    }
    // ft232h 测试
    else if (Idc_Radio_FT232HSelect.GetCheck())
    {
		WriteLogFile(1,_T("before FpgaRead。。。"));

		str_FpgaReadData = FpgaRead(_tcstoui64(str_FpgaRegAddr,0,16));
	    Idc_Edit_FpgaRegData.SetWindowText(str_FpgaReadData);

		WriteLogFile(1,_T("after FpgaRead。。。"));




	}



}



// 主控FPGA升级
// 直接将bin文件烧写到spi flash
void CUpperComputerDlg::OnBnClickedButtonFpgaupdatefileselect()
{



	//创建打开配置文件对话框
	//CFileDialog::CFileDialog( BOOL bOpenFileDialog, LPCTSTR lpszDefExt = NULL, LPCTSTR lpszFileName = NULL, DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, LPCTSTR lpszFilter = NULL, CWnd* pParentWnd = NULL );参数意义如下： 
	//•bOpenFileDialog 为TRUE则显示打开对话框，为FALSE则显示保存对话文件对话框。 
	//•lpszDefExt 指定默认的文件扩展名。 
	//•lpszFileName 指定默认的文件名。 
	//•dwFlags 指明一些特定风格。 
	//•lpszFilter 是最重要的一个参数，它指明可供选择的文件类型和相应的扩展名。参数格式如： 
	//"Chart Files (*.xlc)|*.xlc|Worksheet Files (*.xls)|*.xls|Data Files (*.xlc;*.xls)|*.xlc; *.xls|All Files (*.*)|*.*||";文件类型说明和扩展名间用 | 分隔，同种类型文件的扩展名间可以用 ; 分割，每种文件类型间用 | 分隔，末尾用 || 指明。 
	//•pParentWnd 为父窗口指针。 
	
	CFileDialog cfdlg_FpgaUpdateFileSelect( TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("Data Files (*.bit)|*.bit||"),NULL ); 

	if (IDOK ==cfdlg_FpgaUpdateFileSelect.DoModal())
	{
		//取得文件全路径且显示到编辑框
		Idc_Edit_FpgaUpdateFilePath.SetWindowText(cfdlg_FpgaUpdateFileSelect.GetPathName());

	}
    else
    {
		AfxMessageBox(_T("文件打开失败！")); 
    }
}


void CUpperComputerDlg::OnBnClickedButtonFpgaupdatestart()
{
    int int_SpiFlashStatusData;
	CString str_FpgaUpdateFilePath;
	CFile f_FpgaUpdateFile;

	// 选择烧写文件路径
    Idc_Edit_FpgaUpdateFilePath.GetWindowText(str_FpgaUpdateFilePath);
    // 判断文件是否有效
	if(!PathFileExists(str_FpgaUpdateFilePath))
	{
		WriteLogFile(1,_T("FPGA 升级："));
		WriteLogFile(0,_T("烧写文件不存在！"));
		return;
	}

	// 设置fpga加载模式为本地模式
	int_FpgaUpdateMode = FPGA_UPDATE_MODE_LOCAL;

	// spi-flash更新模式，更新主控fpga
    if (Idc_Radio_FPGAUpdateSpiFlashSelect.GetCheck())
    {
		// 先擦除spi-flash
		SpiFlashChipErase();


		// 读取spi-flash状态寄存器
		int_SpiFlashStatusData = _tcstoui64(SpiFlashStatusRead(),0,16);

		// 如果busy位有效，则擦除指令执行成功
		if((int_SpiFlashStatusData & 0x0001) == 0x0001)
		{
			// 浏览文件按钮不可用
			Idc_Button_FPGAUpdateFileSelect.EnableWindow(FALSE);
			// 启动按钮不可用
			Idc_Button_FpgaUpdateStart.EnableWindow(FALSE);

			WriteLogFile(1,_T("FPGA 升级："));
			WriteLogFile(0,_T("SPI-Flash 正在擦除。。。"));

            // 启动烧写线程
			FpgaUpdateThreadStart();

		}
		// 如果busy位无效，则擦除指令执行失败
		else
		{
			WriteLogFile(1,_T("FPGA 升级："));
			WriteLogFile(0,_T("SPI-Flash 擦除失败！"));
        
		}
	}
	// jtag更新模式，更新实验fpga
    else if (Idc_Radio_FPGAUpdateJtagSelect.GetCheck())
    {
		// 浏览文件按钮不可用
		Idc_Button_FPGAUpdateFileSelect.EnableWindow(FALSE);
		// 启动按钮不可用
		Idc_Button_FpgaUpdateStart.EnableWindow(FALSE);
		
        // 启动烧写线程
		FpgaUpdateThreadStart();


	}


}








void CUpperComputerDlg::OnBnClickedButtonHardwareteststart()
{

	// 打印log文件信息
	Idc_Check_LogDisplay.SetCheck(1);
	
	// 先打开主控串口
	if (!AutoOpenMasterCom())
	{
		return;
	}

	// 启动
	// 打开实验串口
	// 清楚缓存
	FpgaWrite(0, 0x60, 0x0);
	// 设置串口参数
	ExpComOpen(EXPCOM_PORT_BAUDRATE, EXPCOM_PORT_DATABIT, EXPCOM_PORT_PARITYBIT, EXPCOM_PORT_STOPBIT);

	if (Idc_Check_HardwareTestAutoEn.GetCheck()) 
	{
		Idc_Combo_HardwareTestSel.SetWindowText(_T("JTAG接口"));
	}

	// 关闭相关冲突定时器
	if (KillTimer(TIMERID_DATA_SAMPLE))
	{
		bool_TimeridDataSampleStatus = 1;
	}
	else
	{
		bool_TimeridDataSampleStatus = 0;
	}
	if (KillTimer(TIMERID_TEST_DATA_SAMPLE))
	{
		bool_TimeridTestDataSampleStatus = 1;
	}
	else
	{
		bool_TimeridTestDataSampleStatus = 0;
	}
	
    // 启动硬件自检定时器
	SetTimer( TIMERID_HARDWARE_TEST, TIMERID_HARDWARE_TEST_TIME, NULL );
	int_HWTTimeOutCnt = 0;
	
	// 停止按钮可用
	Idc_Button_HardwareTestStop.EnableWindow(TRUE);
	// 开始按钮不可用
	Idc_Button_HardwareTestStart.EnableWindow(FALSE);




}


void CUpperComputerDlg::OnBnClickedButtonHardwareteststop()
{
    // 关闭硬件自检定时器
    KillTimer(TIMERID_HARDWARE_TEST);
	// 停止按钮不可用
	Idc_Button_HardwareTestStop.EnableWindow(FALSE);
	// 开始按钮可用
	Idc_Button_HardwareTestStart.EnableWindow(TRUE);

	// 重新开启之前停止的相关冲突定时器
	if (bool_TimeridDataSampleStatus)
	{
		SetTimer( TIMERID_DATA_SAMPLE, TIMERID_DATA_SAMPLE_TIME, NULL );
	}
	if (bool_TimeridTestDataSampleStatus)
	{
		SetTimer( TIMERID_TEST_DATA_SAMPLE, TIMERID_TEST_DATA_SAMPLE_TIME, NULL );
	}

}


void CUpperComputerDlg::OnBnClickedButtonFpgaupdatestop()
{
	// TODO: 在此添加控件通知处理程序代码
}
