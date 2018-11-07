#pragma once
#include "ConnectMetadata.h"

class WebsocketEndpoint
{
public:
    WebsocketEndpoint();
    ~WebsocketEndpoint();

    int connect(std::string const &uri);
    void close(websocketpp::close::status::value code, std::string reason);
    void send(std::string message);

    std::string getConStatus() const;
    void setFileRcvEnable(bool flag);
    void closeFile();
private:
    client m_endpoint;
    std::shared_ptr<std::thread> m_thread;
    ConnectMetadata::ptr m_conptr;
};

