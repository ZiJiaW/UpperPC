// StatusSocket.cpp : ʵ���ļ�
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


// StatusSocket ��Ա����




////VGA��Ƶ�����߳�
//UINT _VgaSendThread(LPVOID lparam)
//{  	
//	// ����VGAͼ�����ͣ����͸�������
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

        // ��������
	    int_ServerFileRevCnt = ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->m_StatusSocket->Receive(char_ServerFileRevBuf,64*1024,0);
    
        // д���ļ�
	    f_LoadFile.Write(char_ServerFileRevBuf,int_ServerFileRevCnt);
	    dword_FileRevSumLength+=int_ServerFileRevCnt;

        if ( dword_FileRevSumLength >= ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_FileLength )
        {
            // �ر��ļ����ճ�ʱ��ʱ��
	        ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->KillTimer(TIMERID_FILEREV);
	
            //�ر��ļ�
            f_LoadFile.Close();

            if ( dword_FileRevSumLength == ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_FileLength )
            {
	            // ���ͽ���ȷ��ָ��:<Receive><Result>��</Result></Receive>
	            ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->SendCmd(_T("<Receive><Result>Successful</Result></Receive>")); 
	            // ��־��"�ļ����ճɹ���"
                ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->WriteLogFile(1,_T("�ļ����ճɹ���"));

				// ����fpga����ģʽΪ����ģʽ
				((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->int_FpgaUpdateMode = FPGA_UPDATE_MODE_ONLINE;
				// ѡ��jtag����ģʽ
				((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->Idc_Check_FPGAUpdateJtagTestEn.SetCheck(0);
				((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->Idc_Radio_FPGAUpdateJtagSelect.SetCheck(1);
				((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->Idc_Radio_FPGAUpdateSpiFlashSelect.SetCheck(0);

				// ������д�߳�
				((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->FpgaUpdateThreadStart();
            }
            else
            {
	            // ���ͽ���ȷ��ָ��:<Receive><Result>��</Result></Receive>
	            ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->SendCmd(_T("<Receive><Result>Failed</Result></Receive>")); 
	            // ��־��"�ļ�����ʧ�ܣ�"
                ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->WriteLogFile(1,_T("�ļ�����ʧ�ܣ��ļ�������"));
            }
            // �����ļ�����ʹ�ܹر�
            bool_ServerFileRevEn = 0;



        }
    }
    else
    {
	    ServerCmdRevCnt = ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->m_StatusSocket->Receive(ServerCmdBuf,512,0);
	    str_ServerCmdStr.Format(_T("%s"), ServerCmdBuf);
	    str_ServerCmdStr = str_ServerCmdStr.Left(ServerCmdRevCnt);

        // ��־�������յ�ָ���
        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("���յ�ָ�"));
        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(0,str_ServerCmdStr);

        // ָ�����
	    if (ServerCmdParse(str_ServerCmdStr))
	    {
		    switch (((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd)
		    {
			    case SERVERCMD_RECORD :
				    {
					    // ��־����������ע��ɹ�����
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("������ע��ɹ�!"));
                        
					    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->m_ServerRegisterStatus = 1;
				

					    break;
				    }

			    case SERVERCMD_ASKSTATE :
				    {
					    // ��־������������ѯ��λ��״̬��
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("�յ���������ѯ��λ��״ָ̬��!"));

					    // ������λ��״ָ̬��
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SendCmd(_T("<Client><key>") + ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_Key + ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_UpperComputerID + _T("</key><type>ReplyToServerWithState</type><state>") + ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_WorkStatus + _T("</state></Client>"));

					    // ��־��
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("������λ��״ָ̬�"));
                        


					    break;
				    }

			    case SERVERCMD_LOAD :
				    {
					    // ��־�����յ���¼ָ���
                        ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->WriteLogFile(1,_T("�յ���¼ָ�"));

                        // ������λ��״̬
                        ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->str_WorkStatus = _T("Working");
                        // �ر���ض�ʱ��
	                    ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->KillTimer(TIMERID_DATA_SAMPLE);
                        
                        // ��ʼ���ռ����ļ�
                        // �½������ļ�·��
                        if (!PathFileExists(_T("program")))
                        {
	                        CreateDirectory(_T("program"),NULL);
                        }
                        // ������м����ļ�����ɾ��
                        if (PathFileExists(_T("program\\bitfile.bit")))
                        {
                            f_LoadFile.Abort();
                            CFile::Remove(_T("program\\bitfile.bit"));
                        }

                        // �½������ļ�������
	                    if (!f_LoadFile.Open(_T("program\\bitfile.bit"),CFile::modeCreate|CFile::modeReadWrite))
	                    {
		                    // ��־�����ļ�����ʧ�ܣ���
                            ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->WriteLogFile(1,_T("�ļ�����ʧ�ܡ�"));

	                    }
                        else
                        {
		                    // ��־�����ļ������ɹ�����
                            ((CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd))->WriteLogFile(1,_T("�ļ������ɹ���"));
                            // ��Ӧָ��
                            ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SendCmd(CString(_T("<File></File>")));
                            // �����ļ����ճ�ʱ��ʱ��
	                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SetTimer( TIMERID_FILEREV, TIMERID_FILEREV_TIME, NULL );
                            // ����
                            dword_FileRevSumLength = 0;
                            // �ļ�����ʹ����Ч
					        bool_ServerFileRevEn = 1;
                        }

					    break;
				    }
			
			    case SERVERCMD_DATA :
				    {
					    // ����д������fpga
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->FpgaWrite(0,0x10,_tcstoui64(((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_Data.Mid(26, 4),0,16));
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->FpgaWrite(0,0x12,_tcstoui64(((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_Data.Mid(30, 16),0,16));
					    break;
				    }

			    case SERVERCMD_STARTTEST :
				    {
                        // ���¹���ģʽΪ�Զ�����ģʽ
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_WorkMode = _T("TestMode");
					    // ���������Զ����Է���ָ��
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SendCmd(CString(_T("<StartTest></StartTest>")));

                        // ��־�����յ������Զ�����ָ���
					    // �����������Զ����Է���ָ�
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("�յ������Զ�����ָ�"));
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(0,_T("���������Զ����Է���ָ�"));

					    break;
				    }

			    case SERVERCMD_ENDTEST :
				    {
					    // ����ֹͣ�Զ����Է���ָ��
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SendCmd(CString(_T("<EndTest></EndTest>")));
                        // ���¹���ģʽΪʵ��ģʽ
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_WorkMode = _T("ExperimentMode");


                        // ��־�����յ�ֹͣ�Զ�����ָ���
					    // ������ֹͣ�Զ����Է���ָ�
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("�յ�ֹͣ�Զ�����ָ�"));
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(0,_T("����ֹͣ�Զ����Է���ָ�"));

					    break;
				    }

			    case SERVERCMD_TEST :
				    {
					    // ����д������fpga
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->FpgaWrite(0,0x10,_tcstoui64(((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_Test.Mid(22, 12),0,16));
	                    // �����Զ��������ݲɼ���ʱ��
	                    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SetTimer( TIMERID_TEST_DATA_SAMPLE, TIMERID_TEST_DATA_SAMPLE_TIME, NULL );

					    break;
				    }

			    case SERVERCMD_READY :
				    {
                        if (((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_WorkStatus == _T("Working"))
                        {
					        // ������æָ��
                            ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SendCmd(CString(_T("<Answer><State>Busy</State></Answer>")));
                            // ��־�����յ�����ָ���
					        // ��������æָ�
                            ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("�յ�����ָ�"));
                            ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(0,_T("������æָ�"));
                        }
                        else
                        {
					        // ����׼������ȷ��ָ��
                            ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SendCmd(CString(_T("<Answer><State>Already</State></Answer>")));
                            // ��־�����յ�����ָ���
					        // ������׼������ȷ��ָ�
                            ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("�յ�����ָ�"));
                            ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(0,_T("����׼������ȷ��ָ�"));
                       }


					    break;
				    }

			    case SERVERCMD_BREAK :
				    {
                        // �ر���ض�ʱ��
	                    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->KillTimer(TIMERID_DATA_SAMPLE);
	                    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->KillTimer(TIMERID_TEST_DATA_SAMPLE);
						((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->KillTimer(TIMERID_EXPCOMRX);

                        // ���¹���ģʽΪʵ��ģʽ
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_WorkMode = _T("ExperimentMode");

                        // ������λ��״̬
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_WorkStatus = _T("Ready");

                        // ��ʼ������д������fpga
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->FpgaWrite(0,0x10,0xffffffffffffffff);


						
						// ���ͶϿ�ȷ��ָ��
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SendCmd(CString(_T("<Broken></Broken>")));
                        // ��־�����յ��Ͽ�ָ���
					    // �����ͶϿ�ȷ��ָ�
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("�յ��Ͽ�ָ�"));
                        ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(0,_T("���ͶϿ�ȷ��ָ�"));

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
				case SERVERCMD_EXPCOMSET :
					{
						if (((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_ExpComOperation == _T("Open"))
						{
							// ��־������ʵ�鴮�ڣ���
							((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("��ʵ�鴮�ڣ�"));

							if(((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->ExpComOpen(((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_ExpComBitRate,((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_ExpComDataBits,((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_ExpComStopBit,((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_ExpComParityCheck))
							{

								// ����ʵ�鴮�ڴ򿪳ɹ�ָ��
								((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SendCmd(CString(_T("<COMStatus>OpenSuccessful</COMStatus>")));
								// ����ʵ�鴮�ڽ��ն�ʱ��
								((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SetTimer( TIMERID_EXPCOMRX, TIMERID_EXPCOMRX_TIME, NULL );

								// ��־����ʵ�鴮�ڴ򿪳ɹ�����
								((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("ʵ�鴮�ڴ򿪳ɹ�!"));
							}
							else
							{
								// ����ʵ�鴮�ڴ�ʧ��ָ��
								((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SendCmd(CString(_T("<COMStatus>OpenFailed</COMStatus>")));

								// ��־����ʵ�鴮�ڴ�ʧ�ܡ���
								((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("ʵ�鴮�ڴ�ʧ�ܡ�"));
							}

							
							
						}
						else if (((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_ExpComOperation == _T("Close"))
						{
							// �ر�ʵ�鴮�ڽ��ն�ʱ��
							((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->KillTimer(TIMERID_EXPCOMRX);


							// ��־�����ر�ʵ�鴮�ڣ���
							((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("�ر�ʵ�鴮�ڣ�"));

							if (((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->ExpComClose())
							{
								// ����ʵ�鴮�ڹرճɹ�ָ��
								((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SendCmd(CString(_T("<COMStatus>CloseSuccessful</COMStatus>")));
								// ��־����ʵ�鴮�ڹرճɹ�����
								((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("ʵ�鴮�ڹرճɹ���"));
							}
							else 
							{
								// ����ʵ�鴮�ڹر�ʧ��ָ��
								((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->SendCmd(CString(_T("<COMStatus>CloseFailed</COMStatus>")));
								// ��־����ʵ�鴮�ڹر�ʧ�ܡ���
								((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("ʵ�鴮�ڹر�ʧ�ܡ�"));
							}

						}


					    break;
					}

				case SERVERCMD_EXPCOMSENDDATA :
					{
						// ���ݸ�ʽҪ�����ֽ�Ϊ��λ��ʮ�����ƣ�С��0x10�ģ���λ��0����0x0f
						int int_ExpComSendDataCount = 0;
						CString srt_DataTmp;
						unsigned int uint_ExpComSendDataLength = 0;
						CString str_ExpComSendData;
						BYTE byte_ExpComWriteBuf[EXPCOMBUFSIZE];

						uint_ExpComSendDataLength = ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_ExpComSendDataLength;
						str_ExpComSendData = ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_ExpComSendData;

						// ��־����ʵ�鴮�ڷ������ݣ���
						((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("ʵ�鴮�ڷ������ݣ�"));
						((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(0,str_ExpComSendData);


						// �����ݴ��봮�ڷ���buffer
						for (int_ExpComSendDataCount = 0; int_ExpComSendDataCount < uint_ExpComSendDataLength ; int_ExpComSendDataCount++)
						{
							// �����ҽ�ȡ1�ֽ�����
							srt_DataTmp = str_ExpComSendData.Mid(int_ExpComSendDataCount * 2, 2);
							byte_ExpComWriteBuf[int_ExpComSendDataCount]  = (byte)( _tcstoui64(srt_DataTmp,0,16) & 0xff );
						}

						// ���ڷ�������
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
							// ��־����PS2��귢�����ݣ���
							((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("PS2��귢�����ݣ�"));
							((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(0,str_Ps2SendData);
						
							// ��������ݷ��͸�ʵ��fpga��������
							for (int_Ps2SendDataCount = 0; int_Ps2SendDataCount < uint_Ps2SendDataLength ; int_Ps2SendDataCount++)
							{
								// �����ҽ�ȡ1�ֽ�����
								str_DataTmp = str_Ps2SendData.Mid(int_Ps2SendDataCount * 2, 2);
								uint64_DataTmp = _tcstoui64(str_DataTmp,0,16) & 0xff;
								((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->FpgaWrite(0, 0x30, ((uint64_DataTmp | 0x0000000000000100) << 32));
							}
						}

						uint_Ps2SendDataLength = ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Ps2KeyboardSendDataLength;
						str_Ps2SendData = ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_Ps2KeyboardSendData;

						if (uint_Ps2SendDataLength > 0)
						{
							// ��־����PS2���̷������ݣ���
							((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("PS2���̷������ݣ�"));
							((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(0,str_Ps2SendData);
						
							// ��������ݷ��͸�ʵ��fpga��������
							for (int_Ps2SendDataCount = 0; int_Ps2SendDataCount < uint_Ps2SendDataLength ; int_Ps2SendDataCount++)
							{
								// �����ҽ�ȡ1�ֽ�����
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

	// ע��ȷ��ָ�<Record><DataPort>��</DataPort></Record>
	if (str_ServerCmdStr.Left(strlen("<Record>")) == "<Record>")
	{
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_RECORD;
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_DataPort = GetServerCmdParam(str_ServerCmdStr, _T("Dataport"));
		
		return 1;
	}
	// ��¼ָ�<Load><Length>��</Length><HashCode>��</HashCode></Load>
	else if (str_ServerCmdStr.Left(strlen("<Load>")) == "<Load>")
	{
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_LOAD;
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_FileLength = _ttoi(GetServerCmdParam(str_ServerCmdStr, _T("Length")));
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_FileHashCode = _ttoi(GetServerCmdParam(str_ServerCmdStr, _T("Hashcode")));
		
		return 1;
	}
	// ���ݴ���ָ��:<Data>��</Data>
	else if (str_ServerCmdStr.Left(strlen("<Data>")) == "<Data>")
	{
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_DATA;
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_Data = GetServerCmdParam(str_ServerCmdStr, _T("Data"));
		
		return 1;
	}
	// �����Զ�����ָ��:<StartTest></StartTest>
	else if (str_ServerCmdStr.Left(strlen("<StartTest>")) == "<StartTest>")
	{
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_STARTTEST;
		
		return 1;
	}
	// �����Զ�����ָ��:<EndTest></EndTest>
	else if (str_ServerCmdStr.Left(strlen("<EndTest>")) == "<EndTest>")
	{
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_ENDTEST;
		
		return 1;
	}
	// �Զ�����ָ��:<Test>��</Test>
	else if (str_ServerCmdStr.Left(strlen("<Test>")) == "<Test>")
	{
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_TEST;
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_Test = GetServerCmdParam(str_ServerCmdStr, _T("Test"));
		
		return 1;
	}
	//// ����Ӧ��ָ�<Response></Response>
	//else if (str_ServerCmdStr.Left(strlen("<Response>")) == "<Response>")
	//{
	//	((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_RESPONSE;
	//	
	//	return 1;
	//}
	// ��������ѯ��λ��״ָ̬�
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

	// ׼��ָ�<Ready></Ready>
	else if (str_ServerCmdStr.Left(strlen("<Ready>")) == "<Ready>")
	{
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_READY;
		
		return 1;
	}
	// �Ͽ�����ָ�<Break></Break>
	else if (str_ServerCmdStr.Left(strlen("<Break>")) == "<Break>")
	{
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_BREAK;
		
		return 1;
	}
	//// ����vgaͼ��ɼ�ָ�<VgaStart></VgaStart>
	//else if (str_ServerCmdStr.Left(strlen("<VgaStart>")) == "<VgaStart>")
	//{
	//	((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_VGASTART;
	//	
	//	return 1;
	//}
	//// ֹͣvgaͼ��ɼ�ָ�<VgaStop></VgaStop>
	//else if (str_ServerCmdStr.Left(strlen("<VgaStop>")) == "<VgaStop>")
	//{
	//	((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_VGASTOP;
	//	
	//	return 1;
	//}
	// ��������ָ�<COMSet><Operation>��</Operation><BitRate>��</BitRate><DataBits>��</DataBits><ParityCheck>��</ParityCheck><StopBit>��</StopBit></COMSet>
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
	// ��������ָ�<COMSend><Length>��</Length><Data>��</Data></COMSend>
	else if (str_ServerCmdStr.Left(strlen("<COMSend>")) == "<COMSend>")
	{
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_Cmd = SERVERCMD_EXPCOMSENDDATA;
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->uint_ServerMsg_ExpComSendDataLength = _ttoi(GetServerCmdParam(str_ServerCmdStr, _T("Length")));
		((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerMsg_ExpComSendData = GetServerCmdParam(str_ServerCmdStr, _T("Data"));
		
		return 1;
	}
	// PS2���������ݴ���ָ�<PS2Send><MouseLength>��</MouseLength><MouseData>��</MouseData>
	//                          <KeyboardLength>��</KeyboardLength><KeyboardData>��</KeyboardData></PS2Send>
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
	// TODO: �ڴ����ר�ô����/����û���
	 
	
	CSocket::OnConnect(nErrorCode);
}




void StatusSocket::OnClose(int nErrorCode)
{
	// TODO: �����������Ͽ�	 
	Close();

    // �ر���ض�ʱ��
    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->KillTimer(TIMERID_DATA_SAMPLE);
    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->KillTimer(TIMERID_TEST_DATA_SAMPLE);
    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->KillTimer(TIMERID_FILEREV);
    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->KillTimer(TIMERID_EXPCOMRX);
    


    // ���¹���ģʽΪʵ��ģʽ
    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_WorkMode = _T("ExperimentMode");

    // ������λ��״̬
    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_WorkStatus = _T("Ready");

    // ���·���������״ָ̬ʾ
	((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->m_ServerConnectStatus = 0;
    // ���·�����ע��״ָ̬ʾ
	((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->m_ServerRegisterStatus = 0;

    // ��ʼ������д������fpga
    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->FpgaWrite(0,0x10,0xffffffffffffffff);

    //�ر��ļ�
    f_LoadFile.Abort();

	//�ѶϿ�,���Ӱ�ť��Ϊ����
	((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->Idc_Button_ServerConnect.SetWindowText(_T("����"));
	((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->Idc_Button_ServerConnect.EnableWindow(TRUE);

	//�Ͽ����Ӳ�����
	((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->Idc_Button_ServerDisconnect.SetWindowText(_T("�ѶϿ�"));
	((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->Idc_Button_ServerDisconnect.EnableWindow(FALSE);

	// ��־��������������ʧ�ܣ���
	// ��IP��ַ��xxx��
	// ���˿ںţ�TCP-xxxx��
    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(1,_T("����������ʧ�ܣ�"));
    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(0,_T("IP��ַ��")+((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerIPAddress);
    ((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->WriteLogFile(0,_T("�˿ںţ�")+((CUpperComputerDlg*)AfxGetApp()->m_pMainWnd)->str_ServerStatusPort);


	CSocket::OnClose(nErrorCode);
    

}
