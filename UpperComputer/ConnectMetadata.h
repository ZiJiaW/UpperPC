#pragma once

using client = websocketpp::client<websocketpp::config::asio_client>;
#define CSTR(str) _T(str.c_str())

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
    void setFileRcvEnable(bool flag);
    void closeFile();
private:
    websocketpp::connection_hdl m_hdl;
    std::string m_status;
    std::string m_uri;
    std::string m_server;
    std::string m_errorReason;

    bool m_fileRcvEnable;
    bool m_over50;
    CFile m_loadFile;
    DWORD m_fileRcvLengthSum;

    bool parseCmd(std::string cmd);
    CString getParamFromCmd(CString cmd, CString keyword);
};

