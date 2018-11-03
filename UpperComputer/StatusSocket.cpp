// StatusSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "UpperComputer.h"
#include "StatusSocket.h"
#include "UpperComputerDlg.h"
#include "resource.h"
#include "stdio.h"
#include "define.h"





// StatusSocket 


StatusSocket::StatusSocket()
{
}

StatusSocket::~StatusSocket()
{
}


// StatusSocket 成员函数




////VGA视频推送线程
//UINT _VgaSendThread(LPVOID lparam)
//{  	
//	// 启动VGA图像推送，推送给服务器
//	system("ffmpeg -rtbufsize 100M -f dshow -i video=\"VGA2USB V2U967295\" -vcodec libx264 -an -f flv -y \"rtmp://10.2.26.104:1935/live/livestream\"");
// 
//    return 1;
//
//}


void StatusSocket::Init()
{
	m_pFile=new CSocketFile(this);
	m_pArchiveIn=new CArchive(m_pFile,CArchive::load);
	m_pArchiveOut=new CArchive(m_pFile,CArchive::store);
    bool_ServerFileRevEn = 0;
}

void StatusSocket::OnReceive(int nErrorCode)
{
	char ServerCmdBuf[512];
	int ServerCmdRevCnt;
	CString str_ServerCmdStr;
	CString str_SendStr;
	int int_ServerFileRevCnt = 0;

    if ( bool_ServerFileRevEn )
    {

        // 接收数据
	    int_ServerFileRevCnt = ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->m_StatusSocket->Receive(char_ServerFileRevBuf,64*1024,0);
    
        // 写入文件
	    f_LoadFile.Write(char_ServerFileRevBuf,int_ServerFileRevCnt);
	    dword_FileRevSumLength+=int_ServerFileRevCnt;

        if ( dword_FileRevSumLength >= ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_FileLength )
        {
            // 关闭文件接收超时定时器
	        ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->KillTimer(TIMERID_FILEREV);
	
            //关闭文件
            f_LoadFile.Close();

            if ( dword_FileRevSumLength == ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_FileLength )
            {
	            // 发送接收确认指令:<Receive><Result>…</Result></Receive>
	            ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->SendCmd(_T("<Receive><Result>Successful</Result></Receive>")); 
	            // 日志："文件接收成功："
                ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->WriteLogFile(1,_T("文件接收成功。"));

				// 设置fpga升级模式为在线模式
				((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->int_FpgaUpdateMode = FPGA_UPDATE_MODE_ONLINE;
				// 选择jtag加载模式
				((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->Idc_Check_FPGAUpdateJtagTestEn.SetCheck(0);
				((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->Idc_Radio_FPGAUpdateJtagSelect.SetCheck(1);
				((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->Idc_Radio_FPGAUpdateSpiFlashSelect.SetCheck(0);

				// 启动烧写线程
				((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->FpgaUpdateThreadStart();
            }
            else
            {
	            // 发送接收确认指令:<Receive><Result>…</Result></Receive>
	            ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->SendCmd(_T("<Receive><Result>Failed</Result></Receive>")); 
	            // 日志："文件接收失败："
                ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->WriteLogFile(1,_T("文件接收失败：文件超长。"));
            }
            // 加载文件接收使能关闭
            bool_ServerFileRevEn = 0;



        }
    }
    else
    {
	    ServerCmdRevCnt = ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->m_StatusSocket->Receive(ServerCmdBuf,512,0);
	    str_ServerCmdStr.Format(_T("%s"), ServerCmdBuf);
	    str_ServerCmdStr = str_ServerCmdStr.Left(ServerCmdRevCnt);

        // 日志：“接收到指令：”
        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("接收到指令："));
        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(0,str_ServerCmdStr);

        // 指令解析
	    if (ServerCmdParse(str_ServerCmdStr))
	    {
		    switch (((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd)
		    {
			    case SERVERCMD_RECORD :
				    {
					    // 日志：“服务器注册成功：”
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("服务器注册成功!"));
                        
					    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->m_ServerRegisterStatus = 1;
				

					    break;
				    }

			    case SERVERCMD_ASKSTATE :
				    {
					    // 日志：“服务器查询上位机状态”
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("收到服务器查询上位机状态指令!"));

					    // 发送上位机状态指令
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SendCmd(_T("<Client><key>") + ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_Key + ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_UpperComputerID + _T("</key><type>ReplyToServerWithState</type><state>") + ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_WorkStatus + _T("</state></Client>"));

					    // 日志：
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("发送上位机状态指令："));
                        


					    break;
				    }

			    case SERVERCMD_LOAD :
				    {
					    // 日志：“收到烧录指令：”
                        ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->WriteLogFile(1,_T("收到烧录指令。"));

                        // 更新上位机状态
                        ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->str_WorkStatus = _T("Working");
                        // 关闭相关定时器
	                    ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->KillTimer(TIMERID_DATA_SAMPLE);
                        
                        // 开始接收加载文件
                        // 新建加载文件路径
                        if (!PathFileExists(_T("program")))
                        {
	                        CreateDirectory(_T("program"),NULL);
                        }
                        // 如果已有加载文件，则删除
                        if (PathFileExists(_T("program\\bitfile.bit")))
                        {
                            f_LoadFile.Abort();
                            CFile::Remove(_T("program\\bitfile.bit"));
                        }

                        // 新建加载文件，并打开
	                    if (!f_LoadFile.Open(_T("program\\bitfile.bit"),CFile::modeCreate|CFile::modeReadWrite))
	                    {
		                    // 日志：“文件创建失败：”
                            ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->WriteLogFile(1,_T("文件创建失败。"));

	                    }
                        else
                        {
		                    // 日志：“文件创建成功：”
                            ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->WriteLogFile(1,_T("文件创建成功。"));
                            // 响应指令
                            ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SendCmd(CString(_T("<File></File>")));
                            // 启动文件接收超时定时器
	                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SetTimer( TIMERID_FILEREV, TIMERID_FILEREV_TIME, NULL );
                            // 清零
                            dword_FileRevSumLength = 0;
                            // 文件接收使能有效
					        bool_ServerFileRevEn = 1;
                        }

					    break;
				    }
			
			    case SERVERCMD_DATA :
				    {
					    // 数据写入主控fpga
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->FpgaWrite(0,0x10,_tcstoui64(((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_Data.Mid(26, 4),0,16));
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->FpgaWrite(0,0x12,_tcstoui64(((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_Data.Mid(30, 16),0,16));
					    break;
				    }

			    case SERVERCMD_STARTTEST :
				    {
                        // 更新工作模式为自动测试模式
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_WorkMode = _T("TestMode");
					    // 发送启动自动测试返回指令
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SendCmd(CString(_T("<StartTest></StartTest>")));

                        // 日志：“收到启动自动测试指令：”
					    // “发送启动自动测试返回指令”
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("收到启动自动测试指令："));
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(0,_T("发送启动自动测试返回指令。"));

					    break;
				    }

			    case SERVERCMD_ENDTEST :
				    {
					    // 发送停止自动测试返回指令
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SendCmd(CString(_T("<EndTest></EndTest>")));
                        // 更新工作模式为实验模式
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_WorkMode = _T("ExperimentMode");


                        // 日志：“收到停止自动测试指令：”
					    // “发送停止自动测试返回指令”
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("收到停止自动测试指令："));
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(0,_T("发送停止自动测试返回指令。"));

					    break;
				    }

			    case SERVERCMD_TEST :
				    {
					    // 数据写入主控fpga
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->FpgaWrite(0,0x10,_tcstoui64(((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_Test.Mid(22, 12),0,16));
	                    // 启动自动测试数据采集定时器
	                    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SetTimer( TIMERID_TEST_DATA_SAMPLE, TIMERID_TEST_DATA_SAMPLE_TIME, NULL );

					    break;
				    }

			    case SERVERCMD_READY :
				    {
                        if (((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_WorkStatus == _T("Working"))
                        {
					        // 发送正忙指令
                            ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SendCmd(CString(_T("<Answer><State>Busy</State></Answer>")));
                            // 日志：“收到待命指令：”
					        // “发送正忙指令”
                            ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("收到待命指令："));
                            ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(0,_T("发送正忙指令。"));
                        }
                        else
                        {
					        // 发送准备就绪确认指令
                            ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SendCmd(CString(_T("<Answer><State>Already</State></Answer>")));
                            // 日志：“收到待命指令：”
					        // “发送准备就绪确认指令”
                            ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("收到待命指令："));
                            ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(0,_T("发送准备就绪确认指令。"));
                       }


					    break;
				    }

			    case SERVERCMD_BREAK :
				    {
                        // 关闭相关定时器
	                    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->KillTimer(TIMERID_DATA_SAMPLE);
	                    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->KillTimer(TIMERID_TEST_DATA_SAMPLE);
						((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->KillTimer(TIMERID_EXPCOMRX);

                        // 更新工作模式为实验模式
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_WorkMode = _T("ExperimentMode");

                        // 更新上位机状态
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_WorkStatus = _T("Ready");

                        // 初始化数据写入主控fpga
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->FpgaWrite(0,0x10,0xffffffffffffffff);


						
						// 发送断开确认指令
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SendCmd(CString(_T("<Broken></Broken>")));
                        // 日志：“收到断开指令：”
					    // “发送断开确认指令”
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("收到断开指令："));
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(0,_T("发送断开确认指令。"));

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
				case SERVERCMD_EXPCOMSET :
					{
						if (((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_ExpComOperation == _T("Open"))
						{
							// 日志：“打开实验串口：”
							((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("打开实验串口："));

							if(((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->ExpComOpen(((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_ExpComBitRate,((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_ExpComDataBits,((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_ExpComStopBit,((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_ExpComParityCheck))
							{

								// 发送实验串口打开成功指令
								((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SendCmd(CString(_T("<COMStatus>OpenSuccessful</COMStatus>")));
								// 启动实验串口接收定时器
								((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SetTimer( TIMERID_EXPCOMRX, TIMERID_EXPCOMRX_TIME, NULL );

								// 日志：“实验串口打开成功：”
								((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("实验串口打开成功!"));
							}
							else
							{
								// 发送实验串口打开失败指令
								((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SendCmd(CString(_T("<COMStatus>OpenFailed</COMStatus>")));

								// 日志：“实验串口打开失败。”
								((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("实验串口打开失败。"));
							}

							
							
						}
						else if (((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_ExpComOperation == _T("Close"))
						{
							// 关闭实验串口接收定时器
							((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->KillTimer(TIMERID_EXPCOMRX);


							// 日志：“关闭实验串口：”
							((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("关闭实验串口："));

							if (((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->ExpComClose())
							{
								// 发送实验串口关闭成功指令
								((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SendCmd(CString(_T("<COMStatus>CloseSuccessful</COMStatus>")));
								// 日志：“实验串口关闭成功。”
								((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("实验串口关闭成功。"));
							}
							else 
							{
								// 发送实验串口关闭失败指令
								((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SendCmd(CString(_T("<COMStatus>CloseFailed</COMStatus>")));
								// 日志：“实验串口关闭失败。”
								((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("实验串口关闭失败。"));
							}

						}


					    break;
					}

				case SERVERCMD_EXPCOMSENDDATA :
					{
						// 数据格式要求以字节为单位，十六进制，小于0x10的，高位填0，如0x0f
						int int_ExpComSendDataCount = 0;
						CString srt_DataTmp;
						unsigned int uint_ExpComSendDataLength = 0;
						CString str_ExpComSendData;
						BYTE byte_ExpComWriteBuf[EXPCOMBUFSIZE];

						uint_ExpComSendDataLength = ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_ExpComSendDataLength;
						str_ExpComSendData = ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_ExpComSendData;

						// 日志：“实验串口发送数据：”
						((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("实验串口发送数据："));
						((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(0,str_ExpComSendData);


						// 把数据存入串口发送buffer
						for (int_ExpComSendDataCount = 0; int_ExpComSendDataCount < uint_ExpComSendDataLength ; int_ExpComSendDataCount++)
						{
							// 从左到右截取1字节数据
							srt_DataTmp = str_ExpComSendData.Mid(int_ExpComSendDataCount * 2, 2);
							byte_ExpComWriteBuf[int_ExpComSendDataCount]  = (byte)( _tcstoui64(srt_DataTmp,0,16) & 0xff );
						}

						// 串口发送数据
						((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->ExpComWrite( byte_ExpComWriteBuf,uint_ExpComSendDataLength );



					    break;
					}

				case SERVERCMD_PS2SENDDATA :
					{
						int int_Ps2SendDataCount = 0;
						CString str_DataTmp;
						unsigned __int64 uint64_DataTmp;
						unsigned int uint_Ps2SendDataLength = 0;
						CString str_Ps2SendData;

						uint_Ps2SendDataLength = ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Ps2MouseSendDataLength;
						str_Ps2SendData = ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_Ps2MouseSendData;

						if (uint_Ps2SendDataLength > 0)
						{
							// 日志：“PS2鼠标发送数据：”
							((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("PS2鼠标发送数据："));
							((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(0,str_Ps2SendData);
						
							// 把鼠标数据发送给实验fpga的主机端
							for (int_Ps2SendDataCount = 0; int_Ps2SendDataCount < uint_Ps2SendDataLength ; int_Ps2SendDataCount++)
							{
								// 从左到右截取1字节数据
								str_DataTmp = str_Ps2SendData.Mid(int_Ps2SendDataCount * 2, 2);
								uint64_DataTmp = _tcstoui64(str_DataTmp,0,16) & 0xff;
								((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->FpgaWrite(0, 0x30, ((uint64_DataTmp | 0x0000000000000100) << 32));
							}
						}

						uint_Ps2SendDataLength = ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Ps2KeyboardSendDataLength;
						str_Ps2SendData = ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_Ps2KeyboardSendData;

						if (uint_Ps2SendDataLength > 0)
						{
							// 日志：“PS2键盘发送数据：”
							((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("PS2键盘发送数据："));
							((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(0,str_Ps2SendData);
						
							// 把鼠标数据发送给实验fpga的主机端
							for (int_Ps2SendDataCount = 0; int_Ps2SendDataCount < uint_Ps2SendDataLength ; int_Ps2SendDataCount++)
							{
								// 从左到右截取1字节数据
								str_DataTmp = str_Ps2SendData.Mid(int_Ps2SendDataCount * 2, 2);
								uint64_DataTmp = _tcstoui64(str_DataTmp,0,16) & 0xff;
								((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->FpgaWrite(0, 0x30, (uint64_DataTmp | 0x0000000000000100));
							}
						}


					    break;
					}
		
			    default :
				    {					
					    break;
				    }
		
		    }
	
	    }

    }



	CSocket::OnReceive(nErrorCode);
}


int StatusSocket::ServerCmdParse(CString str_ServerCmdStr)
{

	// 注册确认指令：<Record><DataPort>…</DataPort></Record>
	if (str_ServerCmdStr.Left(strlen("<Record>")) == "<Record>")
	{
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_RECORD;
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_DataPort = GetServerCmdParam(str_ServerCmdStr, _T("Dataport"));
		
		return 1;
	}
	// 烧录指令：<Load><Length>…</Length><HashCode>…</HashCode></Load>
	else if (str_ServerCmdStr.Left(strlen("<Load>")) == "<Load>")
	{
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_LOAD;
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_FileLength = _ttoi(GetServerCmdParam(str_ServerCmdStr, _T("Length")));
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_FileHashCode = _ttoi(GetServerCmdParam(str_ServerCmdStr, _T("Hashcode")));
		
		return 1;
	}
	// 数据传输指令:<Data>…</Data>
	else if (str_ServerCmdStr.Left(strlen("<Data>")) == "<Data>")
	{
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_DATA;
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_Data = GetServerCmdParam(str_ServerCmdStr, _T("Data"));
		
		return 1;
	}
	// 启动自动测试指令:<StartTest></StartTest>
	else if (str_ServerCmdStr.Left(strlen("<StartTest>")) == "<StartTest>")
	{
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_STARTTEST;
		
		return 1;
	}
	// 结束自动测试指令:<EndTest></EndTest>
	else if (str_ServerCmdStr.Left(strlen("<EndTest>")) == "<EndTest>")
	{
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_ENDTEST;
		
		return 1;
	}
	// 自动测试指令:<Test>…</Test>
	else if (str_ServerCmdStr.Left(strlen("<Test>")) == "<Test>")
	{
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_TEST;
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_Test = GetServerCmdParam(str_ServerCmdStr, _T("Test"));
		
		return 1;
	}
	//// 心跳应答指令：<Response></Response>
	//else if (str_ServerCmdStr.Left(strlen("<Response>")) == "<Response>")
	//{
	//	((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_RESPONSE;
	//	
	//	return 1;
	//}
	// 服务器查询上位机状态指令：
	// <Server><key>(key value)[string]</key><type>AskClientState</type></Server>
	else if (str_ServerCmdStr.Left(strlen("<Server><key>")) == "<Server><key>")
	{
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_Key = GetServerCmdParam(str_ServerCmdStr, _T("<key>"));
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_Type = GetServerCmdParam(str_ServerCmdStr, _T("<type>"));
		if (((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_Type == "AskClientState")
		{
			((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_ASKSTATE;
			return 1;
		}

		
	}

	// 准备指令：<Ready></Ready>
	else if (str_ServerCmdStr.Left(strlen("<Ready>")) == "<Ready>")
	{
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_READY;
		
		return 1;
	}
	// 断开连接指令：<Break></Break>
	else if (str_ServerCmdStr.Left(strlen("<Break>")) == "<Break>")
	{
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_BREAK;
		
		return 1;
	}
	//// 启动vga图像采集指令：<VgaStart></VgaStart>
	//else if (str_ServerCmdStr.Left(strlen("<VgaStart>")) == "<VgaStart>")
	//{
	//	((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_VGASTART;
	//	
	//	return 1;
	//}
	//// 停止vga图像采集指令：<VgaStop></VgaStop>
	//else if (str_ServerCmdStr.Left(strlen("<VgaStop>")) == "<VgaStop>")
	//{
	//	((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_VGASTOP;
	//	
	//	return 1;
	//}
	// 串口设置指令：<COMSet><Operation>…</Operation><BitRate>…</BitRate><DataBits>…</DataBits><ParityCheck>…</ParityCheck><StopBit>…</StopBit></COMSet>
	else if (str_ServerCmdStr.Left(strlen("<COMSet>")) == "<COMSet>")
	{
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_EXPCOMSET;
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_ExpComOperation = GetServerCmdParam(str_ServerCmdStr, _T("Operation"));
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_ExpComBitRate = _ttoi(GetServerCmdParam(str_ServerCmdStr, _T("BitRate")));
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_ExpComDataBits = _ttoi(GetServerCmdParam(str_ServerCmdStr, _T("DataBits")));
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_ExpComParityCheck = _ttoi(GetServerCmdParam(str_ServerCmdStr, _T("ParityCheck")));
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_ExpComStopBit = _ttoi(GetServerCmdParam(str_ServerCmdStr, _T("StopBit")));
		
		return 1;
	}
	// 串口数据指令：<COMSend><Length>…</Length><Data>…</Data></COMSend>
	else if (str_ServerCmdStr.Left(strlen("<COMSend>")) == "<COMSend>")
	{
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_EXPCOMSENDDATA;
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_ExpComSendDataLength = _ttoi(GetServerCmdParam(str_ServerCmdStr, _T("Length")));
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_ExpComSendData = GetServerCmdParam(str_ServerCmdStr, _T("Data"));
		
		return 1;
	}
	// PS2鼠标键盘数据传输指令：<PS2Send><MouseLength>…</MouseLength><MouseData>…</MouseData>
	//                          <KeyboardLength>…</KeyboardLength><KeyboardData>…</KeyboardData></PS2Send>
	else if (str_ServerCmdStr.Left(strlen("<PS2Send>")) == "<PS2Send>")
	{
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_PS2SENDDATA;
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Ps2MouseSendDataLength = _ttoi(GetServerCmdParam(str_ServerCmdStr, _T("MouseLength")));
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_Ps2MouseSendData = GetServerCmdParam(str_ServerCmdStr, _T("MouseData"));
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Ps2KeyboardSendDataLength = _ttoi(GetServerCmdParam(str_ServerCmdStr, _T("KeyboardLength")));
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_Ps2KeyboardSendData = GetServerCmdParam(str_ServerCmdStr, _T("KeyboardData"));
		
		return 1;
	}

		
	return 0;


}

CString StatusSocket::GetServerCmdParam(CString str_ServerCmdStr, CString str_ServerCmdKeyWordStr)
{

	int ParamLength;
	int ParamLocation;
	CString ServerCmdParam;

	ParamLocation = str_ServerCmdStr.Find(_T("<") + str_ServerCmdKeyWordStr + _T(">")) + str_ServerCmdKeyWordStr.GetLength() + 2;
	ParamLength = str_ServerCmdStr.Find(_T("</")+str_ServerCmdKeyWordStr+_T(">")) - ParamLocation;
	return ServerCmdParam = str_ServerCmdStr.Mid(ParamLocation, ParamLength);

	
}


void StatusSocket::OnConnect(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	 
	
	CSocket::OnConnect(nErrorCode);
}




void StatusSocket::OnClose(int nErrorCode)
{
	// TODO: 服务器主动断开	 
	Close();

    // 关闭相关定时器
    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->KillTimer(TIMERID_DATA_SAMPLE);
    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->KillTimer(TIMERID_TEST_DATA_SAMPLE);
    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->KillTimer(TIMERID_FILEREV);
    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->KillTimer(TIMERID_EXPCOMRX);
    


    // 更新工作模式为实验模式
    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_WorkMode = _T("ExperimentMode");

    // 更新上位机状态
    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_WorkStatus = _T("Ready");

    // 更新服务器连接状态指示
	((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->m_ServerConnectStatus = 0;
    // 更新服务器注册状态指示
	((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->m_ServerRegisterStatus = 0;

    // 初始化数据写入主控fpga
    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->FpgaWrite(0,0x10,0xffffffffffffffff);

    //关闭文件
    f_LoadFile.Abort();

	//已断开,连接按钮设为可用
	((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->Idc_Button_ServerConnect.SetWindowText(_T("连接"));
	((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->Idc_Button_ServerConnect.EnableWindow(TRUE);

	//断开连接不可用
	((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->Idc_Button_ServerDisconnect.SetWindowText(_T("已断开"));
	((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->Idc_Button_ServerDisconnect.EnableWindow(FALSE);

	// 日志：“服务器连接失败：”
	// “IP地址：xxx”
	// “端口号：TCP-xxxx”
    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("服务器连接失败："));
    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(0,_T("IP地址：")+((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerIPAddress);
    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(0,_T("端口号：")+((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerStatusPort);


	CSocket::OnClose(nErrorCode);
    

}
