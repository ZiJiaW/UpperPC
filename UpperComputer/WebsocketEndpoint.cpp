#include "stdafx.h"
#include "WebsocketEndpoint.h"
#include "UpperComputer.h"
#include "UpperComputerDlg.h"
#include "resource.h"
#include "define.h"

WebsocketEndpoint::WebsocketEndpoint()
{
    m_endpoint.clear_access_channels(websocketpp::log::alevel::all);
    m_endpoint.clear_error_channels(websocketpp::log::alevel::all);
    m_endpoint.init_asio();
    m_endpoint.start_perpetual();
    m_thread.reset(new std::thread(&client::run, &m_endpoint));
}

WebsocketEndpoint::~WebsocketEndpoint()
{
    m_endpoint.stop_perpetual();
    auto pDlg = (CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd);
    pDlg->WriteLogFile(1, _T("正在关闭终端......"));
    if (m_conptr->getStatus() == "Open")// close opening connection
    {
        std::error_code ec;
        m_endpoint.close(m_conptr->getHdl(), websocketpp::close::status::going_away, "App closed!", ec);
    }
}

int WebsocketEndpoint::connect(std::string const &uri)
{
    std::error_code ec;
    client::connection_ptr con = m_endpoint.get_connection(uri, ec);
    auto pDlg = (CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd);
    if (ec)
    {
        pDlg->WriteLogFile(1, _T("初始化连接失败！"));
        return -1;
    }
    m_conptr.reset(new ConnectMetadata(con->get_handle(), uri));
    con->set_open_handler(std::bind(&ConnectMetadata::onOpen, m_conptr, &m_endpoint, std::placeholders::_1));
    con->set_fail_handler(std::bind(&ConnectMetadata::onFail, m_conptr, &m_endpoint, std::placeholders::_1));
    con->set_close_handler(std::bind(&ConnectMetadata::onClose, m_conptr, &m_endpoint, std::placeholders::_1));
    con->set_message_handler(std::bind(&ConnectMetadata::onMessage, m_conptr, std::placeholders::_1, std::placeholders::_2));
    con->set_pong_timeout(5000);
    m_endpoint.connect(con);
    return 1;
}
void WebsocketEndpoint::close(websocketpp::close::status::value code, std::string reason)
{
    std::error_code ec;
    auto pDlg = (CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd);
    try {
        m_endpoint.close(m_conptr->getHdl(), code, reason, ec);
        closeFile();
    }
    catch (...) {
        pDlg->WriteLogFile(1, _T("连接关闭异常！"));
        pDlg->OnBnClickedButtonDisconnect();
    }
    setFileRcvEnable(false);
    if(ec)
    {
        pDlg->WriteLogFile(1, _T("连接关闭失败！"));
    }
}
void WebsocketEndpoint::send(std::string message, bool toPrint)
{
    std::error_code ec;
    auto pDlg = (CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd);
    try {
        m_endpoint.send(m_conptr->getHdl(), message, websocketpp::frame::opcode::text, ec);
    }
    catch (...) {
        pDlg->WriteLogFile(1, CString(_T("发送异常，发送内容：")) + CSTR(message));
    }
    
    if (ec)
    {
        pDlg->WriteLogFile(1, CString(_T("发送消息失败，错误信息：")) + CSTR(ec.message()));
    }
    else
    {
        if(toPrint) pDlg->WriteLogFile(1, CString(_T("发送：")) + CSTR(message));
    }
}

std::string WebsocketEndpoint::getConStatus() const
{
    return  m_conptr->getStatus();
}

void WebsocketEndpoint::setFileRcvEnable(bool flag)
{
    m_conptr->setFileRcvEnable(flag);
}

void WebsocketEndpoint::closeFile()
{
    m_conptr->closeFile();
}