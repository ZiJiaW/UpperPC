#pragma once

using client = websocketpp::client<websocketpp::config::asio_client>;

class ConnectMetadata
{
public:
    using ptr = std::shared_ptr<ConnectMetadata>;

    ConnectMetadata(websocketpp::connection_hdl hdl, std::string uri);
    ~ConnectMetadata();
    void onOpen(client* c, websocketpp::connection_hdl hdl);
    void onFail(client* c, websocketpp::connection_hdl hdl);
    void onClose(client* c, websocketpp::connection_hdl hdl);
    void onMessage(websocketpp::connection_hdl hdl, client::message_ptr msg);

    websocketpp::connection_hdl getHdl() const;
    std::string getStatus() const;

private:
    websocketpp::connection_hdl m_hdl;
    std::string m_status;
    std::string m_uri;
    std::string m_server;
    std::string m_errorReason;
};

