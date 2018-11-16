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
    pDlg->WriteLogFile(1, CString(_T("连接建立成功：")) + CSTR(m_uri));
    //pDlg->wsEndpoint->send(LPCSTR(CString("hello")));
}

void ConnectMetadata::onFail(client* c, websocketpp::connection_hdl hdl)
{
    auto pDlg = (CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd);
    m_status = "Failed";
    client::connection_ptr con = c->get_con_from_hdl(hdl);
    m_server = con->get_response_header("Server");
    m_errorReason = con->get_ec().message();
    pDlg->WriteLogFile(1, CString(_T("连接建立失败：")) + CSTR(m_uri));
}
void ConnectMetadata::onClose(client* c, websocketpp::connection_hdl hdl)
{
    auto pDlg = (CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd);
    m_status = "Closed";
    client::connection_ptr con = c->get_con_from_hdl(hdl);
    // 记录关闭原因
    std::stringstream s;
    s << "close code: " << con->get_remote_close_code() << " ("
        << websocketpp::close::status::get_string(con->get_remote_close_code())
        << "), close reason: " << con->get_remote_close_reason();
    m_errorReason = s.str();
    // 关闭相关定时器
    pDlg->KillTimer(TIMERID_DATA_SAMPLE);
    pDlg->KillTimer(TIMERID_TEST_DATA_SAMPLE);
    pDlg->KillTimer(TIMERID_FILEREV);
    pDlg->KillTimer(TIMERID_EXPCOMRX);
    // 更新工作模式为实验模式
    pDlg->str_WorkMode = _T("ExperimentMode");
    // 更新上位机状态
    pDlg->str_WorkStatus = _T("Ready");
    // 更新服务器连接状态指示
    pDlg->m_ServerConnectStatus = 0;
    // 更新服务器注册状态指示
    pDlg->m_ServerRegisterStatus = 0;
    // 初始化数据写入主控fpga
    pDlg->FpgaWrite(0, 0x10, 0xffffffffffffffff);
    //关闭文件
    m_loadFile.Abort();
    //已断开,连接按钮设为可用
    pDlg->Idc_Button_ServerConnect.SetWindowText(_T("连接"));
    pDlg->Idc_Button_ServerConnect.EnableWindow(TRUE);
    //断开连接不可用
    pDlg->Idc_Button_ServerDisconnect.SetWindowText(_T("已断开"));
    pDlg->Idc_Button_ServerDisconnect.EnableWindow(FALSE);
    // 日志：“服务器连接断开：”
    pDlg->WriteLogFile(1, CString(_T("连接关闭，关闭原因：")) + CSTR(m_errorReason));
}

void ConnectMetadata::onMessage(websocketpp::connection_hdl hdl, client::message_ptr msg)
{
    auto pDlg = (CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd);
    auto serverMessage = msg->get_payload();
    if (msg->get_opcode() == websocketpp::frame::opcode::text) {
        pDlg->WriteLogFile(1, CString(_T("收到text消息：")) + CSTR(serverMessage));
    }
    else {
        //pDlg->WriteLogFile(1, CString(_T("收到binary消息：")) + CSTR(websocketpp::utility::to_hex(serverMessage)));
    }
    if (!m_fileRcvEnable)// 不在传输文件
    {
        if (parseCmd(serverMessage))
        {
            switch (pDlg->uint_ServerMsg_Cmd)
            {
            case SERVERCMD_RECORD:
            {
                pDlg->WriteLogFile(1, _T("服务器注册成功!"));
                pDlg->m_ServerRegisterStatus = 1;
                break;
            }
            case SERVERCMD_ASKSTATE:
            {
                pDlg->WriteLogFile(1, _T("收到服务器查询上位机状态指令!"));
                CString toSend = _T("<Client><key>") + pDlg->str_ServerMsg_Key + pDlg->str_UpperComputerID + 
                    _T("</key><type>ReplyToServerWithState</type><state>") + pDlg->str_WorkStatus + _T("</state></Client>");
                pDlg->WriteLogFile(0, _T("发送上位机状态指令："));
                pDlg->wsEndpoint->send(LPCSTR(toSend));
                break;
            }
            case SERVERCMD_LOAD:
            {
                pDlg->WriteLogFile(1, _T("收到烧录指令。"));
                // 更新上位机状态
                pDlg->str_WorkStatus = _T("Working");
                // 关闭相关定时器
                pDlg->KillTimer(TIMERID_DATA_SAMPLE);
                // 开始接收加载文件
                // 新建加载文件路径
                if (!PathFileExists(_T("program")))
                {
                    CreateDirectory(_T("program"), NULL);
                }
                // 如果已有加载文件，则删除
                if (PathFileExists(_T("program\\bitfile.bit")))
                {
                    m_loadFile.Abort();
                    CFile::Remove(_T("program\\bitfile.bit"));
                }
                // 新建加载文件，并打开
                if (!m_loadFile.Open(_T("program\\bitfile.bit"), CFile::modeCreate | CFile::modeReadWrite))
                {
                    pDlg->WriteLogFile(1, _T("文件创建失败。"));
                }
                else
                {
                    // 日志：“文件创建成功：”
                    pDlg->WriteLogFile(1, _T("文件创建成功。"));
                    // 启动文件接收超时定时器
                    pDlg->SetTimer(TIMERID_FILEREV, TIMERID_FILEREV_TIME, NULL);
                    // 接收长度清零
                    m_fileRcvLengthSum = 0;
                    // 文件接收使能有效
                    m_fileRcvEnable = true;
                    m_over50 = false;
                    // 响应指令
                    pDlg->wsEndpoint->send("<File></File>");
                    pDlg->WriteLogFile(0, _T("开始接收文件......"));
                }
                break;
            }
            case SERVERCMD_DATA:
            {
                // 数据写入主控fpga
                pDlg->FpgaWrite(0, 0x10, _tcstoui64(pDlg->str_ServerMsg_Data.Mid(26, 4), 0, 16));
                pDlg->FpgaWrite(0, 0x12, _tcstoui64(pDlg->str_ServerMsg_Data.Mid(30, 16), 0, 16));
                break;
            }
            case SERVERCMD_STARTTEST:
            {
                // 更新工作模式为自动测试模式
                pDlg->str_WorkMode = _T("TestMode");
                // 发送启动自动测试返回指令
                pDlg->WriteLogFile(1, _T("收到启动自动测试指令。"));
                pDlg->WriteLogFile(0, _T("发送启动自动测试返回指令："));
                pDlg->wsEndpoint->send("<StartTest></StartTest>");
                
                break;
            }
            case SERVERCMD_ENDTEST:
            {
                pDlg->WriteLogFile(1, _T("收到停止自动测试指令。"));
                // 发送停止自动测试返回指令
                pDlg->WriteLogFile(0, _T("发送停止自动测试返回指令："));
                pDlg->wsEndpoint->send("<EndTest></EndTest>");
                // 更新工作模式为实验模式
                pDlg->str_WorkMode = _T("ExperimentMode");
                break;
            }
            case SERVERCMD_TEST:
            {
                // 数据写入主控fpga
                pDlg->FpgaWrite(0, 0x10, _tcstoui64(pDlg->str_ServerMsg_Test.Mid(22, 12), 0, 16));
                // 启动自动测试数据采集定时器
                pDlg->SetTimer(TIMERID_TEST_DATA_SAMPLE, TIMERID_TEST_DATA_SAMPLE_TIME, NULL);
                break;
            }
            case SERVERCMD_READY:
            {
                if (pDlg->str_WorkStatus == _T("Working"))
                {
                    // 发送正忙指令
                    pDlg->WriteLogFile(1, _T("收到待命指令。"));
                    pDlg->WriteLogFile(0, _T("发送正忙指令："));
                    pDlg->wsEndpoint->send("<Answer><State>Busy</State></Answer>");
                }
                else
                {
                    // 发送准备就绪确认指令
                    pDlg->WriteLogFile(1, _T("收到待命指令："));
                    pDlg->WriteLogFile(0, _T("发送准备就绪确认指令。"));
                    pDlg->wsEndpoint->send("<Answer><State>Already</State></Answer>");
                }
                break;
            }
            case SERVERCMD_BREAK:
            {
                // 关闭相关定时器
                pDlg->KillTimer(TIMERID_DATA_SAMPLE);
                pDlg->KillTimer(TIMERID_TEST_DATA_SAMPLE);
                pDlg->KillTimer(TIMERID_EXPCOMRX);
                // 更新工作模式为实验模式
                pDlg->str_WorkMode = _T("ExperimentMode");
                // 更新上位机状态
                pDlg->str_WorkStatus = _T("Ready");
                // 初始化数据写入主控fpga
                pDlg->FpgaWrite(0, 0x10, 0xffffffffffffffff);
                // 日志
                pDlg->WriteLogFile(1, _T("收到断开指令："));
                pDlg->WriteLogFile(0, _T("发送断开确认指令。"));
                // 发送断开确认指令
                pDlg->wsEndpoint->send("<Broken></Broken>");
                break;
            }
            //// 启动VGA图像采集
            //case SERVERCMD_VGASTART :
            //	{
            //		//CWinThread  *ThreadHandle = AfxBeginThread(_VgaSendThread,this);
            //		//CloseHandel(ThreadHandle);
            //		break;
            //	
            //	}
            //// 结束VGA图像采集
            //case SERVERCMD_VGASTOP :
            //	{
            //		// 停止VGA图像推送
            //		//system("EXIT");
            //		break;
            //	
            //	}
            case SERVERCMD_EXPCOMSET:
            {
                if (pDlg->str_ServerMsg_ExpComOperation == _T("Open"))
                {
                    // 日志：“打开实验串口：”
                    pDlg->WriteLogFile(1, _T("打开实验串口："));
                    if (pDlg->ExpComOpen(pDlg->uint_ServerMsg_ExpComBitRate, pDlg->uint_ServerMsg_ExpComDataBits, 
                        pDlg->uint_ServerMsg_ExpComStopBit, pDlg->uint_ServerMsg_ExpComParityCheck))
                    {
                        // 发送实验串口打开成功指令
                        pDlg->wsEndpoint->send("<COMStatus>OpenSuccessful</COMStatus>");
                        // 启动实验串口接收定时器
                        pDlg->SetTimer(TIMERID_EXPCOMRX, TIMERID_EXPCOMRX_TIME, NULL);
                        // 日志：“实验串口打开成功：”
                        pDlg->WriteLogFile(1, _T("实验串口打开成功!"));
                    }
                    else
                    {
                        // 发送实验串口打开失败指令
                        pDlg->wsEndpoint->send("<COMStatus>OpenFailed</COMStatus>");
                        // 日志：“实验串口打开失败。”
                        pDlg->WriteLogFile(1, _T("实验串口打开失败。"));
                    }
                }
                else if (pDlg->str_ServerMsg_ExpComOperation == _T("Close"))
                {
                    // 关闭实验串口接收定时器
                    pDlg->KillTimer(TIMERID_EXPCOMRX);
                    // 日志：“关闭实验串口：”
                    pDlg->WriteLogFile(1, _T("关闭实验串口："));
                    if (pDlg->ExpComClose())
                    {
                        // 发送实验串口关闭成功指令
                        pDlg->wsEndpoint->send("<COMStatus>CloseSuccessful</COMStatus>");
                        // 日志：“实验串口关闭成功。”
                        pDlg->WriteLogFile(1, _T("实验串口关闭成功。"));
                    }
                    else
                    {
                        // 发送实验串口关闭失败指令
                        pDlg->wsEndpoint->send("<COMStatus>CloseFailed</COMStatus>");
                        // 日志：“实验串口关闭失败。”
                        pDlg->WriteLogFile(1, _T("实验串口关闭失败。"));
                    }
                }
                break;
            }
            case SERVERCMD_EXPCOMSENDDATA:
            {
                // 数据格式要求以字节为单位，十六进制，小于0x10的，高位填0，如0x0f
                int int_ExpComSendDataCount = 0;
                CString srt_DataTmp;
                unsigned int uint_ExpComSendDataLength = 0;
                CString str_ExpComSendData;
                BYTE byte_ExpComWriteBuf[EXPCOMBUFSIZE];

                uint_ExpComSendDataLength = pDlg->uint_ServerMsg_ExpComSendDataLength;
                str_ExpComSendData = pDlg->str_ServerMsg_ExpComSendData;

                // 日志：“实验串口发送数据：”
                pDlg->WriteLogFile(1, _T("实验串口发送数据："));
                pDlg->WriteLogFile(0, str_ExpComSendData);

                // 把数据存入串口发送buffer
                for (int_ExpComSendDataCount = 0; int_ExpComSendDataCount < uint_ExpComSendDataLength; int_ExpComSendDataCount++)
                {
                    // 从左到右截取1字节数据
                    srt_DataTmp = str_ExpComSendData.Mid(int_ExpComSendDataCount * 2, 2);
                    byte_ExpComWriteBuf[int_ExpComSendDataCount] = (byte)(_tcstoui64(srt_DataTmp, 0, 16) & 0xff);
                }
                // 串口发送数据
                pDlg->ExpComWrite(byte_ExpComWriteBuf, uint_ExpComSendDataLength);
                break;
            }
            case SERVERCMD_PS2SENDDATA:
            {
                int int_Ps2SendDataCount = 0;
                CString str_DataTmp;
                unsigned __int64 uint64_DataTmp;
                unsigned int uint_Ps2SendDataLength = 0;
                CString str_Ps2SendData;

                uint_Ps2SendDataLength = pDlg->uint_ServerMsg_Ps2MouseSendDataLength;
                str_Ps2SendData = pDlg->str_ServerMsg_Ps2MouseSendData;

                if (uint_Ps2SendDataLength > 0)
                {
                    // 日志：“PS2鼠标发送数据：”
                    pDlg->WriteLogFile(1, _T("PS2鼠标发送数据："));
                    pDlg->WriteLogFile(0, str_Ps2SendData);

                    // 把鼠标数据发送给实验fpga的主机端
                    for (int_Ps2SendDataCount = 0; int_Ps2SendDataCount < uint_Ps2SendDataLength; int_Ps2SendDataCount++)
                    {
                        // 从左到右截取1字节数据
                        str_DataTmp = str_Ps2SendData.Mid(int_Ps2SendDataCount * 2, 2);
                        uint64_DataTmp = _tcstoui64(str_DataTmp, 0, 16) & 0xff;
                        pDlg->FpgaWrite(0, 0x30, ((uint64_DataTmp | 0x0000000000000100) << 32));
                    }
                }

                uint_Ps2SendDataLength = pDlg->uint_ServerMsg_Ps2KeyboardSendDataLength;
                str_Ps2SendData = pDlg->str_ServerMsg_Ps2KeyboardSendData;

                if (uint_Ps2SendDataLength > 0)
                {
                    // 日志：“PS2键盘发送数据：”
                    pDlg->WriteLogFile(1, _T("PS2键盘发送数据："));
                    pDlg->WriteLogFile(0, str_Ps2SendData);

                    // 把鼠标数据发送给实验fpga的主机端
                    for (int_Ps2SendDataCount = 0; int_Ps2SendDataCount < uint_Ps2SendDataLength; int_Ps2SendDataCount++)
                    {
                        // 从左到右截取1字节数据
                        str_DataTmp = str_Ps2SendData.Mid(int_Ps2SendDataCount * 2, 2);
                        uint64_DataTmp = _tcstoui64(str_DataTmp, 0, 16) & 0xff;
                        pDlg->FpgaWrite(0, 0x30, (uint64_DataTmp | 0x0000000000000100));
                    }
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
            pDlg->WriteLogFile(1, CString(_T("接收到无法解析的内容：")) + CSTR(serverMessage));
        }
    }
    else// 接收文件
    {
        size_t lenOfSlice = serverMessage.length();
        m_fileRcvLengthSum += lenOfSlice;
        //pDlg->WriteLogFile(1, _T("接收文件片段长度：") + lenOfSlice);
        if (!m_over50 && double(m_fileRcvLengthSum) / pDlg->uint_ServerMsg_FileLength > 0.5)
        {
            pDlg->WriteLogFile(0, _T("已接收50%......"));
            m_over50 = true;
        }
        m_loadFile.Write(serverMessage.c_str(), lenOfSlice);
        if (m_fileRcvLengthSum >= pDlg->uint_ServerMsg_FileLength)// 总长度达到期望文件长度，停止接收并处理
        {
            // 关闭文件接收超时定时器
            pDlg->KillTimer(TIMERID_FILEREV);
            m_loadFile.Close();
            if (m_fileRcvLengthSum == pDlg->uint_ServerMsg_FileLength)// 长度对应相等
            {
                // 发送接收确认指令:<Receive><Result>…</Result></Receive>
                pDlg->wsEndpoint->send("<Receive><Result>Successful</Result></Receive>");
                // 日志："文件接收成功："
                pDlg->WriteLogFile(0, _T("文件接收成功。"));
                // 设置fpga升级模式为在线模式
                pDlg->int_FpgaUpdateMode = FPGA_UPDATE_MODE_ONLINE;
                // 选择jtag加载模式
                pDlg->Idc_Check_FPGAUpdateJtagTestEn.SetCheck(0);
                pDlg->Idc_Radio_FPGAUpdateJtagSelect.SetCheck(1);
                pDlg->Idc_Radio_FPGAUpdateSpiFlashSelect.SetCheck(0);
                // 启动烧写线程
                pDlg->FpgaUpdateThreadStart();
            }
            else //长度不对，接受失败
            {
                pDlg->wsEndpoint->send("<Receive><Result>Failed</Result></Receive>");
                pDlg->WriteLogFile(0, _T("文件接收失败：文件超长。"));
            }
            m_fileRcvEnable = false;// 文件接收使能关闭
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
    // 注册确认指令：<Record><DataPort>…</DataPort></Record>
    if (str_ServerCmdStr.Left(strlen("<Record>")) == "<Record>")
    {
        pDlg->uint_ServerMsg_Cmd = SERVERCMD_RECORD;
        pDlg->str_ServerMsg_DataPort = getParamFromCmd(str_ServerCmdStr, _T("Dataport"));
        return true;
    }
    // 烧录指令：<Load><Length>…</Length><HashCode>…</HashCode></Load>
    else if (str_ServerCmdStr.Left(strlen("<Load>")) == "<Load>")
    {
        pDlg->uint_ServerMsg_Cmd = SERVERCMD_LOAD;
        pDlg->uint_ServerMsg_FileLength = _ttoi(getParamFromCmd(str_ServerCmdStr, _T("Length")));
        pDlg->uint_ServerMsg_FileHashCode = _ttoi(getParamFromCmd(str_ServerCmdStr, _T("Hashcode")));
        return true;
    }
    // 数据传输指令:<Data>…</Data>
    else if (str_ServerCmdStr.Left(strlen("<Data>")) == "<Data>")
    {
        pDlg->uint_ServerMsg_Cmd = SERVERCMD_DATA;
        pDlg->str_ServerMsg_Data = getParamFromCmd(str_ServerCmdStr, _T("Data"));
        return true;
    }
    // 启动自动测试指令:<StartTest></StartTest>
    else if (str_ServerCmdStr.Left(strlen("<StartTest>")) == "<StartTest>")
    {
        pDlg->uint_ServerMsg_Cmd = SERVERCMD_STARTTEST;
        return true;
    }
    // 结束自动测试指令:<EndTest></EndTest>
    else if (str_ServerCmdStr.Left(strlen("<EndTest>")) == "<EndTest>")
    {
        pDlg->uint_ServerMsg_Cmd = SERVERCMD_ENDTEST;
        return true;
    }
    // 自动测试指令:<Test>…</Test>
    else if (str_ServerCmdStr.Left(strlen("<Test>")) == "<Test>")
    {
        pDlg->uint_ServerMsg_Cmd = SERVERCMD_TEST;
        pDlg->str_ServerMsg_Test = getParamFromCmd(str_ServerCmdStr, _T("Test"));
        return true;
    }
    //// 心跳应答指令：<Response></Response>
    //else if (str_ServerCmdStr.Left(strlen("<Response>")) == "<Response>")
    //{
    //	pDlg->uint_ServerMsg_Cmd = SERVERCMD_RESPONSE;
    //	
    //	return true;
    //}
    // 服务器查询上位机状态指令：
    // <Server><key>(key value)[string]</key><type>AskClientState</type></Server>
    else if (str_ServerCmdStr.Left(strlen("<Server><key>")) == "<Server><key>")
    {
        pDlg->str_ServerMsg_Key = getParamFromCmd(str_ServerCmdStr, _T("<key>"));
        pDlg->str_ServerMsg_Type = getParamFromCmd(str_ServerCmdStr, _T("<type>"));
        if (pDlg->str_ServerMsg_Type == "AskClientState")
        {
            pDlg->uint_ServerMsg_Cmd = SERVERCMD_ASKSTATE;
        }
        return true;
    }
    // 准备指令：<Ready></Ready>
    else if (str_ServerCmdStr.Left(strlen("<Ready>")) == "<Ready>")
    {
        pDlg->uint_ServerMsg_Cmd = SERVERCMD_READY;
        return true;
    }
    // 断开连接指令：<Break></Break>
    else if (str_ServerCmdStr.Left(strlen("<Break>")) == "<Break>")
    {
        pDlg->uint_ServerMsg_Cmd = SERVERCMD_BREAK;
        return true;
    }
    //// 启动vga图像采集指令：<VgaStart></VgaStart>
    //else if (str_ServerCmdStr.Left(strlen("<VgaStart>")) == "<VgaStart>")
    //{
    //	pDlg->uint_ServerMsg_Cmd = SERVERCMD_VGASTART;
    //	
    //	return true;
    //}
    //// 停止vga图像采集指令：<VgaStop></VgaStop>
    //else if (str_ServerCmdStr.Left(strlen("<VgaStop>")) == "<VgaStop>")
    //{
    //	pDlg->uint_ServerMsg_Cmd = SERVERCMD_VGASTOP;
    //	
    //	return true;
    //}
    // 串口设置指令：<COMSet><Operation>…</Operation><BitRate>…</BitRate><DataBits>…</DataBits><ParityCheck>…</ParityCheck><StopBit>…</StopBit></COMSet>
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
    // 串口数据指令：<COMSend><Length>…</Length><Data>…</Data></COMSend>
    else if (str_ServerCmdStr.Left(strlen("<COMSend>")) == "<COMSend>")
    {
        pDlg->uint_ServerMsg_Cmd = SERVERCMD_EXPCOMSENDDATA;
        pDlg->uint_ServerMsg_ExpComSendDataLength = _ttoi(getParamFromCmd(str_ServerCmdStr, _T("Length")));
        pDlg->str_ServerMsg_ExpComSendData = getParamFromCmd(str_ServerCmdStr, _T("Data"));
        return true;
    }
    // PS2鼠标键盘数据传输指令：<PS2Send><MouseLength>…</MouseLength><MouseData>…</MouseData>
    //                          <KeyboardLength>…</KeyboardLength><KeyboardData>…</KeyboardData></PS2Send>
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
