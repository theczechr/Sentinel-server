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
    LOG_DEBUG << "New websocket connection!";

    std::string username = req->getParameter("username");
    std::string password_hash = req->getParameter("password_hash");
    std::string email_hash = req->getParameter("email_hash");
    std::string phone_hash = req->getParameter("phone_hash");
    std::string recovery_phrase = req->getParameter("recovery_phrase");
    std::string input = req->getPath();

    switch (resolveOption(input))
    {
        case Login:
        {
            LOG_INFO << "Request path '" << req->getPath() << "'";
            if (true) //!database::user_exist(username, password_hash)
            {
                conn->send("0, User doesnt exist. Please register.");
                return;
            }
            conn->send("1, Successfully logged in.");
            return;
        }
        /*
        case Register:
        {
            LOG_INFO << "Request path '" << req->getPath() << "'";
            if (database::user_exist_full(username, email_hash, password_hash, phone_hash))
            {
                conn->send("0, User already exist.");
                return;
            }
            database::create_account(username, email_hash, password_hash, phone_hash, recovery_phrase);
            conn->send("1, Successfully registered.");
            return;
        }
        case Change_username:
        {
            LOG_INFO << "Request path '" << req->getPath() << "'";
            if (!database::user_exist(username, password_hash))
            {
                conn->send("0, User doesnt exist. Please register.");
                return;
            }
            account::change_username(req->getParameter("old_username"), req->getParameter("new_username"));
            break;
        }
        */
        case Change_password:
        {
            LOG_INFO << "Request path '" << req->getPath() << "'";
            // Jak se dostanu k Account change_password_hash ?
            break;
        }
        case Change_email:
        {
            LOG_INFO << "Request path '" << req->getPath() << "'";
            // Jak se dostanu k Account change_email_hash ?
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
