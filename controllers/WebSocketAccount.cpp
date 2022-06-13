#include "WebSocketAccount.hpp"

/*
* Smazal jsem tvoje veci na chatrooms, protoze jsme se bavili, ze si to musime rozdelit
* Tohle bude slouzit na komunikaci ohledne accountu
* Ty vytvor neco jako WebSocketChat, ale necham to na tobe
* ---
* Udelal jsem ti nejakou base podle examplu
*/

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
    
    // Tohle mi prijde hrozne ghetto, ale nevim jak to jinak vyresit
    if (req->getPath() == "/register")
    {
        LOG_INFO << "Request path '" << req->getPath() << "'";
        if (database::user_exist_full(req->getParameter("username"), req->getParameter("email_hash"), req->getParameter("password_hash"), req->getParameter("phone_hash")))
        {
            conn->send("0, User already exist.");
            return;
        }
        database::create_account(req->getParameter("username"), req->getParameter("email_hash"), req->getParameter("password_hash"), req->getParameter("phone_hash"), "co jak kdy kde");
        conn->send("1, Successfully registered.");
        return;
    }
    else if (req->getPath() == "/login")
    {
        LOG_INFO << "Request path '" << req->getPath() << "'";
        if (!database::user_exist(req->getParameter("username"), req->getParameter("password_hash")))
        {
            conn->send("0, User doesnt exist. Please register.");
            return;
        }
        conn->send("1, Successfully logged in.");
        return;
    }
    else if (req->getPath() == "/changeUsername")
    {
        LOG_INFO << "Request path '" << req->getPath() << "'";
        // Jak se dostanu k Account change_username ?
    }
    else if (req->getPath() == "/changeEmail")
    {
        LOG_INFO << "Request path '" << req->getPath() << "'";
        // Jak se dostanu k Account change_email_hash ?
    }
    else if (req->getPath() == "/changePassword")
    {
        LOG_INFO << "Request path '" << req->getPath() << "'";
        // Jak se dostanu k Account change_password_hash ?
    }
    LOG_ERROR << "Request path '" << req->getPath() << "' doesnt exist";
}