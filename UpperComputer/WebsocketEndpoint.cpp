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
    if (m_conptr->getStatus() == "Open")// close opening connection
    {
        std::error_code ec;
        // todo
    }
}

int WebsocketEndpoint::connect(std::string const &uri)
{
    std::error_code ec;
    client::connection_ptr con = m_endpoint.get_connection(uri, ec);
    if (ec)
    {
        //TODO
        return -1;
    }
    m_conptr.reset(new ConnectMetadata(con->get_handle(), uri));
    con->set_open_handler(std::bind(&ConnectMetadata::onOpen, m_conptr, &m_endpoint, std::placeholders::_1));
    con->set_fail_handler(std::bind(&ConnectMetadata::onFail, m_conptr, &m_endpoint, std::placeholders::_1));
    con->set_close_handler(std::bind(&ConnectMetadata::onClose, m_conptr, &m_endpoint, std::placeholders::_1));
    con->set_message_handler(std::bind(&ConnectMetadata::onMessage, m_conptr, std::placeholders::_1, std::placeholders::_2));

    m_endpoint.connect(con);
    return 1;
}
void WebsocketEndpoint::close(websocketpp::close::status::value code, std::string reason)
{
    std::error_code ec;
    m_endpoint.close(m_conptr->getHdl(), code, reason, ec);
    if(ec)
    {
        // TODO
    }
}
void WebsocketEndpoint::send(std::string message)
{
    std::error_code ec;
    m_endpoint.send(m_conptr->getHdl(), message, websocketpp::frame::opcode::text, ec);
    // TODO: do some record
    auto pDlg = (CUpperComputerDlg*)(AfxGetApp()->m_pMainWnd);// 对话框指针
    if (ec)
    {
        pDlg->WriteLogFile(1, _T("发送消息失败，错误信息："));
        pDlg->WriteLogFile(0, CSTR(ec.message()));
    }
    else
    {
        pDlg->WriteLogFile(1, _T("发送："));
        pDlg->WriteLogFile(0, CSTR(message));
    }
}

std::string WebsocketEndpoint::getConStatus() const
{
    return  m_conptr->getStatus();
}
