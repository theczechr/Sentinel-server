#include "WebSocketAccount.hpp"

void WebSocketAccount::handleNewMessage(const drogon::WebSocketConnectionPtr& wsConnPtr, std::string&& message, const drogon::WebSocketMessageType& type)
{
    std::string messageType = "Unknown";
    if (type == drogon::WebSocketMessageType::Text)
        messageType = "text";
    else if (type == drogon::WebSocketMessageType::Pong)
        messageType = "pong";
    else if (type == drogon::WebSocketMessageType::Ping)
        messageType = "ping";
    else if (type == drogon::WebSocketMessageType::Binary)
        messageType = "binary";
    else if (type == drogon::WebSocketMessageType::Close)
        messageType = "Close";

    LOG_INFO << "Message from '" << wsConnPtr->peerAddr().toIpPort() << "', message content '" << message << "', message type '" << messageType << "'";
}

void WebSocketAccount::handleConnectionClosed(const drogon::WebSocketConnectionPtr& conn)
{
    LOG_INFO << "Websocket connection closed!";
}

void WebSocketAccount::handleNewConnection(const drogon::HttpRequestPtr& req, const drogon::WebSocketConnectionPtr& conn)
{
    LOG_INFO << "New websocket connection!";

    std::string input = req->getPath();

    switch (resolveOption(input))
    {
        case Register:
        {
            LOG_INFO << "Request path '" << req->getPath() << "'";

            std::string pub_key_fprint = req->getParameter("pub_key_fprint");
            std::string username = req->getParameter("username");
            std::string recovery_phrase = req->getParameter("recovery_phrase");
            std::string last_login = req->getParameter("last_login");

            return;
        }
        case login:
        {
            LOG_INFO << "Request path '" << req->getPath() << "'";

            std::string pub_key_fprint = req->getParameter("pub_key_fprint");
            std::string last_login = req->getParameter("last_login");

            return;
        }
        case change_username:
        {
            LOG_INFO << "Request path '" << req->getPath() << "'";

            std::string pub_key_fprint = req->getParameter("pub_key_fprint");
            std::string username = req->getParameter("username");
            std::string last_login = req->getParameter("last_login");            

            break;
        }
        case recovery:
        {
            LOG_INFO << "Request path '" << req->getPath() << "'";

            std::string recovery_phrase = req->getParameter("recovery_phrase");
            std::string last_login = req->getParameter("last_login");

            break;
        }
        
        // handles Option_Invalid and any other missing/unmapped cases
        default:
        {
            LOG_ERROR << "Request path '" << req->getPath() << "' doesnt exist";
            break;
        }
    }
}
