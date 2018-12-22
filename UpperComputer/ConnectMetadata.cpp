#include "stdafx.h"
#include "ConnectMetadata.h"
#include "UpperComputer.h"
#include "UpperComputerDlg.h"
#include "resource.h"
#include "define.h"

using std::string;


ConnectMetadata::ConnectMetadata(websocketpp::connection_hdl hdl, string uri):
    m_hdl(hdl), m_uri(uri), m_status("Connecting"), m_server("None"), m_errorReason(""), m_fileRcvEnable(false), m_fileRcvLengthSum(0), m_over50(false){}

ConnectMetadata::~ConnectMetadata(){}

void ConnectMetadata::onOpen(client* c, websocketpp::connection_hdl hdl)
{
    auto pDlg = (CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd);
    m_status = "Open";
    client::connection_ptr con = c->get_con_from_hdl(hdl);
    m_server = con->get_response_header("Server");
    pDlg->WriteLogFile(1, CString(_T("���ӽ����ɹ���")) + CSTR(m_uri));
    //pDlg->wsEndpoint->send(LPCSTR(CString("hello")));
    // ������,���Ӱ�ť��Ϊ������
    pDlg->Idc_Button_ServerConnect.SetWindowText(_T("������"));
    pDlg->Idc_Button_ServerConnect.EnableWindow(FALSE);
    // �Ͽ����ӿ���
    pDlg->Idc_Button_ServerDisconnect.SetWindowText(_T("�Ͽ�"));
    pDlg->Idc_Button_ServerDisconnect.EnableWindow(TRUE);
    // ����״̬��1
    pDlg->m_ServerConnectStatus = 1;
    // ˢ��������ʱ���¼���
    pDlg->last_check_time = CTime::GetCurrentTime().GetTime();
    // ���ӳɹ�����ע������
    pDlg->wsEndpoint->send(std::string("<Register><Id>") + LPCSTR(pDlg->str_UpperComputerID) + "</Id></Register>");
}

void ConnectMetadata::onFail(client* c, websocketpp::connection_hdl hdl)
{
    auto pDlg = (CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd);
    m_status = "Failed";
    client::connection_ptr con = c->get_con_from_hdl(hdl);
    m_server = con->get_response_header("Server");
    m_errorReason = con->get_ec().message();
    pDlg->m_ServerConnectStatus = 0;
    pDlg->m_ServerRegisterStatus = 0;
    pDlg->WriteLogFile(1, CString(_T("���ӽ���ʧ�ܣ�")) + CSTR(m_uri));
}
void ConnectMetadata::onClose(client* c, websocketpp::connection_hdl hdl)
{
    auto pDlg = (CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd);
    m_status = "Closed";
    client::connection_ptr con = c->get_con_from_hdl(hdl);
    // ��¼�ر�ԭ��
    std::stringstream s;
    s << "close code: " << con->get_remote_close_code() << " ("
        << websocketpp::close::status::get_string(con->get_remote_close_code())
        << "), close reason: " << con->get_remote_close_reason();
    m_errorReason = s.str();
    // �ر���ض�ʱ��
    pDlg->KillTimer(TIMERID_DATA_SAMPLE);
    pDlg->KillTimer(TIMERID_TEST_DATA_SAMPLE);
    pDlg->KillTimer(TIMERID_FILEREV);
    pDlg->KillTimer(TIMERID_EXPCOMRX);
    // ���¹���ģʽΪʵ��ģʽ
    pDlg->str_WorkMode = _T("ExperimentMode");
    // ������λ��״̬
    pDlg->str_WorkStatus = _T("Ready");
    // ���·���������״ָ̬ʾ
    pDlg->m_ServerConnectStatus = 0;
    // ���·�����ע��״ָ̬ʾ
    pDlg->m_ServerRegisterStatus = 0;
    // ��ʼ������д������fpga
    pDlg->FpgaWrite(0, 0x10, 0xffffffffffffffff);
    //�ر��ļ�
    m_loadFile.Abort();
    //�ѶϿ�,���Ӱ�ť��Ϊ����
    pDlg->Idc_Button_ServerConnect.SetWindowText(_T("����"));
    pDlg->Idc_Button_ServerConnect.EnableWindow(TRUE);
    //�Ͽ����Ӳ�����
    pDlg->Idc_Button_ServerDisconnect.SetWindowText(_T("�ѶϿ�"));
    pDlg->Idc_Button_ServerDisconnect.EnableWindow(FALSE);
    // ��־�������������ӶϿ�����
    pDlg->WriteLogFile(1, CString(_T("���ӹرգ��ر�ԭ��")) + CSTR(m_errorReason));
}

void ConnectMetadata::onMessage(websocketpp::connection_hdl hdl, client::message_ptr msg)
{
    auto pDlg = (CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd);
    auto serverMessage = msg->get_payload();
    bool isBinary = false;
    if (msg->get_opcode() == websocketpp::frame::opcode::text) {
        //pDlg->WriteLogFile(1, CString(_T("�յ�text��Ϣ��")) + CSTR(serverMessage));
    }
    else {
        isBinary = true; //��������Ϣ
        //pDlg->WriteLogFile(1, CString(_T("�յ�binary��Ϣ��")) + CSTR(websocketpp::utility::to_hex(serverMessage)));
    }
    if (isBinary && m_fileRcvEnable)// �����ļ���ֻ�����������Ϣ
    {
        size_t lenOfSlice = serverMessage.length();
        m_fileRcvLengthSum += lenOfSlice;
        //pDlg->WriteLogFile(1, _T("�����ļ�Ƭ�γ��ȣ�") + lenOfSlice);
        if (!m_over50 && double(m_fileRcvLengthSum) / pDlg->uint_ServerMsg_FileLength > 0.5)
        {
            pDlg->WriteLogFile(0, _T("�ѽ���50%......"));
            m_over50 = true;
        }
        m_loadFile.Write(serverMessage.c_str(), lenOfSlice);
        if (m_fileRcvLengthSum >= pDlg->uint_ServerMsg_FileLength)// �ܳ��ȴﵽ�����ļ����ȣ�ֹͣ���ղ�����
        {
            // �ر��ļ����ճ�ʱ��ʱ��
            pDlg->KillTimer(TIMERID_FILEREV);
            m_loadFile.Close();
            if (m_fileRcvLengthSum == pDlg->uint_ServerMsg_FileLength)// ���ȶ�Ӧ���
            {
                // ���ͽ���ȷ��ָ��:<Receive><Result>��</Result></Receive>
                pDlg->wsEndpoint->send("<Receive><Result>Successful</Result></Receive>");
                // ��־��"�ļ����ճɹ���"
                pDlg->WriteLogFile(0, _T("�ļ����ճɹ���"));
                // ����fpga����ģʽΪ����ģʽ
                pDlg->int_FpgaUpdateMode = FPGA_UPDATE_MODE_ONLINE;
                // ѡ��jtag����ģʽ
                pDlg->Idc_Check_FPGAUpdateAutoTestEn.SetCheck(0);
                pDlg->Idc_Radio_FPGAUpdateJtagSelect.SetCheck(1);
                pDlg->Idc_Radio_FPGAUpdateSpiFlashSelect.SetCheck(0);
                // ������д�߳�
                pDlg->FpgaUpdateThreadStart();
            }
            else //���Ȳ��ԣ�����ʧ��
            {
                pDlg->wsEndpoint->send("<Receive><Result>Failed</Result></Receive>");
                pDlg->WriteLogFile(0, _T("�ļ�����ʧ�ܣ��ļ�������"));
            }
            m_fileRcvEnable = false;// �ļ�����ʹ�ܹر�
        }
    }
    else// ���ڴ����ļ�
    {
        if (parseCmd(serverMessage))
        {
            //if(pDlg->uint_ServerMsg_Cmd != SERVERCMD_ASKSTATE)
                pDlg->WriteLogFile(1, CString(_T("�յ�text��Ϣ��")) + CSTR(serverMessage));
            switch (pDlg->uint_ServerMsg_Cmd)
            {
            case SERVERCMD_RECORD:
            {
                pDlg->WriteLogFile(1, _T("������ע��ɹ�!"));
                pDlg->m_ServerRegisterStatus = 1;
                break;
            }
            case SERVERCMD_ASKSTATE:// ����Ӧ��
            {
                //pDlg->WriteLogFile(1, _T("�յ���������ѯ��λ��״ָ̬��!"));
                CString toSend = _T("<Client><key>") + pDlg->str_ServerMsg_Key + pDlg->str_UpperComputerID + 
                    _T("</key><type>ReplyToServerWithState</type><state>") + pDlg->str_WorkStatus + _T("</state></Client>");
                //pDlg->WriteLogFile(0, _T("������λ��״ָ̬�"));
                pDlg->wsEndpoint->send(LPCSTR(toSend), false);
                pDlg->last_check_time = CTime::GetCurrentTime().GetTime();
                break;
            }
            case SERVERCMD_LOAD:
            {
                if (m_fileRcvEnable) 
                { 
                    pDlg->WriteLogFile(1, _T("���ڽ����ļ����������µ��ļ���"));
                    break; 
                }

                if (pDlg->fpga_is_loading)
                {
                    pDlg->WriteLogFile(1, _T("���ڼ��أ��������µ��ļ���"));
                    break;
                }
                pDlg->WriteLogFile(1, _T("�յ���¼ָ�"));

                // ������λ��״̬
                pDlg->str_WorkStatus = _T("Working");
                // �ر���ض�ʱ��
                pDlg->KillTimer(TIMERID_DATA_SAMPLE);
                // ��ʼ���ռ����ļ�
                // �½������ļ�·��
                if (!PathFileExists(_T("program")))
                {
                    CreateDirectory(_T("program"), NULL);
                }
                // ������м����ļ�����ɾ��
                if (PathFileExists(_T("program\\bitfile.bit")))
                {
                    m_loadFile.Abort();
                    CFile::Remove(_T("program\\bitfile.bit"));
                }
                // �½������ļ�������
                CFileException fileException;
                if (!m_loadFile.Open(_T("program\\bitfile.bit"), CFile::modeCreate | CFile::modeReadWrite, &fileException))
                {
                    pDlg->WriteLogFile(1, _T("�ļ�����ʧ�ܡ�")+fileException.m_cause);
                }
                else
                {
                    // ��־�����ļ������ɹ�����
                    pDlg->WriteLogFile(1, _T("�ļ������ɹ���"));
                    // �����ļ����ճ�ʱ��ʱ��
                    pDlg->SetTimer(TIMERID_FILEREV, TIMERID_FILEREV_TIME, NULL);
                    // ���ճ�������
                    m_fileRcvLengthSum = 0;
                    // �ļ�����ʹ����Ч
                    m_fileRcvEnable = true;
                    m_over50 = false;
                    // ��Ӧָ��
                    pDlg->wsEndpoint->send("<File></File>");
                    pDlg->WriteLogFile(0, _T("��ʼ�����ļ�......"));
                }
                break;
            }
            case SERVERCMD_DATA:
            {
                // ����д������fpga
                pDlg->FpgaWrite(0, 0x10, _tcstoui64(pDlg->str_ServerMsg_Data.Mid(26, 4), 0, 16));
                pDlg->FpgaWrite(0, 0x12, _tcstoui64(pDlg->str_ServerMsg_Data.Mid(30, 16), 0, 16));
                break;
            }
            case SERVERCMD_STARTTEST:
            {
                // ���¹���ģʽΪ�Զ�����ģʽ
                pDlg->str_WorkMode = _T("TestMode");
                // ���������Զ����Է���ָ��
                pDlg->WriteLogFile(1, _T("�յ������Զ�����ָ�"));
                pDlg->WriteLogFile(0, _T("���������Զ����Է���ָ�"));
                pDlg->wsEndpoint->send("<StartTest></StartTest>");
                
                break;
            }
            case SERVERCMD_ENDTEST:
            {
                pDlg->WriteLogFile(1, _T("�յ�ֹͣ�Զ�����ָ�"));
                // ����ֹͣ�Զ����Է���ָ��
                pDlg->WriteLogFile(0, _T("����ֹͣ�Զ����Է���ָ�"));
                pDlg->wsEndpoint->send("<EndTest></EndTest>");
                // ���¹���ģʽΪʵ��ģʽ
                pDlg->str_WorkMode = _T("ExperimentMode");
                break;
            }
            case SERVERCMD_TEST:
            {
                // ����д������fpga
                pDlg->FpgaWrite(0, 0x10, _tcstoui64(pDlg->str_ServerMsg_Test.Mid(22, 12), 0, 16));
                // �����Զ��������ݲɼ���ʱ��
                pDlg->SetTimer(TIMERID_TEST_DATA_SAMPLE, TIMERID_TEST_DATA_SAMPLE_TIME, NULL);
                break;
            }
            case SERVERCMD_READY:
            {
                if (pDlg->str_WorkStatus == _T("Working"))
                {
                    // ������æָ��
                    pDlg->WriteLogFile(1, _T("�յ�����ָ�"));
                    pDlg->WriteLogFile(0, _T("������æָ�"));
                    pDlg->wsEndpoint->send("<Answer><State>Busy</State></Answer>");
                }
                else
                {
                    // ����׼������ȷ��ָ��
                    pDlg->WriteLogFile(1, _T("�յ�����ָ�"));
                    pDlg->WriteLogFile(0, _T("����׼������ȷ��ָ�"));
                    pDlg->wsEndpoint->send("<Answer><State>Already</State></Answer>");
                }
                break;
            }
            case SERVERCMD_BREAK:
            {
                // �ر���ض�ʱ��
                pDlg->KillTimer(TIMERID_DATA_SAMPLE);
                pDlg->KillTimer(TIMERID_TEST_DATA_SAMPLE);
                pDlg->KillTimer(TIMERID_FILEREV);
                // ���¹���ģʽΪʵ��ģʽ
                pDlg->str_WorkMode = _T("ExperimentMode");
                // ������λ��״̬
                pDlg->str_WorkStatus = _T("Ready");
                // ��ʼ������д������fpga
                pDlg->FpgaWrite(0, 0x10, 0xffffffffffffffff);
                // ��־
                pDlg->WriteLogFile(1, _T("�յ��Ͽ�ָ�"));
                pDlg->WriteLogFile(0, _T("���ͶϿ�ȷ��ָ�"));
                // ���ͶϿ�ȷ��ָ��
                pDlg->wsEndpoint->send("<Broken></Broken>");
                break;
            }
            //// ����VGAͼ��ɼ�
            //case SERVERCMD_VGASTART :
            //	{
            //		//CWinThread  *ThreadHandle = AfxBeginThread(_VgaSendThread,this);
            //		//CloseHandel(ThreadHandle);
            //		break;
            //	
            //	}
            //// ����VGAͼ��ɼ�
            //case SERVERCMD_VGASTOP :
            //	{
            //		// ֹͣVGAͼ������
            //		//system("EXIT");
            //		break;
            //	
            //	}
            case SERVERCMD_EXPCOMSET:
            {
                if (pDlg->str_ServerMsg_ExpComOperation == _T("Open"))
                {
                    // ��־������ʵ�鴮�ڣ���
                    pDlg->WriteLogFile(1, _T("��ʵ�鴮�ڣ�"));
                    if (pDlg->ExpComOpen(pDlg->uint_ServerMsg_ExpComBitRate, pDlg->uint_ServerMsg_ExpComDataBits, 
                        pDlg->uint_ServerMsg_ExpComStopBit, pDlg->uint_ServerMsg_ExpComParityCheck))
                    {
                        // ����ʵ�鴮�ڴ򿪳ɹ�ָ��
                        pDlg->wsEndpoint->send("<COMStatus>OpenSuccessful</COMStatus>");
                        pDlg->bool_ExpComStatus = 1;
                        // ��־����ʵ�鴮�ڴ򿪳ɹ�����
                        pDlg->WriteLogFile(1, _T("ʵ�鴮�ڴ򿪳ɹ�!"));
                    }
                    else
                    {
                        // ����ʵ�鴮�ڴ�ʧ��ָ��
                        pDlg->wsEndpoint->send("<COMStatus>OpenFailed</COMStatus>");
                        // ��־����ʵ�鴮�ڴ�ʧ�ܡ���
                        pDlg->WriteLogFile(1, _T("ʵ�鴮�ڴ�ʧ�ܡ�"));
                    }
                }
                else if (pDlg->str_ServerMsg_ExpComOperation == _T("Close"))
                {
                    // ��־�����ر�ʵ�鴮�ڣ���
                    pDlg->WriteLogFile(1, _T("�ر�ʵ�鴮�ڣ�"));
                    if (pDlg->ExpComClose())
                    {
                        // ����ʵ�鴮�ڹرճɹ�ָ��
                        pDlg->wsEndpoint->send("<COMStatus>CloseSuccessful</COMStatus>");
                        pDlg->bool_ExpComStatus = 0;
                        // ��־����ʵ�鴮�ڹرճɹ�����
                        pDlg->WriteLogFile(1, _T("ʵ�鴮�ڹرճɹ���"));
                    }
                    else
                    {
                        // ����ʵ�鴮�ڹر�ʧ��ָ��
                        pDlg->wsEndpoint->send("<COMStatus>CloseFailed</COMStatus>");
                        // ��־����ʵ�鴮�ڹر�ʧ�ܡ���
                        pDlg->WriteLogFile(1, _T("ʵ�鴮�ڹر�ʧ�ܡ�"));
                    }
                }
                break;
            }
            case SERVERCMD_EXPCOMSENDDATA:
            {
                // ���ݸ�ʽҪ�����ֽ�Ϊ��λ��ʮ�����ƣ�С��0x10�ģ���λ��0����0x0f
                CString str_DataTmp;
                BYTE byte_ExpComWriteBuf[EXPCOMBUFSIZE];


                if (pDlg->uint_ServerMsg_ExpComSendDataLength > 0)
                {
                    // �����ݴ��봮�ڷ���buffer
                    for (int i = 0; i < pDlg->uint_ServerMsg_ExpComSendDataLength; i++)
                    {
                        // �����ҽ�ȡ1�ֽ�����
                        str_DataTmp = pDlg->str_ServerMsg_ExpComSendData.Mid(i * 2, 2);
                        byte_ExpComWriteBuf[i] = (byte)(_tcstoui64(str_DataTmp, 0, 16) & 0xff);
                    }

                    // ���ڷ�������
                    pDlg->ExpComWrite(byte_ExpComWriteBuf, pDlg->uint_ServerMsg_ExpComSendDataLength);

                    // ��־
                    pDlg->WriteLogFile(1, _T("ʵ�鴮�ڷ������ݣ�") + pDlg->str_ServerMsg_ExpComSendData);
                }

                break;
            }
            case SERVERCMD_PS2SENDDATA:
            {
                // ���ݸ�ʽҪ�����ֽ�Ϊ��λ��ʮ�����ƣ�С��0x10�ģ���λ��0����0x0f
                CString str_DataTmp;
                BYTE byte_Ps2WriteBuf[256];

                if (pDlg->uint_ServerMsg_Ps2MouseSendDataLength > 0)
                {
                    // �����ݴ���PS2����buffer
                    for (int i = 0; i < pDlg->uint_ServerMsg_Ps2MouseSendDataLength; i++)
                    {
                        // �����ҽ�ȡ1�ֽ�����
                        str_DataTmp = pDlg->str_ServerMsg_Ps2MouseSendData.Mid(i * 2, 2);
                        byte_Ps2WriteBuf[i] = (byte)(_tcstoui64(str_DataTmp, 0, 16) & 0xff);
                    }

                    // ��������ݷ��͸�ʵ��fpga��������
                    pDlg->FpgaBlockWrite(0x31, byte_Ps2WriteBuf, 0x1, pDlg->uint_ServerMsg_Ps2MouseSendDataLength);

                    // ��־
                    pDlg->WriteLogFile(1, _T("PS2��귢�����ݣ�") + pDlg->str_ServerMsg_Ps2MouseSendData);
                }

                if (pDlg->uint_ServerMsg_Ps2KeyboardSendDataLength > 0)
                {
                    // �����ݴ���PS2����buffer
                    for (int i = 0; i < pDlg->uint_ServerMsg_Ps2KeyboardSendDataLength; i++)
                    {
                        // �����ҽ�ȡ1�ֽ�����
                        str_DataTmp = pDlg->str_ServerMsg_Ps2KeyboardSendData.Mid(i * 2, 2);
                        byte_Ps2WriteBuf[i] = (byte)(_tcstoui64(str_DataTmp, 0, 16) & 0xff);
                    }

                    // �Ѽ������ݷ��͸�ʵ��fpga��������
                    pDlg->FpgaBlockWrite(0x30, byte_Ps2WriteBuf, 0x1, pDlg->uint_ServerMsg_Ps2KeyboardSendDataLength);

                    // ��־
                    pDlg->WriteLogFile(1, _T("PS2���̷������ݣ�") + pDlg->str_ServerMsg_Ps2KeyboardSendData);
                }

                break;
            }
            default:
            {
                break;
            }
            }
        }
        else
        {
            pDlg->WriteLogFile(1, CString(_T("���յ��޷����������ݣ�")) + CSTR(serverMessage));
        }
    }
    
}

websocketpp::connection_hdl ConnectMetadata::getHdl() const
{
    return m_hdl;
}

std::string ConnectMetadata::getStatus() const
{
    return m_status;
}

void ConnectMetadata::setFileRcvEnable(bool flag)
{
    m_fileRcvEnable = flag;
}

CString ConnectMetadata::getParamFromCmd(CString str_ServerCmdStr, CString str_ServerCmdKeyWordStr)
{
    int ParamLength;
    int ParamLocation;
    CString ServerCmdParam;

    ParamLocation = str_ServerCmdStr.Find(_T("<") + str_ServerCmdKeyWordStr + _T(">")) + str_ServerCmdKeyWordStr.GetLength() + 2;
    ParamLength = str_ServerCmdStr.Find(_T("</") + str_ServerCmdKeyWordStr + _T(">")) - ParamLocation;
    ServerCmdParam = str_ServerCmdStr.Mid(ParamLocation, ParamLength);
    return ServerCmdParam;
}

bool ConnectMetadata::parseCmd(string cmd)
{
    auto pDlg = (CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd);
    CString str_ServerCmdStr = CSTR(cmd);
    
    // ע��ȷ��ָ�<Record><DataPort>��</DataPort></Record>
    if (str_ServerCmdStr.Left(strlen("<Record>")) == "<Record>")
    {
        pDlg->uint_ServerMsg_Cmd = SERVERCMD_RECORD;
        pDlg->str_ServerMsg_DataPort = getParamFromCmd(str_ServerCmdStr, _T("Dataport"));
        return true;
    }
    // ��¼ָ�<Load><Length>��</Length><HashCode>��</HashCode></Load>
    else if (str_ServerCmdStr.Left(strlen("<Load>")) == "<Load>")
    {
        pDlg->uint_ServerMsg_Cmd = SERVERCMD_LOAD;
        pDlg->uint_ServerMsg_FileLength = _ttoi(getParamFromCmd(str_ServerCmdStr, _T("Length")));
        pDlg->uint_ServerMsg_FileHashCode = _ttoi(getParamFromCmd(str_ServerCmdStr, _T("Hashcode")));
        return true;
    }
    // ���ݴ���ָ��:<Data>��</Data>
    else if (str_ServerCmdStr.Left(strlen("<Data>")) == "<Data>")
    {
        pDlg->uint_ServerMsg_Cmd = SERVERCMD_DATA;
        pDlg->str_ServerMsg_Data = getParamFromCmd(str_ServerCmdStr, _T("Data"));
        return true;
    }
    // �����Զ�����ָ��:<StartTest></StartTest>
    else if (str_ServerCmdStr.Left(strlen("<StartTest>")) == "<StartTest>")
    {
        pDlg->uint_ServerMsg_Cmd = SERVERCMD_STARTTEST;
        return true;
    }
    // �����Զ�����ָ��:<EndTest></EndTest>
    else if (str_ServerCmdStr.Left(strlen("<EndTest>")) == "<EndTest>")
    {
        pDlg->uint_ServerMsg_Cmd = SERVERCMD_ENDTEST;
        return true;
    }
    // �Զ�����ָ��:<Test>��</Test>
    else if (str_ServerCmdStr.Left(strlen("<Test>")) == "<Test>")
    {
        pDlg->uint_ServerMsg_Cmd = SERVERCMD_TEST;
        pDlg->str_ServerMsg_Test = getParamFromCmd(str_ServerCmdStr, _T("Test"));
        return true;
    }
    //// ����Ӧ��ָ�<Response></Response>
    //else if (str_ServerCmdStr.Left(strlen("<Response>")) == "<Response>")
    //{
    //	pDlg->uint_ServerMsg_Cmd = SERVERCMD_RESPONSE;
    //	
    //	return true;
    //}
    // ��������ѯ��λ��״ָ̬�
    // <Server><key>(key value)[string]</key><type>AskClientState</type></Server>
    else if (str_ServerCmdStr.Left(strlen("<Server><key>")) == "<Server><key>")
    {
        pDlg->str_ServerMsg_Key = getParamFromCmd(str_ServerCmdStr, _T("key"));
        pDlg->str_ServerMsg_Type = getParamFromCmd(str_ServerCmdStr, _T("type"));
        /*if (pDlg->str_ServerMsg_Type == "AskClientState")
        {
            pDlg->uint_ServerMsg_Cmd = SERVERCMD_ASKSTATE;
        }*/
        pDlg->uint_ServerMsg_Cmd = SERVERCMD_ASKSTATE;
        //pDlg->WriteLogFile(0, _T(pDlg->str_ServerMsg_Type));
        return true;
    }
    // ׼��ָ�<Ready></Ready>
    else if (str_ServerCmdStr.Left(strlen("<Ready>")) == "<Ready>")
    {
        pDlg->uint_ServerMsg_Cmd = SERVERCMD_READY;
        return true;
    }
    // �Ͽ�����ָ�<Break></Break>
    else if (str_ServerCmdStr.Left(strlen("<Break>")) == "<Break>")
    {
        pDlg->uint_ServerMsg_Cmd = SERVERCMD_BREAK;
        return true;
    }
    //// ����vgaͼ��ɼ�ָ�<VgaStart></VgaStart>
    //else if (str_ServerCmdStr.Left(strlen("<VgaStart>")) == "<VgaStart>")
    //{
    //	pDlg->uint_ServerMsg_Cmd = SERVERCMD_VGASTART;
    //	
    //	return true;
    //}
    //// ֹͣvgaͼ��ɼ�ָ�<VgaStop></VgaStop>
    //else if (str_ServerCmdStr.Left(strlen("<VgaStop>")) == "<VgaStop>")
    //{
    //	pDlg->uint_ServerMsg_Cmd = SERVERCMD_VGASTOP;
    //	
    //	return true;
    //}
    // ��������ָ�<COMSet><Operation>��</Operation><BitRate>��</BitRate><DataBits>��</DataBits><ParityCheck>��</ParityCheck><StopBit>��</StopBit></COMSet>
    else if (str_ServerCmdStr.Left(strlen("<COMSet>")) == "<COMSet>")
    {
        pDlg->uint_ServerMsg_Cmd = SERVERCMD_EXPCOMSET;
        pDlg->str_ServerMsg_ExpComOperation = getParamFromCmd(str_ServerCmdStr, _T("Operation"));
        pDlg->uint_ServerMsg_ExpComBitRate = _ttoi(getParamFromCmd(str_ServerCmdStr, _T("BitRate")));
        pDlg->uint_ServerMsg_ExpComDataBits = _ttoi(getParamFromCmd(str_ServerCmdStr, _T("DataBits")));
        pDlg->uint_ServerMsg_ExpComParityCheck = _ttoi(getParamFromCmd(str_ServerCmdStr, _T("ParityCheck")));
        pDlg->uint_ServerMsg_ExpComStopBit = _ttoi(getParamFromCmd(str_ServerCmdStr, _T("StopBit")));
        return true;
    }
    // ��������ָ�<COMSend><Length>��</Length><Data>��</Data></COMSend>
    else if (str_ServerCmdStr.Left(strlen("<COMSend>")) == "<COMSend>")
    {
        pDlg->uint_ServerMsg_Cmd = SERVERCMD_EXPCOMSENDDATA;
        pDlg->uint_ServerMsg_ExpComSendDataLength = _ttoi(getParamFromCmd(str_ServerCmdStr, _T("Length")));
        pDlg->str_ServerMsg_ExpComSendData = getParamFromCmd(str_ServerCmdStr, _T("Data"));
        return true;
    }
    // PS2���������ݴ���ָ�<PS2Send><MouseLength>��</MouseLength><MouseData>��</MouseData>
    //                          <KeyboardLength>��</KeyboardLength><KeyboardData>��</KeyboardData></PS2Send>
    else if (str_ServerCmdStr.Left(strlen("<PS2Send>")) == "<PS2Send>")
    {
        pDlg->uint_ServerMsg_Cmd = SERVERCMD_PS2SENDDATA;
        pDlg->uint_ServerMsg_Ps2MouseSendDataLength = _ttoi(getParamFromCmd(str_ServerCmdStr, _T("MouseLength")));
        pDlg->str_ServerMsg_Ps2MouseSendData = getParamFromCmd(str_ServerCmdStr, _T("MouseData"));
        pDlg->uint_ServerMsg_Ps2KeyboardSendDataLength = _ttoi(getParamFromCmd(str_ServerCmdStr, _T("KeyboardLength")));
        pDlg->str_ServerMsg_Ps2KeyboardSendData = getParamFromCmd(str_ServerCmdStr, _T("KeyboardData"));
        return true;
    }
    return false;
}

void ConnectMetadata::closeFile()
{
    m_loadFile.Abort();
}
