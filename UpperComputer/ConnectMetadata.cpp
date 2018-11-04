#include "stdafx.h"
#include "ConnectMetadata.h"


ConnectMetadata::ConnectMetadata(websocketpp::connection_hdl hdl, std::string uri):
    m_hdl(hdl), m_uri(uri), m_status("Connecting"), m_server("None"), m_errorReason(""){}

ConnectMetadata::~ConnectMetadata(){}

void ConnectMetadata::onOpen(client* c, websocketpp::connection_hdl hdl)
{
    m_status = "Open";
    client::connection_ptr con = c->get_con_from_hdl(hdl);
    m_server = con->get_response_header("Server");
}

void ConnectMetadata::onFail(client* c, websocketpp::connection_hdl hdl)
{
    m_status = "Failed";
    client::connection_ptr con = c->get_con_from_hdl(hdl);
    m_server = con->get_response_header("Server");
    m_errorReason = con->get_ec().message();
}
void ConnectMetadata::onClose(client* c, websocketpp::connection_hdl hdl)
{
    m_status = "Closed";
    client::connection_ptr con = c->get_con_from_hdl(hdl);
    std::stringstream s;
    s << "close code: " << con->get_remote_close_code() << " ("
        << websocketpp::close::status::get_string(con->get_remote_close_code())
        << "), close reason: " << con->get_remote_close_reason();
    m_errorReason = s.str();
}

void ConnectMetadata::onMessage(websocketpp::connection_hdl hdl, client::message_ptr msg)
{
    // TODO
}

websocketpp::connection_hdl ConnectMetadata::getHdl() const
{
    return m_hdl;
}

std::string ConnectMetadata::getStatus() const
{
    return m_status;
}

