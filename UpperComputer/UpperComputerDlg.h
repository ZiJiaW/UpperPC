
// UpperComputerDlg.h : ͷ�ļ�
//



#pragma once
#include "StatusSocket.h"
#include "resource.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "PubSub.h"

#include "ftd2xx.h"
#include "types.h"
#include "WebsocketEndpoint.h"

#pragma comment(lib, "ftd2xx.lib")


// CUpperComputerDlg �Ի���
class CUpperComputerDlg : public CDialogEx
{
// ����
public:
	CUpperComputerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	// �Ի�������
	enum { IDD = IDD_UPPERCOMPUTER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
    afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

    // ��������Ϣ
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonDisconnect();


	CString str_ServerIPAddress;
	CString str_ServerStatusPort;
	CString str_UpperComputerID;

	unsigned int uint_ServerStatusPort;
    CString str_LogFileWrite;


    // ״̬�˿�CSocket
	StatusSocket* m_StatusSocket;

    // websocket�����ն�
    WebsocketEndpoint* wsEndpoint;

	bool m_ServerConnectStatus;
	bool m_ServerRegisterStatus;

	CString str_WorkStatus;
    CString str_WorkMode;

	afx_msg void OnBnClickedButtonSenddata();
	CComboBox Idc_Combo_ComSel;

	// ������ָ��
	unsigned int uint_ServerMsg_Cmd;
	CString str_ServerMsg_DataPort;
	unsigned int uint_ServerMsg_FileLength;
	unsigned int uint_ServerMsg_FileHashCode;
	CString str_ServerMsg_FileMatchResult;
	CString str_ServerMsg_Data;
	CString str_ServerMsg_Test;
	CString str_ServerMsg_Key;
	CString str_ServerMsg_Type;
	CString str_ServerMsg_State;
	CString str_ServerMsg_ExpComOperation;
	unsigned int uint_ServerMsg_ExpComBitRate;
	unsigned int uint_ServerMsg_ExpComDataBits;
	unsigned int uint_ServerMsg_ExpComParityCheck;
	unsigned int uint_ServerMsg_ExpComStopBit;
	unsigned int uint_ServerMsg_ExpComSendDataLength;
	CString str_ServerMsg_ExpComSendData;
	unsigned int uint_ServerMsg_Ps2MouseSendDataLength;
	CString str_ServerMsg_Ps2MouseSendData;
	unsigned int uint_ServerMsg_Ps2KeyboardSendDataLength;
	CString str_ServerMsg_Ps2KeyboardSendData;




    void SendCmd(CString str_SendStr);


    // ��־�ļ�
    void WriteLogFile(int int_NewLog, CString str_Log );
    CFile f_LogFile;
	void LogDisplay(int int_NewLog, CString str_Log );

    // FPGA ����
    CString FpgaRead(unsigned __int64 uint64_ReadAddr);
    void FpgaWrite(unsigned int uint_WriteCmd, unsigned __int64 uint64_WriteAddr, unsigned __int64 uint64_WriteData);
	void FpgaBlockWrite(unsigned int uint_WriteAddr, BYTE *byte_FpgaWriteBuf, unsigned int uint_UnitDataLength, unsigned int uint_TotalDataLength);
	unsigned int FpgaBlockRead(unsigned int uint_ReadAddr, BYTE *byte_FpgaReadBuf, unsigned int uint_UnitDataLength, unsigned int uint_TotalDataLength);
    CString ExpFpgaRead(unsigned __int64 uint64_ReadAddr);
    void ExpFpgaWrite(unsigned int uint_WriteCmd, unsigned __int64 uint64_WriteAddr, unsigned __int64 uint64_WriteData);

    // spi-flash ����
    void SpiFlashChipErase();
    CString SpiFlashStatusRead();
    void SpiFlashPageProgram(unsigned __int64 uint64_StartAddr, BYTE *lpBuf, unsigned int uint_DataLength );

	// jtag ���
	void CUpperComputerDlg::JtagStateReset();
	void CUpperComputerDlg::JtagStateIdle();
	void CUpperComputerDlg::JtagSIR(unsigned __int64 uint64_IRLengthInBit,unsigned __int64 uint64_IR);
	void CUpperComputerDlg::JtagSDR(unsigned __int64 uint64_DRLengthInBit,unsigned __int64 uint64_DR);

	// FPGA����
	int int_FpgaUpdateStatus;
	int int_FpgaUpdateMode;
	void FpgaUpdateThreadStart();


    // ����
   	CPubSub cpubsub_MasterCom;
	BOOL ExpComOpen(unsigned int uint_ExpComBautrate, BYTE ExpComDataBits, BYTE ExpComParityBit, BYTE ExpComStopBit);
	BOOL ExpComClose();
	void ExpComWrite(BYTE *byte_ExpComWriteBuffer,unsigned int uint_ExpComWriteLength);
	unsigned int ExpComRead(BYTE *byte_ExpComReadBuffer,unsigned int uint_ExpComReadLength);
    BOOL AutoOpenMasterCom();

    // ���ݲɼ�
    CString str_FpgaSampleData0;
    CString str_FpgaSampleData1;
    CString str_FpgaSetData0;
    CString str_FpgaSetData1;


	// Ӳ���Լ�
	CButton Idc_Button_HardwareTestStart;
	CButton Idc_Button_HardwareTestStop;
	CButton Idc_Check_HardwareTestAutoEn;
	CComboBox Idc_Combo_HardwareTestSel;
	int int_HWTTimeOutCnt;
	int int_HWTCnt;
	unsigned __int64 uint64_HWTPattern;
	BOOL bool_TimeridDataSampleStatus;
	BOOL bool_TimeridTestDataSampleStatus;
	BOOL bool_TimeridExpComRxStatus;

	CButton Idc_Button_ServerConnect;
	CButton Idc_Button_ServerDisconnect;
	CEdit Idc_Edit_ServerStatusPort;
    CButton Idc_Button_ComClose;
    CButton Idc_Button_ComOpen;
    afx_msg void OnBnClickedButtonComopen();
    afx_msg void OnBnClickedButtonComclose();
    CIPAddressCtrl Idc_IPaddress_ServerIPAddr;
    CEdit Idc_Edit_FpgaRegAddr;
    CEdit Idc_Edit_FpgaRegData;
    CButton Idc_Button_FpgaRegWrite;
    CButton Idc_Button_FpgaRegRead;
    afx_msg void OnBnClickedButtonFpgaregwrite();
    afx_msg void OnBnClickedButtonFpgaregread();
    CEdit Idc_Edit_LogDisplay;
    CButton Idc_Check_LogDisplay;
    afx_msg void OnBnClickedButtonFpgaupdatefileselect();
    afx_msg void OnBnClickedButtonFpgaupdatestart();
    CEdit Idc_Edit_FpgaUpdateFilePath;
    CButton Idc_Button_FPGAUpdateFileSelect;
    CButton Idc_Button_FpgaUpdateStart;
    CProgressCtrl Idc_Progress_FpgaUpdateProgress;
    CButton Idc_Radio_MasterFpgaSelect;
    CButton Idc_Radio_ExpFpgaSelect;
    CButton Idc_Radio_SpiFlashSelect;
    CButton Idc_Radio_SpiFlashStatusSelect;
    CButton Idc_Radio_SpiFlashChipEraseSelect;
    CButton Idc_Radio_JtagIRSelect;
    CButton Idc_Radio_JtagDRSelect;
    CButton Idc_Radio_FPGAUpdateJtagSelect;
    CButton Idc_Check_FPGAUpdateJtagTestEn;
    CButton Idc_Radio_FPGAUpdateSpiFlashSelect;
    CButton Idc_Radio_FT232HSelect;





	afx_msg void OnBnClickedButtonHardwareteststart();
	afx_msg void OnBnClickedButtonHardwareteststop();
	afx_msg void OnBnClickedButtonFpgaupdatestop();
};
